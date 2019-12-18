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
struct ls_scfg_msi {int irqs_num; int /*<<< orphan*/  lock; int /*<<< orphan*/  used; } ;
struct irq_domain {int dummy; } ;
struct irq_data {int hwirq; } ;

/* Variables and functions */
 int /*<<< orphan*/  __clear_bit (int,int /*<<< orphan*/ ) ; 
 struct ls_scfg_msi* irq_data_get_irq_chip_data (struct irq_data*) ; 
 struct irq_data* irq_domain_get_irq_data (struct irq_domain*,unsigned int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ls_scfg_msi_domain_irq_free(struct irq_domain *domain,
				   unsigned int virq, unsigned int nr_irqs)
{
	struct irq_data *d = irq_domain_get_irq_data(domain, virq);
	struct ls_scfg_msi *msi_data = irq_data_get_irq_chip_data(d);
	int pos;

	pos = d->hwirq;
	if (pos < 0 || pos >= msi_data->irqs_num) {
		pr_err("failed to teardown msi. Invalid hwirq %d\n", pos);
		return;
	}

	spin_lock(&msi_data->lock);
	__clear_bit(pos, msi_data->used);
	spin_unlock(&msi_data->lock);
}