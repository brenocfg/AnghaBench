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
struct uart_port {int /*<<< orphan*/  irq; int /*<<< orphan*/  lock; scalar_t__ membase; } ;

/* Variables and functions */
 scalar_t__ CDNS_UART_CR ; 
 int CDNS_UART_CR_RX_DIS ; 
 int CDNS_UART_CR_TX_DIS ; 
 scalar_t__ CDNS_UART_IDR ; 
 scalar_t__ CDNS_UART_IMR ; 
 scalar_t__ CDNS_UART_ISR ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct uart_port*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void cdns_uart_shutdown(struct uart_port *port)
{
	int status;
	unsigned long flags;

	spin_lock_irqsave(&port->lock, flags);

	/* Disable interrupts */
	status = readl(port->membase + CDNS_UART_IMR);
	writel(status, port->membase + CDNS_UART_IDR);
	writel(0xffffffff, port->membase + CDNS_UART_ISR);

	/* Disable the TX and RX */
	writel(CDNS_UART_CR_TX_DIS | CDNS_UART_CR_RX_DIS,
			port->membase + CDNS_UART_CR);

	spin_unlock_irqrestore(&port->lock, flags);

	free_irq(port->irq, port);
}