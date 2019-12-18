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
struct uart_port {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; scalar_t__ membase; } ;

/* Variables and functions */
 unsigned long LINFLEXD_LINIER_DRIE ; 
 unsigned long LINFLEXD_LINIER_DTIE ; 
 scalar_t__ LINIER ; 
 int /*<<< orphan*/  devm_free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uart_port*) ; 
 unsigned long readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static void linflex_shutdown(struct uart_port *port)
{
	unsigned long ier;
	unsigned long flags;

	spin_lock_irqsave(&port->lock, flags);

	/* disable interrupts */
	ier = readl(port->membase + LINIER);
	ier &= ~(LINFLEXD_LINIER_DRIE | LINFLEXD_LINIER_DTIE);
	writel(ier, port->membase + LINIER);

	spin_unlock_irqrestore(&port->lock, flags);

	devm_free_irq(port->dev, port->irq, port);
}