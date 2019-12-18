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
 int ASCFSTAT_TXFFLMASK ; 
 scalar_t__ LTQ_ASC_FSTAT ; 
 unsigned int TIOCSER_TEMT ; 
 int __raw_readl (scalar_t__) ; 

__attribute__((used)) static unsigned int
lqasc_tx_empty(struct uart_port *port)
{
	int status;
	status = __raw_readl(port->membase + LTQ_ASC_FSTAT) &
		 ASCFSTAT_TXFFLMASK;
	return status ? 0 : TIOCSER_TEMT;
}