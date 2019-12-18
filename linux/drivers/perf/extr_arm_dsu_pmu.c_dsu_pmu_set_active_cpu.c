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
struct dsu_pmu {int /*<<< orphan*/  active_cpu; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpumask_set_cpu (int,int /*<<< orphan*/ *) ; 
 scalar_t__ irq_set_affinity_hint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 

__attribute__((used)) static void dsu_pmu_set_active_cpu(int cpu, struct dsu_pmu *dsu_pmu)
{
	cpumask_set_cpu(cpu, &dsu_pmu->active_cpu);
	if (irq_set_affinity_hint(dsu_pmu->irq, &dsu_pmu->active_cpu))
		pr_warn("Failed to set irq affinity to %d\n", cpu);
}