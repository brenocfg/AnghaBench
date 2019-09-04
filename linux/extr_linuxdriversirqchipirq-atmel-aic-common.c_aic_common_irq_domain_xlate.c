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
typedef  unsigned int u32 ;
struct irq_domain {int dummy; } ;
struct device_node {int dummy; } ;
typedef  unsigned int irq_hw_number_t ;

/* Variables and functions */
 unsigned int const AT91_AIC_IRQ_MAX_PRIORITY ; 
 unsigned int const AT91_AIC_IRQ_MIN_PRIORITY ; 
 int EINVAL ; 
 unsigned int const IRQ_TYPE_SENSE_MASK ; 
 scalar_t__ WARN_ON (int) ; 

int aic_common_irq_domain_xlate(struct irq_domain *d,
				struct device_node *ctrlr,
				const u32 *intspec,
				unsigned int intsize,
				irq_hw_number_t *out_hwirq,
				unsigned int *out_type)
{
	if (WARN_ON(intsize < 3))
		return -EINVAL;

	if (WARN_ON((intspec[2] < AT91_AIC_IRQ_MIN_PRIORITY) ||
		    (intspec[2] > AT91_AIC_IRQ_MAX_PRIORITY)))
		return -EINVAL;

	*out_hwirq = intspec[0];
	*out_type = intspec[1] & IRQ_TYPE_SENSE_MASK;

	return 0;
}