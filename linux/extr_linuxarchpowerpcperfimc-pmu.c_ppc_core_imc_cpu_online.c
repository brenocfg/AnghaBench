#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cpumask {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  counter_mem_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  core_imc_cpumask ; 
 int core_imc_mem_init (unsigned int,int /*<<< orphan*/ ) ; 
 TYPE_1__* core_imc_pmu ; 
 struct cpumask* cpu_sibling_mask (unsigned int) ; 
 scalar_t__ cpumask_and (struct cpumask*,struct cpumask const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpumask_set_cpu (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_core_imc_mem_inited (unsigned int) ; 
 int /*<<< orphan*/  pr_info (char*,unsigned int) ; 

__attribute__((used)) static int ppc_core_imc_cpu_online(unsigned int cpu)
{
	const struct cpumask *l_cpumask;
	static struct cpumask tmp_mask;
	int ret = 0;

	/* Get the cpumask for this core */
	l_cpumask = cpu_sibling_mask(cpu);

	/* If a cpu for this core is already set, then, don't do anything */
	if (cpumask_and(&tmp_mask, l_cpumask, &core_imc_cpumask))
		return 0;

	if (!is_core_imc_mem_inited(cpu)) {
		ret = core_imc_mem_init(cpu, core_imc_pmu->counter_mem_size);
		if (ret) {
			pr_info("core_imc memory allocation for cpu %d failed\n", cpu);
			return ret;
		}
	}

	/* set the cpu in the mask */
	cpumask_set_cpu(cpu, &core_imc_cpumask);
	return 0;
}