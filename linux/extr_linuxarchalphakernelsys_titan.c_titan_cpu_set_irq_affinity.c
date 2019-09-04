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
typedef  int /*<<< orphan*/  cpumask_t ;

/* Variables and functions */
 scalar_t__ cpumask_test_cpu (int,int /*<<< orphan*/ *) ; 
 unsigned long* titan_cpu_irq_affinity ; 

__attribute__((used)) static void
titan_cpu_set_irq_affinity(unsigned int irq, cpumask_t affinity)
{
	int cpu;

	for (cpu = 0; cpu < 4; cpu++) {
		if (cpumask_test_cpu(cpu, &affinity))
			titan_cpu_irq_affinity[cpu] |= 1UL << irq;
		else
			titan_cpu_irq_affinity[cpu] &= ~(1UL << irq);
	}

}