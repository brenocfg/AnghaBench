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
typedef  size_t u8 ;
typedef  unsigned long u64 ;
typedef  int u32 ;
struct TYPE_2__ {int pllsw; int /*<<< orphan*/  branch; scalar_t__ clk38div; scalar_t__ offset; } ;

/* Variables and functions */
 size_t PRCMU_SGACLK ; 
 int PRCM_CLK_MGT_CLK38 ; 
 int PRCM_CLK_MGT_CLK38DIV ; 
 int PRCM_CLK_MGT_CLKPLLDIV_MASK ; 
 int PRCM_CLK_MGT_CLKPLLSW_DDR ; 
 int PRCM_CLK_MGT_CLKPLLSW_MASK ; 
 int PRCM_CLK_MGT_CLKPLLSW_SOC0 ; 
 int PRCM_CLK_MGT_CLKPLLSW_SOC1 ; 
 int /*<<< orphan*/  PRCM_PLLDDR_FREQ ; 
 int /*<<< orphan*/  PRCM_PLLSOC0_FREQ ; 
 int /*<<< orphan*/  PRCM_PLLSOC1_FREQ ; 
 int PRCM_SGACLK_MGT_SGACLKDIV_BY_2_5_EN ; 
 unsigned long ROOT_CLOCK_RATE ; 
 TYPE_1__* clk_mgt ; 
 int /*<<< orphan*/  do_div (unsigned long,int) ; 
 unsigned long pll_rate (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ prcmu_base ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static unsigned long clock_rate(u8 clock)
{
	u32 val;
	u32 pllsw;
	unsigned long rate = ROOT_CLOCK_RATE;

	val = readl(prcmu_base + clk_mgt[clock].offset);

	if (val & PRCM_CLK_MGT_CLK38) {
		if (clk_mgt[clock].clk38div && (val & PRCM_CLK_MGT_CLK38DIV))
			rate /= 2;
		return rate;
	}

	val |= clk_mgt[clock].pllsw;
	pllsw = (val & PRCM_CLK_MGT_CLKPLLSW_MASK);

	if (pllsw == PRCM_CLK_MGT_CLKPLLSW_SOC0)
		rate = pll_rate(PRCM_PLLSOC0_FREQ, rate, clk_mgt[clock].branch);
	else if (pllsw == PRCM_CLK_MGT_CLKPLLSW_SOC1)
		rate = pll_rate(PRCM_PLLSOC1_FREQ, rate, clk_mgt[clock].branch);
	else if (pllsw == PRCM_CLK_MGT_CLKPLLSW_DDR)
		rate = pll_rate(PRCM_PLLDDR_FREQ, rate, clk_mgt[clock].branch);
	else
		return 0;

	if ((clock == PRCMU_SGACLK) &&
		(val & PRCM_SGACLK_MGT_SGACLKDIV_BY_2_5_EN)) {
		u64 r = (rate * 10);

		(void)do_div(r, 25);
		return (unsigned long)r;
	}
	val &= PRCM_CLK_MGT_CLKPLLDIV_MASK;
	if (val)
		return rate / val;
	else
		return 0;
}