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
struct TYPE_2__ {int /*<<< orphan*/  (* cpu_is_up ) (unsigned int,unsigned int) ;int /*<<< orphan*/  (* cluster_is_up ) (unsigned int) ;} ;

/* Variables and functions */
 int EUNATCH ; 
 unsigned int MPIDR_AFFINITY_LEVEL (unsigned int,int) ; 
 int /*<<< orphan*/  arch_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arch_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int mcpm_cluster_unused (unsigned int) ; 
 int** mcpm_cpu_use_count ; 
 int /*<<< orphan*/  mcpm_lock ; 
 TYPE_1__* platform_ops ; 
 unsigned int read_cpuid_mpidr () ; 
 int /*<<< orphan*/  stub1 (unsigned int) ; 
 int /*<<< orphan*/  stub2 (unsigned int,unsigned int) ; 

int mcpm_cpu_powered_up(void)
{
	unsigned int mpidr, cpu, cluster;
	bool cpu_was_down, first_man;
	unsigned long flags;

	if (!platform_ops)
		return -EUNATCH;

	mpidr = read_cpuid_mpidr();
	cpu = MPIDR_AFFINITY_LEVEL(mpidr, 0);
	cluster = MPIDR_AFFINITY_LEVEL(mpidr, 1);
	local_irq_save(flags);
	arch_spin_lock(&mcpm_lock);

	cpu_was_down = !mcpm_cpu_use_count[cluster][cpu];
	first_man = mcpm_cluster_unused(cluster);

	if (first_man && platform_ops->cluster_is_up)
		platform_ops->cluster_is_up(cluster);
	if (cpu_was_down)
		mcpm_cpu_use_count[cluster][cpu] = 1;
	if (platform_ops->cpu_is_up)
		platform_ops->cpu_is_up(cpu, cluster);

	arch_spin_unlock(&mcpm_lock);
	local_irq_restore(flags);

	return 0;
}