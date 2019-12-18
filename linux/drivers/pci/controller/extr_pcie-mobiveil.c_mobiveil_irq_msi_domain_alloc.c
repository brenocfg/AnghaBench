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
struct mobiveil_msi {unsigned long num_of_vectors; int /*<<< orphan*/  lock; int /*<<< orphan*/  msi_irq_in_use; } ;
struct mobiveil_pcie {struct mobiveil_msi msi; } ;
struct irq_domain {struct mobiveil_pcie* host_data; } ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 unsigned long find_first_zero_bit (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  handle_level_irq ; 
 int /*<<< orphan*/  irq_domain_set_info (struct irq_domain*,unsigned int,unsigned long,int /*<<< orphan*/ *,struct mobiveil_pcie*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mobiveil_msi_bottom_irq_chip ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mobiveil_irq_msi_domain_alloc(struct irq_domain *domain,
					 unsigned int virq,
					 unsigned int nr_irqs, void *args)
{
	struct mobiveil_pcie *pcie = domain->host_data;
	struct mobiveil_msi *msi = &pcie->msi;
	unsigned long bit;

	WARN_ON(nr_irqs != 1);
	mutex_lock(&msi->lock);

	bit = find_first_zero_bit(msi->msi_irq_in_use, msi->num_of_vectors);
	if (bit >= msi->num_of_vectors) {
		mutex_unlock(&msi->lock);
		return -ENOSPC;
	}

	set_bit(bit, msi->msi_irq_in_use);

	mutex_unlock(&msi->lock);

	irq_domain_set_info(domain, virq, bit, &mobiveil_msi_bottom_irq_chip,
			    domain->host_data, handle_level_irq, NULL, NULL);
	return 0;
}