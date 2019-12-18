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
struct irq_domain {int dummy; } ;
struct irq_data {int /*<<< orphan*/  hwirq; } ;
struct iproc_msi {int /*<<< orphan*/  bitmap_lock; int /*<<< orphan*/  nr_cpus; int /*<<< orphan*/  bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  bitmap_clear (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int hwirq_to_canonical_hwirq (struct iproc_msi*,int /*<<< orphan*/ ) ; 
 struct iproc_msi* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  irq_domain_free_irqs_parent (struct irq_domain*,unsigned int,unsigned int) ; 
 struct irq_data* irq_domain_get_irq_data (struct irq_domain*,unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iproc_msi_irq_domain_free(struct irq_domain *domain,
				      unsigned int virq, unsigned int nr_irqs)
{
	struct irq_data *data = irq_domain_get_irq_data(domain, virq);
	struct iproc_msi *msi = irq_data_get_irq_chip_data(data);
	unsigned int hwirq;

	mutex_lock(&msi->bitmap_lock);

	hwirq = hwirq_to_canonical_hwirq(msi, data->hwirq);
	bitmap_clear(msi->bitmap, hwirq, msi->nr_cpus);

	mutex_unlock(&msi->bitmap_lock);

	irq_domain_free_irqs_parent(domain, virq, nr_irqs);
}