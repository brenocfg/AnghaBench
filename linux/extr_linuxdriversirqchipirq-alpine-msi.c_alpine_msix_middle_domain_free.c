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
struct alpine_msix_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  alpine_msix_free_sgi (struct alpine_msix_data*,int /*<<< orphan*/ ,unsigned int) ; 
 struct alpine_msix_data* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  irq_domain_free_irqs_parent (struct irq_domain*,unsigned int,unsigned int) ; 
 struct irq_data* irq_domain_get_irq_data (struct irq_domain*,unsigned int) ; 

__attribute__((used)) static void alpine_msix_middle_domain_free(struct irq_domain *domain,
					   unsigned int virq,
					   unsigned int nr_irqs)
{
	struct irq_data *d = irq_domain_get_irq_data(domain, virq);
	struct alpine_msix_data *priv = irq_data_get_irq_chip_data(d);

	irq_domain_free_irqs_parent(domain, virq, nr_irqs);
	alpine_msix_free_sgi(priv, d->hwirq, nr_irqs);
}