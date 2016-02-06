/* 
 * File:   main.c
 * Author: gvanhoy
 * Description: lab 0.
 * Created on August 27, 2015, 10:14 AM
 */

#include <xc.h>
#include <sys/attribs.h>
#include "timer.h"
#include "led.h"
#include "interrupt.h"
#include "config.h"

#define OUTPUT 0
#define INPUT 1

#define press 0;
#define release 1;


//TODO: Define states of the state machine
typedef enum stateTypeEnum{
    led1,led2,led3,delay
} stateType;

volatile stateType state = led1;
volatile int onesec;
//TODO: Use volatile variables that change within interrupts

int main() {
    SYSTEMConfigPerformance(10000000);    //Configures low-level system parameters for 10 MHz clock
    enableInterrupts();                   //This function is necessary to use interrupts.

    //TODO: Write each initialization function
    initLEDs();
    initTimer1();
    initTimer2();
    initSW1();
    
    
    while(1){
        //TODO: Implement a state machine to create the desired functionality
        switch(state){
                case led1:
                    onesec=0;
                    TMR1=0;
                    turnOnLED(1);
                    if (PORTDbits.RD6==0 ){
                        state = delay;
                    }
                    break;
                case led2:
                    onesec=0;
                    TMR1=0;
                    turnOnLED(2);
                    if (PORTDbits.RD6==0 ){
                        state = delay;
                    }
                    break;
                case led3:
                    onesec=0;
                    TMR1=0;
                    turnOnLED(3);
                     if (PORTDbits.RD6==0 ){
                        state = delay;
                    }
                    break;
                case delay:
                    delayMs(5);
                    if (LATDbits.LATD0==1 && PORTDbits.RD6==1 && onesec==0){
                        state=led2;
                    }
                    else if(LATDbits.LATD1==1&& PORTDbits.RD6==1 && onesec==0){
                        state=led3;
                    }
                    else if(LATDbits.LATD2==1&& PORTDbits.RD6==1 && onesec==0){
                        state=led1;
                    }
                    else if (LATDbits.LATD0==1&& PORTDbits.RD6==1 && onesec==1){
                        state=led3;
                    }
                    else if(LATDbits.LATD1==1&& PORTDbits.RD6==1 && onesec==1){
                        state=led1;
                    }
                    else if(LATDbits.LATD2==1 && PORTDbits.RD6==1 && onesec==1){
                        state=led2;
                    }
                    break;
        }
    }
    
    return 0;
}


void __ISR(_TIMER_1_VECTOR, IPL3SRS) _T1Interrupt()
 {
    IFS0bits.T1IF = 0;
    
    onesec=1;
 }

 //TODO: Add interrupt service routines that manage the change of states
 //for particular events as needed
 