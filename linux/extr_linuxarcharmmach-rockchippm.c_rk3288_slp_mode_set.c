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
typedef  int u32 ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMU_ALIVE_USE_LF ; 
 int PMU_ARMINT_WAKEUP_EN ; 
 int /*<<< orphan*/  PMU_BUS_PD_EN ; 
 int /*<<< orphan*/  PMU_CHIP_PD_EN ; 
 int /*<<< orphan*/  PMU_CLK_CORE_SRC_GATE_EN ; 
 int /*<<< orphan*/  PMU_CLR_ALIVE ; 
 int /*<<< orphan*/  PMU_CLR_BUS ; 
 int /*<<< orphan*/  PMU_CLR_CORE ; 
 int /*<<< orphan*/  PMU_CLR_CPUP ; 
 int /*<<< orphan*/  PMU_CLR_DMA ; 
 int /*<<< orphan*/  PMU_CLR_PERI ; 
 int /*<<< orphan*/  PMU_DDR0IO_RET_EN ; 
 int /*<<< orphan*/  PMU_DDR0_GATING_EN ; 
 int /*<<< orphan*/  PMU_DDR1IO_RET_EN ; 
 int /*<<< orphan*/  PMU_DDR1_GATING_EN ; 
 int /*<<< orphan*/  PMU_GLOBAL_INT_DISABLE ; 
 int PMU_GPIOINT_WAKEUP_EN ; 
 int /*<<< orphan*/  PMU_L2FLUSH_EN ; 
 int /*<<< orphan*/  PMU_OSC_24M_DIS ; 
 int /*<<< orphan*/  PMU_PLL_PD_EN ; 
 int /*<<< orphan*/  PMU_PMU_USE_LF ; 
 int /*<<< orphan*/  PMU_PWR_MODE_EN ; 
 int /*<<< orphan*/  PMU_SCU_EN ; 
 int /*<<< orphan*/  PMU_SREF0_ENTER_EN ; 
 int /*<<< orphan*/  PMU_SREF1_ENTER_EN ; 
 int /*<<< orphan*/  RK3288_PMU_OSC_CNT ; 
 int /*<<< orphan*/  RK3288_PMU_PWRMODE_CON ; 
 int /*<<< orphan*/  RK3288_PMU_PWRMODE_CON1 ; 
 int /*<<< orphan*/  RK3288_PMU_STABL_CNT ; 
 int /*<<< orphan*/  RK3288_PMU_WAKEUP_CFG1 ; 
 int /*<<< orphan*/  RK3288_SGRF_CPU_CON0 ; 
 int /*<<< orphan*/  RK3288_SGRF_FAST_BOOT_ADDR ; 
 int /*<<< orphan*/  RK3288_SGRF_SOC_CON0 ; 
 int ROCKCHIP_ARM_OFF_LOGIC_DEEP ; 
 int SGRF_DAPDEVICEEN_WRITE ; 
 int SGRF_FAST_BOOT_EN ; 
 int SGRF_FAST_BOOT_EN_WRITE ; 
 int SGRF_PCLK_WDT_GATE ; 
 int SGRF_PCLK_WDT_GATE_WRITE ; 
 int /*<<< orphan*/  pmu_regmap ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int rk3288_bootram_phy ; 
 int /*<<< orphan*/  rk3288_pmu_pwr_mode_con ; 
 int /*<<< orphan*/  rk3288_sgrf_cpu_con0 ; 
 int /*<<< orphan*/  rk3288_sgrf_soc_con0 ; 
 int rk3288_slp_disable_osc () ; 
 int /*<<< orphan*/  sgrf_regmap ; 

__attribute__((used)) static void rk3288_slp_mode_set(int level)
{
	u32 mode_set, mode_set1;
	bool osc_disable = rk3288_slp_disable_osc();

	regmap_read(sgrf_regmap, RK3288_SGRF_CPU_CON0, &rk3288_sgrf_cpu_con0);
	regmap_read(sgrf_regmap, RK3288_SGRF_SOC_CON0, &rk3288_sgrf_soc_con0);

	regmap_read(pmu_regmap, RK3288_PMU_PWRMODE_CON,
		    &rk3288_pmu_pwr_mode_con);

	/*
	 * SGRF_FAST_BOOT_EN - system to boot from FAST_BOOT_ADDR
	 * PCLK_WDT_GATE - disable WDT during suspend.
	 */
	regmap_write(sgrf_regmap, RK3288_SGRF_SOC_CON0,
		     SGRF_PCLK_WDT_GATE | SGRF_FAST_BOOT_EN
		     | SGRF_PCLK_WDT_GATE_WRITE | SGRF_FAST_BOOT_EN_WRITE);

	/*
	 * The dapswjdp can not auto reset before resume, that cause it may
	 * access some illegal address during resume. Let's disable it before
	 * suspend, and the MASKROM will enable it back.
	 */
	regmap_write(sgrf_regmap, RK3288_SGRF_CPU_CON0, SGRF_DAPDEVICEEN_WRITE);

	/* booting address of resuming system is from this register value */
	regmap_write(sgrf_regmap, RK3288_SGRF_FAST_BOOT_ADDR,
		     rk3288_bootram_phy);

	mode_set = BIT(PMU_GLOBAL_INT_DISABLE) | BIT(PMU_L2FLUSH_EN) |
		   BIT(PMU_SREF0_ENTER_EN) | BIT(PMU_SREF1_ENTER_EN) |
		   BIT(PMU_DDR0_GATING_EN) | BIT(PMU_DDR1_GATING_EN) |
		   BIT(PMU_PWR_MODE_EN) | BIT(PMU_CHIP_PD_EN) |
		   BIT(PMU_SCU_EN);

	mode_set1 = BIT(PMU_CLR_CORE) | BIT(PMU_CLR_CPUP);

	if (level == ROCKCHIP_ARM_OFF_LOGIC_DEEP) {
		/* arm off, logic deep sleep */
		mode_set |= BIT(PMU_BUS_PD_EN) | BIT(PMU_PMU_USE_LF) |
			    BIT(PMU_DDR1IO_RET_EN) | BIT(PMU_DDR0IO_RET_EN) |
			    BIT(PMU_ALIVE_USE_LF) | BIT(PMU_PLL_PD_EN);

		if (osc_disable)
			mode_set |= BIT(PMU_OSC_24M_DIS);

		mode_set1 |= BIT(PMU_CLR_ALIVE) | BIT(PMU_CLR_BUS) |
			     BIT(PMU_CLR_PERI) | BIT(PMU_CLR_DMA);

		regmap_write(pmu_regmap, RK3288_PMU_WAKEUP_CFG1,
			     PMU_ARMINT_WAKEUP_EN);

		/*
		 * In deep suspend we use PMU_PMU_USE_LF to let the rk3288
		 * switch its main clock supply to the alternative 32kHz
		 * source. Therefore set 30ms on a 32kHz clock for pmic
		 * stabilization. Similar 30ms on 24MHz for the other
		 * mode below.
		 */
		regmap_write(pmu_regmap, RK3288_PMU_STABL_CNT, 32 * 30);

		/* only wait for stabilization, if we turned the osc off */
		regmap_write(pmu_regmap, RK3288_PMU_OSC_CNT,
					 osc_disable ? 32 * 30 : 0);
	} else {
		/*
		 * arm off, logic normal
		 * if pmu_clk_core_src_gate_en is not set,
		 * wakeup will be error
		 */
		mode_set |= BIT(PMU_CLK_CORE_SRC_GATE_EN);

		regmap_write(pmu_regmap, RK3288_PMU_WAKEUP_CFG1,
			     PMU_ARMINT_WAKEUP_EN | PMU_GPIOINT_WAKEUP_EN);

		/* 30ms on a 24MHz clock for pmic stabilization */
		regmap_write(pmu_regmap, RK3288_PMU_STABL_CNT, 24000 * 30);

		/* oscillator is still running, so no need to wait */
		regmap_write(pmu_regmap, RK3288_PMU_OSC_CNT, 0);
	}

	regmap_write(pmu_regmap, RK3288_PMU_PWRMODE_CON, mode_set);
	regmap_write(pmu_regmap, RK3288_PMU_PWRMODE_CON1, mode_set1);
}