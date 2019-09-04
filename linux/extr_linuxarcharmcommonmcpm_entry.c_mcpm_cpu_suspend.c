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
struct TYPE_2__ {int /*<<< orphan*/  (* cpu_suspend_prepare ) (unsigned int,unsigned int) ;} ;

/* Variables and functions */
 unsigned int MPIDR_AFFINITY_LEVEL (unsigned int,int) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  arch_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arch_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mcpm_cpu_power_down () ; 
 int /*<<< orphan*/  mcpm_lock ; 
 TYPE_1__* platform_ops ; 
 unsigned int read_cpuid_mpidr () ; 
 int /*<<< orphan*/  stub1 (unsigned int,unsigned int) ; 

void mcpm_cpu_suspend(void)
{
	if (WARN_ON_ONCE(!platform_ops))
		return;

	/* Some platforms might have to enable special resume modes, etc. */
	if (platform_ops->cpu_suspend_prepare) {
		unsigned int mpidr = read_cpuid_mpidr();
		unsigned int cpu = MPIDR_AFFINITY_LEVEL(mpidr, 0);
		unsigned int cluster = MPIDR_AFFINITY_LEVEL(mpidr, 1); 
		arch_spin_lock(&mcpm_lock);
		platform_ops->cpu_suspend_prepare(cpu, cluster);
		arch_spin_unlock(&mcpm_lock);
	}
	mcpm_cpu_power_down();
}