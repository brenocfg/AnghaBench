#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct irq_data {size_t hwirq; scalar_t__ irq; } ;
struct TYPE_3__ {int /*<<< orphan*/  dbb_irqs; } ;
struct TYPE_4__ {int /*<<< orphan*/  mask_work; int /*<<< orphan*/  dbb_irqs_lock; TYPE_1__ req; } ;

/* Variables and functions */
 scalar_t__ IRQ_PRCMU_CA_SLEEP ; 
 TYPE_2__ mb0_transfer ; 
 int /*<<< orphan*/ * prcmu_irq_bit ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void prcmu_irq_mask(struct irq_data *d)
{
	unsigned long flags;

	spin_lock_irqsave(&mb0_transfer.dbb_irqs_lock, flags);

	mb0_transfer.req.dbb_irqs &= ~prcmu_irq_bit[d->hwirq];

	spin_unlock_irqrestore(&mb0_transfer.dbb_irqs_lock, flags);

	if (d->irq != IRQ_PRCMU_CA_SLEEP)
		schedule_work(&mb0_transfer.mask_work);
}