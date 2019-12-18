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
struct irq_domain {struct advk_pcie* host_data; } ;
struct irq_data {int /*<<< orphan*/  hwirq; } ;
struct advk_pcie {int /*<<< orphan*/  msi_used_lock; int /*<<< orphan*/  msi_used; } ;

/* Variables and functions */
 int /*<<< orphan*/  bitmap_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 struct irq_data* irq_domain_get_irq_data (struct irq_domain*,unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void advk_msi_irq_domain_free(struct irq_domain *domain,
				     unsigned int virq, unsigned int nr_irqs)
{
	struct irq_data *d = irq_domain_get_irq_data(domain, virq);
	struct advk_pcie *pcie = domain->host_data;

	mutex_lock(&pcie->msi_used_lock);
	bitmap_clear(pcie->msi_used, d->hwirq, nr_irqs);
	mutex_unlock(&pcie->msi_used_lock);
}