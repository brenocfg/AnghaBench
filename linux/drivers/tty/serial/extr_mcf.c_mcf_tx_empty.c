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
 scalar_t__ MCFUART_USR ; 
 int MCFUART_USR_TXEMPTY ; 
 unsigned int TIOCSER_TEMT ; 
 int readb (scalar_t__) ; 

__attribute__((used)) static unsigned int mcf_tx_empty(struct uart_port *port)
{
	return (readb(port->membase + MCFUART_USR) & MCFUART_USR_TXEMPTY) ?
		TIOCSER_TEMT : 0;
}