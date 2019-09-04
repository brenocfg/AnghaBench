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
struct hibmc_display_panel_pll {int POD; int OD; int N; int M; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 unsigned int HIBMC_FIELD (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HIBMC_PLL_CTRL_BYPASS ; 
 int /*<<< orphan*/  HIBMC_PLL_CTRL_INPUT ; 
 int /*<<< orphan*/  HIBMC_PLL_CTRL_M ; 
 int /*<<< orphan*/  HIBMC_PLL_CTRL_N ; 
 int /*<<< orphan*/  HIBMC_PLL_CTRL_OD ; 
 int /*<<< orphan*/  HIBMC_PLL_CTRL_POD ; 
 int /*<<< orphan*/  HIBMC_PLL_CTRL_POWER ; 

__attribute__((used)) static unsigned int format_pll_reg(void)
{
	unsigned int pllreg = 0;
	struct hibmc_display_panel_pll pll = {0};

	/*
	 * Note that all PLL's have the same format. Here,
	 * we just use Panel PLL parameter to work out the bit
	 * fields in the register.On returning a 32 bit number, the value can
	 * be applied to any PLL in the calling function.
	 */
	pllreg |= HIBMC_FIELD(HIBMC_PLL_CTRL_BYPASS, 0);
	pllreg |= HIBMC_FIELD(HIBMC_PLL_CTRL_POWER, 1);
	pllreg |= HIBMC_FIELD(HIBMC_PLL_CTRL_INPUT, 0);
	pllreg |= HIBMC_FIELD(HIBMC_PLL_CTRL_POD, pll.POD);
	pllreg |= HIBMC_FIELD(HIBMC_PLL_CTRL_OD, pll.OD);
	pllreg |= HIBMC_FIELD(HIBMC_PLL_CTRL_N, pll.N);
	pllreg |= HIBMC_FIELD(HIBMC_PLL_CTRL_M, pll.M);

	return pllreg;
}