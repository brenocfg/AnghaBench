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
struct irq_data {int /*<<< orphan*/  hwirq; } ;

/* Variables and functions */
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  cpu_online_mask ; 
 unsigned int cpumask_any_and (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_of (unsigned int) ; 
 int /*<<< orphan*/  irq_data_get_affinity_mask (struct irq_data*) ; 
 unsigned int nr_cpu_ids ; 
 int /*<<< orphan*/  plic_irq_toggle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void plic_irq_unmask(struct irq_data *d)
{
	unsigned int cpu = cpumask_any_and(irq_data_get_affinity_mask(d),
					   cpu_online_mask);
	if (WARN_ON_ONCE(cpu >= nr_cpu_ids))
		return;
	plic_irq_toggle(cpumask_of(cpu), d->hwirq, 1);
}