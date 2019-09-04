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
 unsigned int IRQ_TYPE_LEVEL_HIGH ; 

__attribute__((used)) static int spider_host_xlate(struct irq_domain *h, struct device_node *ct,
			   const u32 *intspec, unsigned int intsize,
			   irq_hw_number_t *out_hwirq, unsigned int *out_flags)

{
	/* Spider interrupts have 2 cells, first is the interrupt source,
	 * second, well, I don't know for sure yet ... We mask the top bits
	 * because old device-trees encode a node number in there
	 */
	*out_hwirq = intspec[0] & 0x3f;
	*out_flags = IRQ_TYPE_LEVEL_HIGH;
	return 0;
}