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
struct irq_data {int hwirq; } ;

/* Variables and functions */
 int NODMIS_PER_FRAME ; 
 int /*<<< orphan*/  __clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_domain_free_irqs_parent (struct irq_domain*,unsigned int,unsigned int) ; 
 struct irq_data* irq_domain_get_irq_data (struct irq_domain*,unsigned int) ; 
 int /*<<< orphan*/  odmis_bm ; 
 int /*<<< orphan*/  odmis_bm_lock ; 
 int odmis_count ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void odmi_irq_domain_free(struct irq_domain *domain,
				 unsigned int virq, unsigned int nr_irqs)
{
	struct irq_data *d = irq_domain_get_irq_data(domain, virq);

	if (d->hwirq >= odmis_count * NODMIS_PER_FRAME) {
		pr_err("Failed to teardown msi. Invalid hwirq %lu\n", d->hwirq);
		return;
	}

	irq_domain_free_irqs_parent(domain, virq, nr_irqs);

	/* Actually free the MSI */
	spin_lock(&odmis_bm_lock);
	__clear_bit(d->hwirq, odmis_bm);
	spin_unlock(&odmis_bm_lock);
}