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
struct irq_domain {struct alpine_msix_data* host_data; } ;
struct alpine_msix_data {int dummy; } ;

/* Variables and functions */
 int alpine_msix_allocate_sgi (struct alpine_msix_data*,unsigned int) ; 
 int /*<<< orphan*/  alpine_msix_free_sgi (struct alpine_msix_data*,int,unsigned int) ; 
 int alpine_msix_gic_domain_alloc (struct irq_domain*,unsigned int,int) ; 
 int /*<<< orphan*/  irq_domain_free_irqs_parent (struct irq_domain*,unsigned int,int) ; 
 int /*<<< orphan*/  irq_domain_set_hwirq_and_chip (struct irq_domain*,unsigned int,int,int /*<<< orphan*/ *,struct alpine_msix_data*) ; 
 int /*<<< orphan*/  middle_irq_chip ; 

__attribute__((used)) static int alpine_msix_middle_domain_alloc(struct irq_domain *domain,
					   unsigned int virq,
					   unsigned int nr_irqs, void *args)
{
	struct alpine_msix_data *priv = domain->host_data;
	int sgi, err, i;

	sgi = alpine_msix_allocate_sgi(priv, nr_irqs);
	if (sgi < 0)
		return sgi;

	for (i = 0; i < nr_irqs; i++) {
		err = alpine_msix_gic_domain_alloc(domain, virq + i, sgi + i);
		if (err)
			goto err_sgi;

		irq_domain_set_hwirq_and_chip(domain, virq + i, sgi + i,
					      &middle_irq_chip, priv);
	}

	return 0;

err_sgi:
	while (--i >= 0)
		irq_domain_free_irqs_parent(domain, virq, i);
	alpine_msix_free_sgi(priv, sgi, nr_irqs);
	return err;
}