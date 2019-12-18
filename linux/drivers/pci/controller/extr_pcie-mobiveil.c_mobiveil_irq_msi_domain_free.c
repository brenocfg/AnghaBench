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
struct mobiveil_msi {int /*<<< orphan*/  lock; int /*<<< orphan*/  msi_irq_in_use; } ;
struct mobiveil_pcie {TYPE_1__* pdev; struct mobiveil_msi msi; } ;
struct irq_domain {int dummy; } ;
struct irq_data {int /*<<< orphan*/  hwirq; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct mobiveil_pcie* irq_data_get_irq_chip_data (struct irq_data*) ; 
 struct irq_data* irq_domain_get_irq_data (struct irq_domain*,unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mobiveil_irq_msi_domain_free(struct irq_domain *domain,
					 unsigned int virq,
					 unsigned int nr_irqs)
{
	struct irq_data *d = irq_domain_get_irq_data(domain, virq);
	struct mobiveil_pcie *pcie = irq_data_get_irq_chip_data(d);
	struct mobiveil_msi *msi = &pcie->msi;

	mutex_lock(&msi->lock);

	if (!test_bit(d->hwirq, msi->msi_irq_in_use))
		dev_err(&pcie->pdev->dev, "trying to free unused MSI#%lu\n",
			d->hwirq);
	else
		__clear_bit(d->hwirq, msi->msi_irq_in_use);

	mutex_unlock(&msi->lock);
}