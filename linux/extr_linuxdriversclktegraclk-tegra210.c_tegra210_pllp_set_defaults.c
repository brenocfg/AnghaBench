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
struct tegra_clk_pll {TYPE_1__* params; } ;
struct TYPE_2__ {int defaults_set; scalar_t__* ext_misc_reg; scalar_t__ base_reg; } ;

/* Variables and functions */
 int PLLP_MISC0_DEFAULT_VALUE ; 
 int PLLP_MISC0_LOCK_ENABLE ; 
 int PLLP_MISC0_LOCK_OVERRIDE ; 
 int PLLP_MISC1_DEFAULT_VALUE ; 
 int PLLP_MISC1_HSIO_EN ; 
 int PLLP_MISC1_XUSB_EN ; 
 int PLL_ENABLE ; 
 scalar_t__ clk_base ; 
 int /*<<< orphan*/  pllp_check_defaults (struct tegra_clk_pll*,int) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void tegra210_pllp_set_defaults(struct tegra_clk_pll *pllp)
{
	u32 mask;
	u32 val = readl_relaxed(clk_base + pllp->params->base_reg);

	pllp->params->defaults_set = true;

	if (val & PLL_ENABLE) {

		/*
		 * PLL is ON: check if defaults already set, then set those
		 * that can be updated in flight.
		 */
		pllp_check_defaults(pllp, true);
		if (!pllp->params->defaults_set)
			pr_warn("PLL_P already enabled. Postponing set full defaults\n");

		/* Enable lock detect */
		val = readl_relaxed(clk_base + pllp->params->ext_misc_reg[0]);
		mask = PLLP_MISC0_LOCK_ENABLE | PLLP_MISC0_LOCK_OVERRIDE;
		val &= ~mask;
		val |= PLLP_MISC0_DEFAULT_VALUE & mask;
		writel_relaxed(val, clk_base + pllp->params->ext_misc_reg[0]);
		udelay(1);

		return;
	}

	/* set IDDQ, enable lock detect */
	writel_relaxed(PLLP_MISC0_DEFAULT_VALUE,
			clk_base + pllp->params->ext_misc_reg[0]);

	/* Preserve branch control */
	val = readl_relaxed(clk_base + pllp->params->ext_misc_reg[1]);
	mask = PLLP_MISC1_HSIO_EN | PLLP_MISC1_XUSB_EN;
	val &= mask;
	val |= ~mask & PLLP_MISC1_DEFAULT_VALUE;
	writel_relaxed(val, clk_base + pllp->params->ext_misc_reg[1]);
	udelay(1);
}