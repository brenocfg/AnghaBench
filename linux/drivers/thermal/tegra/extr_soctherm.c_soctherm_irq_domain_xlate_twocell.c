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
typedef  int u32 ;
struct irq_domain {int dummy; } ;
struct device_node {int dummy; } ;
typedef  int irq_hw_number_t ;

/* Variables and functions */
 int EINVAL ; 
 int const IRQ_TYPE_SENSE_MASK ; 
 scalar_t__ WARN_ON (int) ; 

__attribute__((used)) static int soctherm_irq_domain_xlate_twocell(struct irq_domain *d,
	struct device_node *ctrlr, const u32 *intspec, unsigned int intsize,
	irq_hw_number_t *out_hwirq, unsigned int *out_type)
{
	if (WARN_ON(intsize < 2))
		return -EINVAL;

	/*
	 * The HW value is 1 index less than the DT IRQ values.
	 * i.e. OC4 goes to HW index 3.
	 */
	*out_hwirq = intspec[0] - 1;
	*out_type = intspec[1] & IRQ_TYPE_SENSE_MASK;
	return 0;
}