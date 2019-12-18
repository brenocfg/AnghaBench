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
 unsigned long LINFLEXD_UARTSR_DTFTFF ; 
 unsigned int TIOCSER_TEMT ; 
 scalar_t__ UARTSR ; 
 unsigned long readl (scalar_t__) ; 

__attribute__((used)) static unsigned int linflex_tx_empty(struct uart_port *port)
{
	unsigned long status;

	status = readl(port->membase + UARTSR) & LINFLEXD_UARTSR_DTFTFF;

	return status ? TIOCSER_TEMT : 0;
}