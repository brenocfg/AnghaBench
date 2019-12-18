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
 int TIOCM_CAR ; 
 int TIOCM_CTS ; 
 int TIOCM_DSR ; 
 int TIOCM_RNG ; 
 int UART_MSR_CTS ; 
 int UART_MSR_DCD ; 
 int UART_MSR_DSR ; 
 int UART_MSR_RI ; 

__attribute__((used)) static inline int serial8250_MSR_to_TIOCM(int msr)
{
	int tiocm = 0;

	if (msr & UART_MSR_DCD)
		tiocm |= TIOCM_CAR;
	if (msr & UART_MSR_RI)
		tiocm |= TIOCM_RNG;
	if (msr & UART_MSR_DSR)
		tiocm |= TIOCM_DSR;
	if (msr & UART_MSR_CTS)
		tiocm |= TIOCM_CTS;

	return tiocm;
}