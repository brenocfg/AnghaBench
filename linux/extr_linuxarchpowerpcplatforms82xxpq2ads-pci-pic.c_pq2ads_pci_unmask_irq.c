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
struct pq2ads_pci_pic {TYPE_1__* regs; } ;
struct irq_data {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mask; } ;

/* Variables and functions */
 int NUM_IRQS ; 
 int /*<<< orphan*/  clrbits32 (int /*<<< orphan*/ *,int) ; 
 struct pq2ads_pci_pic* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int irqd_to_hwirq (struct irq_data*) ; 
 int /*<<< orphan*/  pci_pic_lock ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void pq2ads_pci_unmask_irq(struct irq_data *d)
{
	struct pq2ads_pci_pic *priv = irq_data_get_irq_chip_data(d);
	int irq = NUM_IRQS - irqd_to_hwirq(d) - 1;

	if (irq != -1) {
		unsigned long flags;

		raw_spin_lock_irqsave(&pci_pic_lock, flags);
		clrbits32(&priv->regs->mask, 1 << irq);
		raw_spin_unlock_irqrestore(&pci_pic_lock, flags);
	}
}