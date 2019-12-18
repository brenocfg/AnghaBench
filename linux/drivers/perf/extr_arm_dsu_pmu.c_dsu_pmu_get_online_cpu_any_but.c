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
struct dsu_pmu {int /*<<< orphan*/  associated_cpus; } ;
struct cpumask {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_online_mask ; 
 int /*<<< orphan*/  cpumask_and (struct cpumask*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int cpumask_any_but (struct cpumask*,int) ; 

__attribute__((used)) static int dsu_pmu_get_online_cpu_any_but(struct dsu_pmu *dsu_pmu, int cpu)
{
	struct cpumask online_supported;

	cpumask_and(&online_supported,
			 &dsu_pmu->associated_cpus, cpu_online_mask);
	return cpumask_any_but(&online_supported, cpu);
}