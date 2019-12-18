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
typedef  int u32 ;
struct ath10k_hw_params {int target_cpu_freq; struct ath10k_hw_clk_params* hw_clk; } ;
struct ath10k_hw_clk_params {int rnfrac; int outdiv; int settle_time; int refdiv; int div; } ;
struct ath10k {TYPE_1__* regs; struct ath10k_hw_params hw_params; } ;
typedef  int /*<<< orphan*/  mem_val ;
struct TYPE_2__ {scalar_t__ core_clk_div_address; scalar_t__ cpu_pll_init_address; scalar_t__ cpu_speed_address; } ;

/* Variables and functions */
 int ATH10K_HW_REFCLK_COUNT ; 
 int /*<<< orphan*/  BB_PLL_CONFIG_FRAC ; 
 int BB_PLL_CONFIG_FRAC_MASK ; 
 int BB_PLL_CONFIG_OFFSET ; 
 int /*<<< orphan*/  BB_PLL_CONFIG_OUTDIV ; 
 int BB_PLL_CONFIG_OUTDIV_MASK ; 
 int EFUSE_OFFSET ; 
 int /*<<< orphan*/  EFUSE_XTAL_SEL ; 
 int EINVAL ; 
 int MS (int,int /*<<< orphan*/ ) ; 
 int RTC_SOC_BASE_ADDRESS ; 
 int RTC_SYNC_STATUS_OFFSET ; 
 int /*<<< orphan*/  RTC_SYNC_STATUS_PLL_CHANGING ; 
 int RTC_WMAC_BASE_ADDRESS ; 
 int SM (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOC_CORE_CLK_CTRL_DIV ; 
 int SOC_CORE_CLK_CTRL_DIV_MASK ; 
 int SOC_CORE_CLK_CTRL_OFFSET ; 
 int SOC_CPU_CLOCK_OFFSET ; 
 int /*<<< orphan*/  SOC_CPU_CLOCK_STANDARD ; 
 int SOC_CPU_CLOCK_STANDARD_MASK ; 
 int /*<<< orphan*/  WLAN_PLL_CONTROL_BYPASS ; 
 int WLAN_PLL_CONTROL_BYPASS_MASK ; 
 int /*<<< orphan*/  WLAN_PLL_CONTROL_DIV ; 
 int /*<<< orphan*/  WLAN_PLL_CONTROL_NOPWD ; 
 int WLAN_PLL_CONTROL_NOPWD_MASK ; 
 int WLAN_PLL_CONTROL_OFFSET ; 
 int /*<<< orphan*/  WLAN_PLL_CONTROL_REFDIV ; 
 int WLAN_PLL_SETTLE_OFFSET ; 
 int /*<<< orphan*/  WLAN_PLL_SETTLE_TIME ; 
 int WLAN_PLL_SETTLE_TIME_MASK ; 
 int ath10k_bmi_read_soc_reg (struct ath10k*,int,int*) ; 
 int ath10k_bmi_write_memory (struct ath10k*,int,int*,int) ; 
 int ath10k_bmi_write_soc_reg (struct ath10k*,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int ath10k_hw_qca6174_enable_pll_clock(struct ath10k *ar)
{
	int ret, wait_limit;
	u32 clk_div_addr, pll_init_addr, speed_addr;
	u32 addr, reg_val, mem_val;
	struct ath10k_hw_params *hw;
	const struct ath10k_hw_clk_params *hw_clk;

	hw = &ar->hw_params;

	if (ar->regs->core_clk_div_address == 0 ||
	    ar->regs->cpu_pll_init_address == 0 ||
	    ar->regs->cpu_speed_address == 0)
		return -EINVAL;

	clk_div_addr = ar->regs->core_clk_div_address;
	pll_init_addr = ar->regs->cpu_pll_init_address;
	speed_addr = ar->regs->cpu_speed_address;

	/* Read efuse register to find out the right hw clock configuration */
	addr = (RTC_SOC_BASE_ADDRESS | EFUSE_OFFSET);
	ret = ath10k_bmi_read_soc_reg(ar, addr, &reg_val);
	if (ret)
		return -EINVAL;

	/* sanitize if the hw refclk index is out of the boundary */
	if (MS(reg_val, EFUSE_XTAL_SEL) > ATH10K_HW_REFCLK_COUNT)
		return -EINVAL;

	hw_clk = &hw->hw_clk[MS(reg_val, EFUSE_XTAL_SEL)];

	/* Set the rnfrac and outdiv params to bb_pll register */
	addr = (RTC_SOC_BASE_ADDRESS | BB_PLL_CONFIG_OFFSET);
	ret = ath10k_bmi_read_soc_reg(ar, addr, &reg_val);
	if (ret)
		return -EINVAL;

	reg_val &= ~(BB_PLL_CONFIG_FRAC_MASK | BB_PLL_CONFIG_OUTDIV_MASK);
	reg_val |= (SM(hw_clk->rnfrac, BB_PLL_CONFIG_FRAC) |
		    SM(hw_clk->outdiv, BB_PLL_CONFIG_OUTDIV));
	ret = ath10k_bmi_write_soc_reg(ar, addr, reg_val);
	if (ret)
		return -EINVAL;

	/* Set the correct settle time value to pll_settle register */
	addr = (RTC_WMAC_BASE_ADDRESS | WLAN_PLL_SETTLE_OFFSET);
	ret = ath10k_bmi_read_soc_reg(ar, addr, &reg_val);
	if (ret)
		return -EINVAL;

	reg_val &= ~WLAN_PLL_SETTLE_TIME_MASK;
	reg_val |= SM(hw_clk->settle_time, WLAN_PLL_SETTLE_TIME);
	ret = ath10k_bmi_write_soc_reg(ar, addr, reg_val);
	if (ret)
		return -EINVAL;

	/* Set the clock_ctrl div to core_clk_ctrl register */
	addr = (RTC_SOC_BASE_ADDRESS | SOC_CORE_CLK_CTRL_OFFSET);
	ret = ath10k_bmi_read_soc_reg(ar, addr, &reg_val);
	if (ret)
		return -EINVAL;

	reg_val &= ~SOC_CORE_CLK_CTRL_DIV_MASK;
	reg_val |= SM(1, SOC_CORE_CLK_CTRL_DIV);
	ret = ath10k_bmi_write_soc_reg(ar, addr, reg_val);
	if (ret)
		return -EINVAL;

	/* Set the clock_div register */
	mem_val = 1;
	ret = ath10k_bmi_write_memory(ar, clk_div_addr, &mem_val,
				      sizeof(mem_val));
	if (ret)
		return -EINVAL;

	/* Configure the pll_control register */
	addr = (RTC_WMAC_BASE_ADDRESS | WLAN_PLL_CONTROL_OFFSET);
	ret = ath10k_bmi_read_soc_reg(ar, addr, &reg_val);
	if (ret)
		return -EINVAL;

	reg_val |= (SM(hw_clk->refdiv, WLAN_PLL_CONTROL_REFDIV) |
		    SM(hw_clk->div, WLAN_PLL_CONTROL_DIV) |
		    SM(1, WLAN_PLL_CONTROL_NOPWD));
	ret = ath10k_bmi_write_soc_reg(ar, addr, reg_val);
	if (ret)
		return -EINVAL;

	/* busy wait (max 1s) the rtc_sync status register indicate ready */
	wait_limit = 100000;
	addr = (RTC_WMAC_BASE_ADDRESS | RTC_SYNC_STATUS_OFFSET);
	do {
		ret = ath10k_bmi_read_soc_reg(ar, addr, &reg_val);
		if (ret)
			return -EINVAL;

		if (!MS(reg_val, RTC_SYNC_STATUS_PLL_CHANGING))
			break;

		wait_limit--;
		udelay(10);

	} while (wait_limit > 0);

	if (MS(reg_val, RTC_SYNC_STATUS_PLL_CHANGING))
		return -EINVAL;

	/* Unset the pll_bypass in pll_control register */
	addr = (RTC_WMAC_BASE_ADDRESS | WLAN_PLL_CONTROL_OFFSET);
	ret = ath10k_bmi_read_soc_reg(ar, addr, &reg_val);
	if (ret)
		return -EINVAL;

	reg_val &= ~WLAN_PLL_CONTROL_BYPASS_MASK;
	reg_val |= SM(0, WLAN_PLL_CONTROL_BYPASS);
	ret = ath10k_bmi_write_soc_reg(ar, addr, reg_val);
	if (ret)
		return -EINVAL;

	/* busy wait (max 1s) the rtc_sync status register indicate ready */
	wait_limit = 100000;
	addr = (RTC_WMAC_BASE_ADDRESS | RTC_SYNC_STATUS_OFFSET);
	do {
		ret = ath10k_bmi_read_soc_reg(ar, addr, &reg_val);
		if (ret)
			return -EINVAL;

		if (!MS(reg_val, RTC_SYNC_STATUS_PLL_CHANGING))
			break;

		wait_limit--;
		udelay(10);

	} while (wait_limit > 0);

	if (MS(reg_val, RTC_SYNC_STATUS_PLL_CHANGING))
		return -EINVAL;

	/* Enable the hardware cpu clock register */
	addr = (RTC_SOC_BASE_ADDRESS | SOC_CPU_CLOCK_OFFSET);
	ret = ath10k_bmi_read_soc_reg(ar, addr, &reg_val);
	if (ret)
		return -EINVAL;

	reg_val &= ~SOC_CPU_CLOCK_STANDARD_MASK;
	reg_val |= SM(1, SOC_CPU_CLOCK_STANDARD);
	ret = ath10k_bmi_write_soc_reg(ar, addr, reg_val);
	if (ret)
		return -EINVAL;

	/* unset the nopwd from pll_control register */
	addr = (RTC_WMAC_BASE_ADDRESS | WLAN_PLL_CONTROL_OFFSET);
	ret = ath10k_bmi_read_soc_reg(ar, addr, &reg_val);
	if (ret)
		return -EINVAL;

	reg_val &= ~WLAN_PLL_CONTROL_NOPWD_MASK;
	ret = ath10k_bmi_write_soc_reg(ar, addr, reg_val);
	if (ret)
		return -EINVAL;

	/* enable the pll_init register */
	mem_val = 1;
	ret = ath10k_bmi_write_memory(ar, pll_init_addr, &mem_val,
				      sizeof(mem_val));
	if (ret)
		return -EINVAL;

	/* set the target clock frequency to speed register */
	ret = ath10k_bmi_write_memory(ar, speed_addr, &hw->target_cpu_freq,
				      sizeof(hw->target_cpu_freq));
	if (ret)
		return -EINVAL;

	return 0;
}