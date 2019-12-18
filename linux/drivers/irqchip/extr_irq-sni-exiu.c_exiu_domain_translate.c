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
struct irq_fwspec {int param_count; scalar_t__* param; int /*<<< orphan*/  fwnode; } ;
struct irq_domain {struct exiu_irq_data* host_data; } ;
struct exiu_irq_data {unsigned long spi_base; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ GIC_SPI ; 
 unsigned int IRQ_TYPE_SENSE_MASK ; 
 scalar_t__ is_of_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int exiu_domain_translate(struct irq_domain *domain,
				 struct irq_fwspec *fwspec,
				 unsigned long *hwirq,
				 unsigned int *type)
{
	struct exiu_irq_data *info = domain->host_data;

	if (is_of_node(fwspec->fwnode)) {
		if (fwspec->param_count != 3)
			return -EINVAL;

		if (fwspec->param[0] != GIC_SPI)
			return -EINVAL; /* No PPI should point to this domain */

		*hwirq = fwspec->param[1] - info->spi_base;
		*type = fwspec->param[2] & IRQ_TYPE_SENSE_MASK;
	} else {
		if (fwspec->param_count != 2)
			return -EINVAL;
		*hwirq = fwspec->param[0];
		*type = fwspec->param[2] & IRQ_TYPE_SENSE_MASK;
	}
	return 0;
}