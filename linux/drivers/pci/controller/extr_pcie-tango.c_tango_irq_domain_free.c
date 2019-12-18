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
struct tango_pcie {int /*<<< orphan*/  used_msi_lock; int /*<<< orphan*/  used_msi; } ;
struct irq_domain {int dummy; } ;
struct irq_data {int /*<<< orphan*/  hwirq; struct tango_pcie* chip_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct irq_data* irq_domain_get_irq_data (struct irq_domain*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void tango_irq_domain_free(struct irq_domain *dom, unsigned int virq,
				  unsigned int nr_irqs)
{
	unsigned long flags;
	struct irq_data *d = irq_domain_get_irq_data(dom, virq);
	struct tango_pcie *pcie = d->chip_data;

	spin_lock_irqsave(&pcie->used_msi_lock, flags);
	__clear_bit(d->hwirq, pcie->used_msi);
	spin_unlock_irqrestore(&pcie->used_msi_lock, flags);
}