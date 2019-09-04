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
struct irq_data {int /*<<< orphan*/  irq; } ;
struct cpumask {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int assign_managed_vector (struct irq_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_online_mask ; 
 int /*<<< orphan*/  cpumask_and (int /*<<< orphan*/ ,struct cpumask const*,int /*<<< orphan*/ ) ; 
 int cpumask_empty (int /*<<< orphan*/ ) ; 
 struct cpumask* irq_data_get_affinity_mask (struct irq_data*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vector_searchmask ; 

__attribute__((used)) static int activate_managed(struct irq_data *irqd)
{
	const struct cpumask *dest = irq_data_get_affinity_mask(irqd);
	int ret;

	cpumask_and(vector_searchmask, dest, cpu_online_mask);
	if (WARN_ON_ONCE(cpumask_empty(vector_searchmask))) {
		/* Something in the core code broke! Survive gracefully */
		pr_err("Managed startup for irq %u, but no CPU\n", irqd->irq);
		return -EINVAL;
	}

	ret = assign_managed_vector(irqd, vector_searchmask);
	/*
	 * This should not happen. The vector reservation got buggered.  Handle
	 * it gracefully.
	 */
	if (WARN_ON_ONCE(ret < 0)) {
		pr_err("Managed startup irq %u, no vector available\n",
		       irqd->irq);
	}
	return ret;
}