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
 int /*<<< orphan*/  cpu_online_mask ; 
 unsigned int cpumask_first_and (struct cpumask const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_of (unsigned int) ; 
 int /*<<< orphan*/  evtchn_from_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_data_update_effective_affinity (struct irq_data*,int /*<<< orphan*/ ) ; 
 int xen_rebind_evtchn_to_cpu (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int set_affinity_irq(struct irq_data *data, const struct cpumask *dest,
			    bool force)
{
	unsigned tcpu = cpumask_first_and(dest, cpu_online_mask);
	int ret = xen_rebind_evtchn_to_cpu(evtchn_from_irq(data->irq), tcpu);

	if (!ret)
		irq_data_update_effective_affinity(data, cpumask_of(tcpu));

	return ret;
}