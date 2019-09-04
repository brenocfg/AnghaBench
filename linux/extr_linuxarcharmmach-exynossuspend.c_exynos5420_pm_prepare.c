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
 int /*<<< orphan*/  EXYNOS5420_ARM_COMMON_OPTION ; 
 scalar_t__ EXYNOS5420_CPU_STATE ; 
 unsigned int EXYNOS5420_EMULATION ; 
 int /*<<< orphan*/  EXYNOS5420_FSYS2_OPTION ; 
 unsigned int EXYNOS5420_L2RSTDISABLE_VALUE ; 
 int /*<<< orphan*/  EXYNOS5420_PSGEN_OPTION ; 
 int /*<<< orphan*/  EXYNOS5420_SFR_AXI_CGDIS1 ; 
 unsigned int EXYNOS5420_UFS ; 
 int /*<<< orphan*/  EXYNOS_L2_OPTION (int /*<<< orphan*/ ) ; 
 unsigned int EXYNOS_L2_USE_RETENTION ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S5P_INFORM0 ; 
 int /*<<< orphan*/  S5P_PMU_SPARE3 ; 
 unsigned int __pa_symbol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exynos5420_cpu_state ; 
 int /*<<< orphan*/  exynos_pm_enter_sleep_mode () ; 
 int /*<<< orphan*/  exynos_pm_set_wakeup_mask () ; 
 void* exynos_pmu_spare3 ; 
 int /*<<< orphan*/  mcpm_entry_point ; 
 void* pmu_raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmu_raw_writel (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 scalar_t__ sysram_base_addr ; 

__attribute__((used)) static void exynos5420_pm_prepare(void)
{
	unsigned int tmp;

	/* Set wake-up mask registers */
	exynos_pm_set_wakeup_mask();

	exynos_pmu_spare3 = pmu_raw_readl(S5P_PMU_SPARE3);
	/*
	 * The cpu state needs to be saved and restored so that the
	 * secondary CPUs will enter low power start. Though the U-Boot
	 * is setting the cpu state with low power flag, the kernel
	 * needs to restore it back in case, the primary cpu fails to
	 * suspend for any reason.
	 */
	exynos5420_cpu_state = readl_relaxed(sysram_base_addr +
					     EXYNOS5420_CPU_STATE);

	exynos_pm_enter_sleep_mode();

	/* ensure at least INFORM0 has the resume address */
	if (IS_ENABLED(CONFIG_EXYNOS5420_MCPM))
		pmu_raw_writel(__pa_symbol(mcpm_entry_point), S5P_INFORM0);

	tmp = pmu_raw_readl(EXYNOS_L2_OPTION(0));
	tmp &= ~EXYNOS_L2_USE_RETENTION;
	pmu_raw_writel(tmp, EXYNOS_L2_OPTION(0));

	tmp = pmu_raw_readl(EXYNOS5420_SFR_AXI_CGDIS1);
	tmp |= EXYNOS5420_UFS;
	pmu_raw_writel(tmp, EXYNOS5420_SFR_AXI_CGDIS1);

	tmp = pmu_raw_readl(EXYNOS5420_ARM_COMMON_OPTION);
	tmp &= ~EXYNOS5420_L2RSTDISABLE_VALUE;
	pmu_raw_writel(tmp, EXYNOS5420_ARM_COMMON_OPTION);

	tmp = pmu_raw_readl(EXYNOS5420_FSYS2_OPTION);
	tmp |= EXYNOS5420_EMULATION;
	pmu_raw_writel(tmp, EXYNOS5420_FSYS2_OPTION);

	tmp = pmu_raw_readl(EXYNOS5420_PSGEN_OPTION);
	tmp |= EXYNOS5420_EMULATION;
	pmu_raw_writel(tmp, EXYNOS5420_PSGEN_OPTION);
}