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
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int DUR_WAIT_RESET ; 
 int /*<<< orphan*/  EXYNOS5420_ARM_COMMON_OPTION ; 
 int /*<<< orphan*/  EXYNOS5420_ARM_INTR_SPREAD_ENABLE ; 
 int /*<<< orphan*/  EXYNOS5420_ARM_INTR_SPREAD_USE_STANDBYWFI ; 
 unsigned int EXYNOS5420_ATB_ISP_ARM ; 
 unsigned int EXYNOS5420_ATB_KFC ; 
 int /*<<< orphan*/  EXYNOS5420_KFC_COMMON_OPTION ; 
 int /*<<< orphan*/  EXYNOS5420_LOGIC_RESET_DURATION3 ; 
 int /*<<< orphan*/  EXYNOS5420_LPI_MASK ; 
 int /*<<< orphan*/  EXYNOS5420_LPI_MASK1 ; 
 int /*<<< orphan*/  EXYNOS5420_UP_SCHEDULER ; 
 int EXYNOS5420_USE_STANDBY_WFI_ALL ; 
 unsigned int EXYNOS5_SKIP_DEACTIVATE_ACEACP_IN_PWDN ; 
 int /*<<< orphan*/  EXYNOS_L2_OPTION (int) ; 
 unsigned int EXYNOS_L2_USE_RETENTION ; 
 int /*<<< orphan*/  S5P_CENTRAL_SEQ_OPTION ; 
 int SPREAD_ENABLE ; 
 int SPREAD_USE_STANDWFI ; 
 int /*<<< orphan*/ * exynos5420_list_disable_pmu_reg ; 
 unsigned int pmu_raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmu_raw_writel (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*) ; 

__attribute__((used)) static void exynos5420_pmu_init(void)
{
	unsigned int value;
	int i;

	/*
	 * Set the CMU_RESET, CMU_SYSCLK and CMU_CLKSTOP registers
	 * for local power blocks to Low initially as per Table 8-4:
	 * "System-Level Power-Down Configuration Registers".
	 */
	for (i = 0; i < ARRAY_SIZE(exynos5420_list_disable_pmu_reg); i++)
		pmu_raw_writel(0, exynos5420_list_disable_pmu_reg[i]);

	/* Enable USE_STANDBY_WFI for all CORE */
	pmu_raw_writel(EXYNOS5420_USE_STANDBY_WFI_ALL, S5P_CENTRAL_SEQ_OPTION);

	value  = pmu_raw_readl(EXYNOS_L2_OPTION(0));
	value &= ~EXYNOS_L2_USE_RETENTION;
	pmu_raw_writel(value, EXYNOS_L2_OPTION(0));

	value = pmu_raw_readl(EXYNOS_L2_OPTION(1));
	value &= ~EXYNOS_L2_USE_RETENTION;
	pmu_raw_writel(value, EXYNOS_L2_OPTION(1));

	/*
	 * If L2_COMMON is turned off, clocks related to ATB async
	 * bridge are gated. Thus, when ISP power is gated, LPI
	 * may get stuck.
	 */
	value = pmu_raw_readl(EXYNOS5420_LPI_MASK);
	value |= EXYNOS5420_ATB_ISP_ARM;
	pmu_raw_writel(value, EXYNOS5420_LPI_MASK);

	value  = pmu_raw_readl(EXYNOS5420_LPI_MASK1);
	value |= EXYNOS5420_ATB_KFC;
	pmu_raw_writel(value, EXYNOS5420_LPI_MASK1);

	/* Prevent issue of new bus request from L2 memory */
	value = pmu_raw_readl(EXYNOS5420_ARM_COMMON_OPTION);
	value |= EXYNOS5_SKIP_DEACTIVATE_ACEACP_IN_PWDN;
	pmu_raw_writel(value, EXYNOS5420_ARM_COMMON_OPTION);

	value = pmu_raw_readl(EXYNOS5420_KFC_COMMON_OPTION);
	value |= EXYNOS5_SKIP_DEACTIVATE_ACEACP_IN_PWDN;
	pmu_raw_writel(value, EXYNOS5420_KFC_COMMON_OPTION);

	/* This setting is to reduce suspend/resume time */
	pmu_raw_writel(DUR_WAIT_RESET, EXYNOS5420_LOGIC_RESET_DURATION3);

	/* Serialized CPU wakeup of Eagle */
	pmu_raw_writel(SPREAD_ENABLE, EXYNOS5420_ARM_INTR_SPREAD_ENABLE);

	pmu_raw_writel(SPREAD_USE_STANDWFI,
			EXYNOS5420_ARM_INTR_SPREAD_USE_STANDBYWFI);

	pmu_raw_writel(0x1, EXYNOS5420_UP_SCHEDULER);

	pr_info("EXYNOS5420 PMU initialized\n");
}