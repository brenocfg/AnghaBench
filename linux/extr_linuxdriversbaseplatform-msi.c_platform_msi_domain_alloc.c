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
struct platform_msi_priv_data {int /*<<< orphan*/  arg; int /*<<< orphan*/  dev; } ;
struct irq_domain {int /*<<< orphan*/  parent; struct platform_msi_priv_data* host_data; } ;

/* Variables and functions */
 int msi_domain_populate_irqs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ *) ; 
 int platform_msi_alloc_descs_with_irq (int /*<<< orphan*/ ,unsigned int,unsigned int,struct platform_msi_priv_data*) ; 
 int /*<<< orphan*/  platform_msi_domain_free (struct irq_domain*,unsigned int,unsigned int) ; 

int platform_msi_domain_alloc(struct irq_domain *domain, unsigned int virq,
			      unsigned int nr_irqs)
{
	struct platform_msi_priv_data *data = domain->host_data;
	int err;

	err = platform_msi_alloc_descs_with_irq(data->dev, virq, nr_irqs, data);
	if (err)
		return err;

	err = msi_domain_populate_irqs(domain->parent, data->dev,
				       virq, nr_irqs, &data->arg);
	if (err)
		platform_msi_domain_free(domain, virq, nr_irqs);

	return err;
}