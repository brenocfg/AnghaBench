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

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_EXYNOS5420_MCPM ; 
 scalar_t__ EXYNOS5420_CPU_STATE ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 unsigned int MPIDR_AFFINITY_LEVEL (unsigned int,int) ; 
 int /*<<< orphan*/  exynos_cpu_resume ; 
 int /*<<< orphan*/  mcpm_cpu_suspend () ; 
 int /*<<< orphan*/  mcpm_set_entry_vector (unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 unsigned int read_cpuid_mpidr () ; 
 scalar_t__ sysram_base_addr ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int exynos5420_cpu_suspend(unsigned long arg)
{
	/* MCPM works with HW CPU identifiers */
	unsigned int mpidr = read_cpuid_mpidr();
	unsigned int cluster = MPIDR_AFFINITY_LEVEL(mpidr, 1);
	unsigned int cpu = MPIDR_AFFINITY_LEVEL(mpidr, 0);

	writel_relaxed(0x0, sysram_base_addr + EXYNOS5420_CPU_STATE);

	if (IS_ENABLED(CONFIG_EXYNOS5420_MCPM)) {
		mcpm_set_entry_vector(cpu, cluster, exynos_cpu_resume);
		mcpm_cpu_suspend();
	}

	pr_info("Failed to suspend the system\n");

	/* return value != 0 means failure */
	return 1;
}