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
struct uart_port {int /*<<< orphan*/  lock; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  PORT_RDA ; 
 int /*<<< orphan*/  RDA_UART_IRQ_MASK ; 
 int /*<<< orphan*/  RDA_UART_STATUS ; 
 int UART_CONFIG_TYPE ; 
 int /*<<< orphan*/  rda_uart_request_port (struct uart_port*) ; 
 int /*<<< orphan*/  rda_uart_write (struct uart_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void rda_uart_config_port(struct uart_port *port, int flags)
{
	unsigned long irq_flags;

	if (flags & UART_CONFIG_TYPE) {
		port->type = PORT_RDA;
		rda_uart_request_port(port);
	}

	spin_lock_irqsave(&port->lock, irq_flags);

	/* Clear mask, so no surprise interrupts. */
	rda_uart_write(port, 0, RDA_UART_IRQ_MASK);

	/* Clear status register */
	rda_uart_write(port, 0, RDA_UART_STATUS);

	spin_unlock_irqrestore(&port->lock, irq_flags);
}