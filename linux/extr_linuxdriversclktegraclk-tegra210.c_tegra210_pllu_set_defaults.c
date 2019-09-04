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
struct tegra_clk_pll_params {int defaults_set; scalar_t__* ext_misc_reg; scalar_t__ base_reg; } ;

/* Variables and functions */
 int PLLU_MISC0_DEFAULT_VALUE ; 
 int PLLU_MISC0_LOCK_ENABLE ; 
 int PLLU_MISC1_DEFAULT_VALUE ; 
 int PLLU_MISC1_LOCK_OVERRIDE ; 
 int PLL_ENABLE ; 
 scalar_t__ clk_base ; 
 int /*<<< orphan*/  pllu_check_defaults (struct tegra_clk_pll_params*,int) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void tegra210_pllu_set_defaults(struct tegra_clk_pll_params *pllu)
{
	u32 val = readl_relaxed(clk_base + pllu->base_reg);

	pllu->defaults_set = true;

	if (val & PLL_ENABLE) {

		/*
		 * PLL is ON: check if defaults already set, then set those
		 * that can be updated in flight.
		 */
		pllu_check_defaults(pllu, false);
		if (!pllu->defaults_set)
			pr_warn("PLL_U already enabled. Postponing set full defaults\n");

		/* Enable lock detect */
		val = readl_relaxed(clk_base + pllu->ext_misc_reg[0]);
		val &= ~PLLU_MISC0_LOCK_ENABLE;
		val |= PLLU_MISC0_DEFAULT_VALUE & PLLU_MISC0_LOCK_ENABLE;
		writel_relaxed(val, clk_base + pllu->ext_misc_reg[0]);

		val = readl_relaxed(clk_base + pllu->ext_misc_reg[1]);
		val &= ~PLLU_MISC1_LOCK_OVERRIDE;
		val |= PLLU_MISC1_DEFAULT_VALUE & PLLU_MISC1_LOCK_OVERRIDE;
		writel_relaxed(val, clk_base + pllu->ext_misc_reg[1]);
		udelay(1);

		return;
	}

	/* set IDDQ, enable lock detect */
	writel_relaxed(PLLU_MISC0_DEFAULT_VALUE,
			clk_base + pllu->ext_misc_reg[0]);
	writel_relaxed(PLLU_MISC1_DEFAULT_VALUE,
			clk_base + pllu->ext_misc_reg[1]);
	udelay(1);
}