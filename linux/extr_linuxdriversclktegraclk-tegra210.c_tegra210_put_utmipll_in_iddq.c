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
 scalar_t__ UTMIPLL_HW_PWRDN_CFG0 ; 
 int UTMIPLL_HW_PWRDN_CFG0_IDDQ_OVERRIDE ; 
 int UTMIPLL_HW_PWRDN_CFG0_UTMIPLL_LOCK ; 
 scalar_t__ clk_base ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

void tegra210_put_utmipll_in_iddq(void)
{
	u32 reg;

	reg = readl_relaxed(clk_base + UTMIPLL_HW_PWRDN_CFG0);

	if (reg & UTMIPLL_HW_PWRDN_CFG0_UTMIPLL_LOCK) {
		pr_err("trying to assert IDDQ while UTMIPLL is locked\n");
		return;
	}

	reg |= UTMIPLL_HW_PWRDN_CFG0_IDDQ_OVERRIDE;
	writel_relaxed(reg, clk_base + UTMIPLL_HW_PWRDN_CFG0);
}