#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int TIOCM_DTR ; 
 int TIOCM_LOOP ; 
 int TIOCM_OUT1 ; 
 int TIOCM_OUT2 ; 
 int TIOCM_RTS ; 
 int UART_MCR_DTR ; 
 int UART_MCR_LOOP ; 
 int UART_MCR_OUT1 ; 
 int UART_MCR_OUT2 ; 
 int UART_MCR_RTS ; 

__attribute__((used)) static inline int serial8250_MCR_to_TIOCM(int mcr)
{
	int tiocm = 0;

	if (mcr & UART_MCR_RTS)
		tiocm |= TIOCM_RTS;
	if (mcr & UART_MCR_DTR)
		tiocm |= TIOCM_DTR;
	if (mcr & UART_MCR_OUT1)
		tiocm |= TIOCM_OUT1;
	if (mcr & UART_MCR_OUT2)
		tiocm |= TIOCM_OUT2;
	if (mcr & UART_MCR_LOOP)
		tiocm |= TIOCM_LOOP;

	return tiocm;
}