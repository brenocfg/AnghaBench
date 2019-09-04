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
 unsigned long* cpu_irq_affinity ; 
 scalar_t__ cpumask_test_cpu (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
cpu_set_irq_affinity(unsigned int irq, cpumask_t affinity)
{
	int cpu;

	for (cpu = 0; cpu < 4; cpu++) {
		unsigned long aff = cpu_irq_affinity[cpu];
		if (cpumask_test_cpu(cpu, &affinity))
			aff |= 1UL << irq;
		else
			aff &= ~(1UL << irq);
		cpu_irq_affinity[cpu] = aff;
	}
}