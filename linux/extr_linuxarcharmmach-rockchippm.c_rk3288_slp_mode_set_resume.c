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
 int /*<<< orphan*/  RK3288_PMU_PWRMODE_CON ; 
 int /*<<< orphan*/  RK3288_SGRF_CPU_CON0 ; 
 int /*<<< orphan*/  RK3288_SGRF_SOC_CON0 ; 
 int SGRF_DAPDEVICEEN_WRITE ; 
 int SGRF_FAST_BOOT_EN_WRITE ; 
 int SGRF_PCLK_WDT_GATE_WRITE ; 
 int /*<<< orphan*/  pmu_regmap ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int rk3288_pmu_pwr_mode_con ; 
 int rk3288_sgrf_cpu_con0 ; 
 int rk3288_sgrf_soc_con0 ; 
 int /*<<< orphan*/  sgrf_regmap ; 

__attribute__((used)) static void rk3288_slp_mode_set_resume(void)
{
	regmap_write(sgrf_regmap, RK3288_SGRF_CPU_CON0,
		     rk3288_sgrf_cpu_con0 | SGRF_DAPDEVICEEN_WRITE);

	regmap_write(pmu_regmap, RK3288_PMU_PWRMODE_CON,
		     rk3288_pmu_pwr_mode_con);

	regmap_write(sgrf_regmap, RK3288_SGRF_SOC_CON0,
		     rk3288_sgrf_soc_con0 | SGRF_PCLK_WDT_GATE_WRITE
		     | SGRF_FAST_BOOT_EN_WRITE);
}