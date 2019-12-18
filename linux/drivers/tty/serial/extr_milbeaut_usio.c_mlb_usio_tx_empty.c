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
struct uart_port {scalar_t__ membase; } ;

/* Variables and functions */
 scalar_t__ MLB_USIO_REG_SSR ; 
 int MLB_USIO_SSR_TBI ; 
 unsigned int TIOCSER_TEMT ; 
 int readb (scalar_t__) ; 

__attribute__((used)) static unsigned int mlb_usio_tx_empty(struct uart_port *port)
{
	return (readb(port->membase + MLB_USIO_REG_SSR) & MLB_USIO_SSR_TBI) ?
		TIOCSER_TEMT : 0;
}