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
struct irq_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  icp_hv_set_xirr (int) ; 
 int /*<<< orphan*/  iosync () ; 
 scalar_t__ irqd_to_hwirq (struct irq_data*) ; 
 int xics_pop_cppr () ; 

__attribute__((used)) static void icp_hv_eoi(struct irq_data *d)
{
	unsigned int hw_irq = (unsigned int)irqd_to_hwirq(d);

	iosync();
	icp_hv_set_xirr((xics_pop_cppr() << 24) | hw_irq);
}