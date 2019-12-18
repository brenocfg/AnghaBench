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
struct nwl_msi {int /*<<< orphan*/  lock; int /*<<< orphan*/  bitmap; } ;
struct nwl_pcie {struct nwl_msi msi; } ;
struct irq_domain {int dummy; } ;
struct irq_data {int /*<<< orphan*/  hwirq; } ;

/* Variables and functions */
 int /*<<< orphan*/  bitmap_release_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_count_order (unsigned int) ; 
 struct nwl_pcie* irq_data_get_irq_chip_data (struct irq_data*) ; 
 struct irq_data* irq_domain_get_irq_data (struct irq_domain*,unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nwl_irq_domain_free(struct irq_domain *domain, unsigned int virq,
					unsigned int nr_irqs)
{
	struct irq_data *data = irq_domain_get_irq_data(domain, virq);
	struct nwl_pcie *pcie = irq_data_get_irq_chip_data(data);
	struct nwl_msi *msi = &pcie->msi;

	mutex_lock(&msi->lock);
	bitmap_release_region(msi->bitmap, data->hwirq,
			      get_count_order(nr_irqs));
	mutex_unlock(&msi->lock);
}