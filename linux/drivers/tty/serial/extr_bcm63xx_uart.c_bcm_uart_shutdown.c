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
struct uart_port {int /*<<< orphan*/  irq; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  UART_IR_REG ; 
 int /*<<< orphan*/  bcm_uart_disable (struct uart_port*) ; 
 int /*<<< orphan*/  bcm_uart_flush (struct uart_port*) ; 
 int /*<<< orphan*/  bcm_uart_writel (struct uart_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct uart_port*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void bcm_uart_shutdown(struct uart_port *port)
{
	unsigned long flags;

	spin_lock_irqsave(&port->lock, flags);
	bcm_uart_writel(port, 0, UART_IR_REG);
	spin_unlock_irqrestore(&port->lock, flags);

	bcm_uart_disable(port);
	bcm_uart_flush(port);
	free_irq(port->irq, port);
}