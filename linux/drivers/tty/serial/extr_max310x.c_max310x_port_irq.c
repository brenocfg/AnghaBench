#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct uart_port {int dummy; } ;
struct max310x_port {TYPE_1__* p; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {struct uart_port port; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  MAX310X_IRQSTS_REG ; 
 unsigned int MAX310X_IRQ_CTS_BIT ; 
 unsigned int MAX310X_IRQ_TXEMPTY_BIT ; 
 unsigned int MAX310X_LSR_CTS_BIT ; 
 int /*<<< orphan*/  MAX310X_LSR_IRQSTS_REG ; 
 int /*<<< orphan*/  MAX310X_RXFIFOLVL_REG ; 
 int /*<<< orphan*/  max310x_handle_rx (struct uart_port*,unsigned int) ; 
 unsigned int max310x_port_read (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max310x_start_tx (struct uart_port*) ; 
 int /*<<< orphan*/  uart_handle_cts_change (struct uart_port*,int) ; 

__attribute__((used)) static irqreturn_t max310x_port_irq(struct max310x_port *s, int portno)
{
	struct uart_port *port = &s->p[portno].port;
	irqreturn_t res = IRQ_NONE;

	do {
		unsigned int ists, lsr, rxlen;

		/* Read IRQ status & RX FIFO level */
		ists = max310x_port_read(port, MAX310X_IRQSTS_REG);
		rxlen = max310x_port_read(port, MAX310X_RXFIFOLVL_REG);
		if (!ists && !rxlen)
			break;

		res = IRQ_HANDLED;

		if (ists & MAX310X_IRQ_CTS_BIT) {
			lsr = max310x_port_read(port, MAX310X_LSR_IRQSTS_REG);
			uart_handle_cts_change(port,
					       !!(lsr & MAX310X_LSR_CTS_BIT));
		}
		if (rxlen)
			max310x_handle_rx(port, rxlen);
		if (ists & MAX310X_IRQ_TXEMPTY_BIT)
			max310x_start_tx(port);
	} while (1);
	return res;
}