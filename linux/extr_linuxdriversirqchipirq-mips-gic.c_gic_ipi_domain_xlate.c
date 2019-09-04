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
typedef  int /*<<< orphan*/  u32 ;
struct irq_domain {int dummy; } ;
struct device_node {int dummy; } ;
typedef  scalar_t__ irq_hw_number_t ;

/* Variables and functions */
 unsigned int IRQ_TYPE_EDGE_RISING ; 

__attribute__((used)) static int gic_ipi_domain_xlate(struct irq_domain *d, struct device_node *ctrlr,
				const u32 *intspec, unsigned int intsize,
				irq_hw_number_t *out_hwirq,
				unsigned int *out_type)
{
	/*
	 * There's nothing to translate here. hwirq is dynamically allocated and
	 * the irq type is always edge triggered.
	 * */
	*out_hwirq = 0;
	*out_type = IRQ_TYPE_EDGE_RISING;

	return 0;
}