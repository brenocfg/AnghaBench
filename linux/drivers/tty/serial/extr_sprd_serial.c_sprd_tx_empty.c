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
struct uart_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPRD_STS1 ; 
 int SPRD_TX_FIFO_CNT_MASK ; 
 unsigned int TIOCSER_TEMT ; 
 int serial_in (struct uart_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int sprd_tx_empty(struct uart_port *port)
{
	if (serial_in(port, SPRD_STS1) & SPRD_TX_FIFO_CNT_MASK)
		return 0;
	else
		return TIOCSER_TEMT;
}