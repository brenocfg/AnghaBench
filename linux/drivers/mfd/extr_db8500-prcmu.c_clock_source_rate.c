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
 int PRCM_CLK_MGT_CLK38 ; 
 int PRCM_CLK_MGT_CLKPLLSW_DDR ; 
 int PRCM_CLK_MGT_CLKPLLSW_MASK ; 
 int PRCM_CLK_MGT_CLKPLLSW_SOC0 ; 
 int PRCM_CLK_MGT_CLKPLLSW_SOC1 ; 
 int /*<<< orphan*/  PRCM_PLLDDR_FREQ ; 
 int /*<<< orphan*/  PRCM_PLLSOC0_FREQ ; 
 int /*<<< orphan*/  PRCM_PLLSOC1_FREQ ; 
 unsigned long ROOT_CLOCK_RATE ; 
 unsigned long pll_rate (int /*<<< orphan*/ ,unsigned long,int) ; 

__attribute__((used)) static unsigned long clock_source_rate(u32 clk_mgt_val, int branch)
{
	if (clk_mgt_val & PRCM_CLK_MGT_CLK38)
		return ROOT_CLOCK_RATE;
	clk_mgt_val &= PRCM_CLK_MGT_CLKPLLSW_MASK;
	if (clk_mgt_val == PRCM_CLK_MGT_CLKPLLSW_SOC0)
		return pll_rate(PRCM_PLLSOC0_FREQ, ROOT_CLOCK_RATE, branch);
	else if (clk_mgt_val == PRCM_CLK_MGT_CLKPLLSW_SOC1)
		return pll_rate(PRCM_PLLSOC1_FREQ, ROOT_CLOCK_RATE, branch);
	else if (clk_mgt_val == PRCM_CLK_MGT_CLKPLLSW_DDR)
		return pll_rate(PRCM_PLLDDR_FREQ, ROOT_CLOCK_RATE, branch);
	else
		return 0;
}