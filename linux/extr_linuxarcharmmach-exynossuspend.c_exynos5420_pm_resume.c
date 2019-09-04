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
 scalar_t__ EXYNOS5420_CPU_STATE ; 
 unsigned long EXYNOS5420_EMULATION ; 
 int /*<<< orphan*/  EXYNOS5420_FSYS2_OPTION ; 
 int /*<<< orphan*/  EXYNOS5420_PSGEN_OPTION ; 
 int /*<<< orphan*/  EXYNOS5420_SFR_AXI_CGDIS1 ; 
 unsigned long EXYNOS5420_UFS ; 
 int EXYNOS5420_USE_STANDBY_WFI_ALL ; 
 int /*<<< orphan*/  EXYNOS5_ARM_CORE0_SYS_PWR_REG ; 
 int /*<<< orphan*/  S5P_CENTRAL_SEQ_OPTION ; 
 unsigned long S5P_CORE_LOCAL_PWR_EN ; 
 int /*<<< orphan*/  S5P_INFORM1 ; 
 int /*<<< orphan*/  S5P_PMU_SPARE3 ; 
 int /*<<< orphan*/  exynos5420_cpu_state ; 
 scalar_t__ exynos_pm_central_resume () ; 
 int exynos_pmu_spare3 ; 
 unsigned long pmu_raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmu_raw_writel (int,int /*<<< orphan*/ ) ; 
 scalar_t__ sysram_base_addr ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void exynos5420_pm_resume(void)
{
	unsigned long tmp;

	/* Restore the CPU0 low power state register */
	tmp = pmu_raw_readl(EXYNOS5_ARM_CORE0_SYS_PWR_REG);
	pmu_raw_writel(tmp | S5P_CORE_LOCAL_PWR_EN,
		       EXYNOS5_ARM_CORE0_SYS_PWR_REG);

	/* Restore the sysram cpu state register */
	writel_relaxed(exynos5420_cpu_state,
		       sysram_base_addr + EXYNOS5420_CPU_STATE);

	pmu_raw_writel(EXYNOS5420_USE_STANDBY_WFI_ALL,
			S5P_CENTRAL_SEQ_OPTION);

	if (exynos_pm_central_resume())
		goto early_wakeup;

	pmu_raw_writel(exynos_pmu_spare3, S5P_PMU_SPARE3);

early_wakeup:

	tmp = pmu_raw_readl(EXYNOS5420_SFR_AXI_CGDIS1);
	tmp &= ~EXYNOS5420_UFS;
	pmu_raw_writel(tmp, EXYNOS5420_SFR_AXI_CGDIS1);

	tmp = pmu_raw_readl(EXYNOS5420_FSYS2_OPTION);
	tmp &= ~EXYNOS5420_EMULATION;
	pmu_raw_writel(tmp, EXYNOS5420_FSYS2_OPTION);

	tmp = pmu_raw_readl(EXYNOS5420_PSGEN_OPTION);
	tmp &= ~EXYNOS5420_EMULATION;
	pmu_raw_writel(tmp, EXYNOS5420_PSGEN_OPTION);

	/* Clear SLEEP mode set in INFORM1 */
	pmu_raw_writel(0x0, S5P_INFORM1);
}