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
struct gemini_ethernet_port {struct gemini_ethernet* geth; } ;
struct gemini_ethernet {int /*<<< orphan*/  irq_lock; scalar_t__ base; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ GLOBAL_INTERRUPT_ENABLE_4_REG ; 
 scalar_t__ GLOBAL_INTERRUPT_STATUS_4_REG ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 unsigned long SWFQ_EMPTY_INT_BIT ; 
 int /*<<< orphan*/  geth_fill_freeq (struct gemini_ethernet*,int) ; 
 unsigned long readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static irqreturn_t gemini_port_irq_thread(int irq, void *data)
{
	unsigned long irqmask = SWFQ_EMPTY_INT_BIT;
	struct gemini_ethernet_port *port = data;
	struct gemini_ethernet *geth;
	unsigned long flags;

	geth = port->geth;
	/* The queue is half empty so refill it */
	geth_fill_freeq(geth, true);

	spin_lock_irqsave(&geth->irq_lock, flags);
	/* ACK queue interrupt */
	writel(irqmask, geth->base + GLOBAL_INTERRUPT_STATUS_4_REG);
	/* Enable queue interrupt again */
	irqmask |= readl(geth->base + GLOBAL_INTERRUPT_ENABLE_4_REG);
	writel(irqmask, geth->base + GLOBAL_INTERRUPT_ENABLE_4_REG);
	spin_unlock_irqrestore(&geth->irq_lock, flags);

	return IRQ_HANDLED;
}