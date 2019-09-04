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
struct irq_data {size_t hwirq; } ;
struct bcm7038_l1_chip {int /*<<< orphan*/  lock; int /*<<< orphan*/ * affinity; } ;

/* Variables and functions */
 int /*<<< orphan*/  __bcm7038_l1_unmask (struct irq_data*,int /*<<< orphan*/ ) ; 
 struct bcm7038_l1_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void bcm7038_l1_unmask(struct irq_data *d)
{
	struct bcm7038_l1_chip *intc = irq_data_get_irq_chip_data(d);
	unsigned long flags;

	raw_spin_lock_irqsave(&intc->lock, flags);
	__bcm7038_l1_unmask(d, intc->affinity[d->hwirq]);
	raw_spin_unlock_irqrestore(&intc->lock, flags);
}