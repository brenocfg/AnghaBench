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
typedef  scalar_t__ u32 ;
struct irq_domain {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 scalar_t__ const HW_IRQ_EXTERN_BASE ; 
 int xtensa_irq_domain_xlate (scalar_t__ const*,unsigned int,scalar_t__ const,scalar_t__ const,unsigned long*,unsigned int*) ; 

__attribute__((used)) static int xtensa_mx_irq_domain_xlate(struct irq_domain *d,
		struct device_node *ctrlr,
		const u32 *intspec, unsigned int intsize,
		unsigned long *out_hwirq, unsigned int *out_type)
{
	return xtensa_irq_domain_xlate(intspec, intsize,
			intspec[0], intspec[0] + HW_IRQ_EXTERN_BASE,
			out_hwirq, out_type);
}