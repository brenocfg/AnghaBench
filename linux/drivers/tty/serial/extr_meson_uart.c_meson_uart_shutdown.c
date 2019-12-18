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
typedef  int u32 ;
struct uart_port {int /*<<< orphan*/  lock; scalar_t__ membase; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 scalar_t__ AML_UART_CONTROL ; 
 int AML_UART_RX_EN ; 
 int AML_UART_RX_INT_EN ; 
 int AML_UART_TX_INT_EN ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct uart_port*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void meson_uart_shutdown(struct uart_port *port)
{
	unsigned long flags;
	u32 val;

	free_irq(port->irq, port);

	spin_lock_irqsave(&port->lock, flags);

	val = readl(port->membase + AML_UART_CONTROL);
	val &= ~AML_UART_RX_EN;
	val &= ~(AML_UART_RX_INT_EN | AML_UART_TX_INT_EN);
	writel(val, port->membase + AML_UART_CONTROL);

	spin_unlock_irqrestore(&port->lock, flags);
}