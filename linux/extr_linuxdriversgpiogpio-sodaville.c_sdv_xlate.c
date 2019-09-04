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
#define  IRQ_TYPE_LEVEL_HIGH 129 
#define  IRQ_TYPE_LEVEL_LOW 128 
 struct device_node* irq_domain_get_of_node (struct irq_domain*) ; 

__attribute__((used)) static int sdv_xlate(struct irq_domain *h, struct device_node *node,
		const u32 *intspec, u32 intsize, irq_hw_number_t *out_hwirq,
		u32 *out_type)
{
	u32 line, type;

	if (node != irq_domain_get_of_node(h))
		return -EINVAL;

	if (intsize < 2)
		return -EINVAL;

	line = *intspec;
	*out_hwirq = line;

	intspec++;
	type = *intspec;

	switch (type) {
	case IRQ_TYPE_LEVEL_LOW:
	case IRQ_TYPE_LEVEL_HIGH:
		*out_type = type;
		break;
	default:
		return -EINVAL;
	}
	return 0;
}