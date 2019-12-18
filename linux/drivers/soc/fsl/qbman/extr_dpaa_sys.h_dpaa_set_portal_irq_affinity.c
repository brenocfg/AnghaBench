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
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  cpu_online (int) ; 
 int /*<<< orphan*/  cpu_online_mask ; 
 int cpumask_any (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_of (int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  irq_can_set_affinity (int) ; 
 int irq_set_affinity (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int dpaa_set_portal_irq_affinity(struct device *dev,
					       int irq, int cpu)
{
	int ret = 0;

	if (!irq_can_set_affinity(irq)) {
		dev_err(dev, "unable to set IRQ affinity\n");
		return -EINVAL;
	}

	if (cpu == -1 || !cpu_online(cpu))
		cpu = cpumask_any(cpu_online_mask);

	ret = irq_set_affinity(irq, cpumask_of(cpu));
	if (ret)
		dev_err(dev, "irq_set_affinity() on CPU %d failed\n", cpu);

	return ret;
}