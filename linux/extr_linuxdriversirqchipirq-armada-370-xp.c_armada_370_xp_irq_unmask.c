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
typedef  int /*<<< orphan*/  irq_hw_number_t ;

/* Variables and functions */
 scalar_t__ ARMADA_370_XP_INT_CLEAR_MASK_OFFS ; 
 scalar_t__ ARMADA_370_XP_INT_SET_ENABLE_OFFS ; 
 int /*<<< orphan*/  irqd_to_hwirq (struct irq_data*) ; 
 int /*<<< orphan*/  is_percpu_irq (int /*<<< orphan*/ ) ; 
 scalar_t__ main_int_base ; 
 scalar_t__ per_cpu_int_base ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void armada_370_xp_irq_unmask(struct irq_data *d)
{
	irq_hw_number_t hwirq = irqd_to_hwirq(d);

	if (!is_percpu_irq(hwirq))
		writel(hwirq, main_int_base +
				ARMADA_370_XP_INT_SET_ENABLE_OFFS);
	else
		writel(hwirq, per_cpu_int_base +
				ARMADA_370_XP_INT_CLEAR_MASK_OFFS);
}