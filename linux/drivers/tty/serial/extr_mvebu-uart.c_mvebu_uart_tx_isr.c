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
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 unsigned int STAT_TX_RDY (struct uart_port*) ; 
 scalar_t__ UART_STAT ; 
 int /*<<< orphan*/  mvebu_uart_tx_chars (struct uart_port*,unsigned int) ; 
 unsigned int readl (scalar_t__) ; 

__attribute__((used)) static irqreturn_t mvebu_uart_tx_isr(int irq, void *dev_id)
{
	struct uart_port *port = (struct uart_port *)dev_id;
	unsigned int st = readl(port->membase + UART_STAT);

	if (st & STAT_TX_RDY(port))
		mvebu_uart_tx_chars(port, st);

	return IRQ_HANDLED;
}