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
typedef  size_t u32 ;
struct irq_domain {struct evic_chip_data* host_data; } ;
struct evic_chip_data {size_t* irq_types; } ;
struct device_node {int dummy; } ;
typedef  size_t irq_hw_number_t ;

/* Variables and functions */
 int EINVAL ; 
 size_t const IRQ_TYPE_SENSE_MASK ; 
 size_t const NR_IRQS ; 
 scalar_t__ WARN_ON (int) ; 

int pic32_irq_domain_xlate(struct irq_domain *d, struct device_node *ctrlr,
			   const u32 *intspec, unsigned int intsize,
			   irq_hw_number_t *out_hwirq, unsigned int *out_type)
{
	struct evic_chip_data *priv = d->host_data;

	if (WARN_ON(intsize < 2))
		return -EINVAL;

	if (WARN_ON(intspec[0] >= NR_IRQS))
		return -EINVAL;

	*out_hwirq = intspec[0];
	*out_type = intspec[1] & IRQ_TYPE_SENSE_MASK;

	priv->irq_types[intspec[0]] = intspec[1] & IRQ_TYPE_SENSE_MASK;

	return 0;
}