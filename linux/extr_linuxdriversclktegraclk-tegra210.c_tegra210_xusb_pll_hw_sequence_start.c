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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 scalar_t__ XUSBIO_PLL_CFG0 ; 
 int /*<<< orphan*/  XUSBIO_PLL_CFG0_SEQ_ENABLE ; 
 scalar_t__ clk_base ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

void tegra210_xusb_pll_hw_sequence_start(void)
{
	u32 val;

	val = readl_relaxed(clk_base + XUSBIO_PLL_CFG0);
	val |= XUSBIO_PLL_CFG0_SEQ_ENABLE;
	writel_relaxed(val, clk_base + XUSBIO_PLL_CFG0);
}