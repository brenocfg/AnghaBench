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
 int ARM_WAIT_DIV_396M ; 
 int BM_CDHIPR_ARM_PODF_BUSY ; 
 scalar_t__ CACRR ; 
 scalar_t__ CDHIPR ; 
 int __raw_readl (scalar_t__) ; 
 scalar_t__ ccm_base ; 
 int /*<<< orphan*/  imx6sl_enable_pll_arm (int) ; 
 int imx6sl_get_arm_divider_for_wait () ; 
 unsigned long readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (unsigned long,scalar_t__) ; 

void imx6sl_set_wait_clk(bool enter)
{
	static unsigned long saved_arm_div;
	int arm_div_for_wait = imx6sl_get_arm_divider_for_wait();

	/*
	 * According to hardware design, arm podf change need
	 * PLL1 clock enabled.
	 */
	if (arm_div_for_wait == ARM_WAIT_DIV_396M)
		imx6sl_enable_pll_arm(true);

	if (enter) {
		saved_arm_div = readl_relaxed(ccm_base + CACRR);
		writel_relaxed(arm_div_for_wait, ccm_base + CACRR);
	} else {
		writel_relaxed(saved_arm_div, ccm_base + CACRR);
	}
	while (__raw_readl(ccm_base + CDHIPR) & BM_CDHIPR_ARM_PODF_BUSY)
		;

	if (arm_div_for_wait == ARM_WAIT_DIV_396M)
		imx6sl_enable_pll_arm(false);
}