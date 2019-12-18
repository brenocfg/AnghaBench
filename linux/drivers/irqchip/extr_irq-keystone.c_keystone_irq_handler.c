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
struct keystone_irq_device {unsigned long mask; int /*<<< orphan*/  dev; int /*<<< orphan*/  wa_lock; int /*<<< orphan*/  irqd; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 unsigned long BIT (int) ; 
 unsigned long BIT_OFS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int KEYSTONE_N_IRQ ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  generic_handle_irq (int) ; 
 int irq_find_mapping (int /*<<< orphan*/ ,int) ; 
 unsigned long keystone_irq_readl (struct keystone_irq_device*) ; 
 int /*<<< orphan*/  keystone_irq_writel (struct keystone_irq_device*,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t keystone_irq_handler(int irq, void *keystone_irq)
{
	struct keystone_irq_device *kirq = keystone_irq;
	unsigned long wa_lock_flags;
	unsigned long pending;
	int src, virq;

	dev_dbg(kirq->dev, "start irq %d\n", irq);

	pending = keystone_irq_readl(kirq);
	keystone_irq_writel(kirq, pending);

	dev_dbg(kirq->dev, "pending 0x%lx, mask 0x%x\n", pending, kirq->mask);

	pending = (pending >> BIT_OFS) & ~kirq->mask;

	dev_dbg(kirq->dev, "pending after mask 0x%lx\n", pending);

	for (src = 0; src < KEYSTONE_N_IRQ; src++) {
		if (BIT(src) & pending) {
			virq = irq_find_mapping(kirq->irqd, src);
			dev_dbg(kirq->dev, "dispatch bit %d, virq %d\n",
				src, virq);
			if (!virq)
				dev_warn(kirq->dev, "spurious irq detected hwirq %d, virq %d\n",
					 src, virq);
			raw_spin_lock_irqsave(&kirq->wa_lock, wa_lock_flags);
			generic_handle_irq(virq);
			raw_spin_unlock_irqrestore(&kirq->wa_lock,
						   wa_lock_flags);
		}
	}

	dev_dbg(kirq->dev, "end irq %d\n", irq);
	return IRQ_HANDLED;
}