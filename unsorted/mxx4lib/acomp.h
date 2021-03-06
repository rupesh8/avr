/*
 *      acomp.h
 *      
 *      Copyright 2009 Nathaniel Robert Lewis <linux.robotdude@gmail.com>
 *      
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *      
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *      
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *      MA 02110-1301, USA.
 * 
 * 
 *      This header controls the analog comparator on the atmega chips  
 *      Example:
 *          initACOMP(0, 0);           //init the comparator without multiplexing
 *          uint8_t val = getACOMP();  //get the analog comparator's output and put in new variable val
 * 
 *      The analog comparator also supports mapping the negative input to the output of the ADC multiplexer,
 *      and making the ADC multiplexer bits control the negative input pin
 *      Example:
 *          initACOMP(1, 0);     //set up the comparator with multiplexing on negative pin on ADC0
 *          uint8_t val0 = getACOMP();  //get the analog comparator's value
 *          switchChannel(1);    //change negative pin to ADC1  
 *          uint8_t val1 = getACOMP();  //get the new value
 * 
 */


#ifndef _ACOMP_H
#define _ACOMP_H

#include <avr/io.h>
#include <stdint.h>

void initACOMP (uint8_t multiplex, uint8_t channel) {    //init analog comparator
	if(multiplex) {                             //if multiplexing requested
		ADCSRA = (1 << ACME);                    //tell the ADC to disable and enable comparator multiplexing
		ADMUX = channel & 0x07;                 //the the desired channel to set to the negative input and mask unused bits
    }
    ACSR = 0x00;                            //init the analog comparator
}

void switchChannel (uint8_t channel) { //switched the negative input pin of the Analog comparator in multiplexer mode
	ADMUX = channel & 0x07;     //set the multiplexer channel and mask unused buts
	__asm ("NOP");              //wait 2 clock cycles
	__asm ("NOP");
}

uint8_t getACOMP (void) {
    return ((ACSR >> ACO) & 1);             //return the ACO (analog comparator output) bit in ACSR 
}

#endif
