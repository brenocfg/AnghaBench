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
struct irq_data {scalar_t__ hwirq; } ;
struct cpumask {int dummy; } ;

/* Variables and functions */
 scalar_t__ HW_IRQ_MX_BASE ; 
 int /*<<< orphan*/  MIROUT (scalar_t__) ; 
 int /*<<< orphan*/  cpu_online_mask ; 
 int cpumask_any_and (struct cpumask const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_of (int) ; 
 int /*<<< orphan*/  irq_data_update_effective_affinity (struct irq_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_er (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xtensa_mx_irq_set_affinity(struct irq_data *d,
		const struct cpumask *dest, bool force)
{
	int cpu = cpumask_any_and(dest, cpu_online_mask);
	unsigned mask = 1u << cpu;

	set_er(mask, MIROUT(d->hwirq - HW_IRQ_MX_BASE));
	irq_data_update_effective_affinity(d, cpumask_of(cpu));

	return 0;

}