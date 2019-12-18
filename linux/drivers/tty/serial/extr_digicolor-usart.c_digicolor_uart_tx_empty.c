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
typedef  int u8 ;
struct uart_port {scalar_t__ membase; } ;

/* Variables and functions */
 unsigned int TIOCSER_TEMT ; 
 scalar_t__ UA_STATUS ; 
 int UA_STATUS_TX_READY ; 
 int readb_relaxed (scalar_t__) ; 

__attribute__((used)) static unsigned int digicolor_uart_tx_empty(struct uart_port *port)
{
	u8 status = readb_relaxed(port->membase + UA_STATUS);

	return (status & UA_STATUS_TX_READY) ? TIOCSER_TEMT : 0;
}