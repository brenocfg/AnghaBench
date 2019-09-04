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
struct hsdk_pll_clk {int /*<<< orphan*/  dev; } ;
struct hsdk_pll_cfg {int idiv; int fbdiv; int odiv; int band; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGU_PLL_CTRL ; 
 int CGU_PLL_CTRL_BAND_SHIFT ; 
 int CGU_PLL_CTRL_FBDIV_SHIFT ; 
 int CGU_PLL_CTRL_IDIV_SHIFT ; 
 int CGU_PLL_CTRL_ODIV_SHIFT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  hsdk_pll_write (struct hsdk_pll_clk*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void hsdk_pll_set_cfg(struct hsdk_pll_clk *clk,
				    const struct hsdk_pll_cfg *cfg)
{
	u32 val = 0;

	/* Powerdown and Bypass bits should be cleared */
	val |= cfg->idiv << CGU_PLL_CTRL_IDIV_SHIFT;
	val |= cfg->fbdiv << CGU_PLL_CTRL_FBDIV_SHIFT;
	val |= cfg->odiv << CGU_PLL_CTRL_ODIV_SHIFT;
	val |= cfg->band << CGU_PLL_CTRL_BAND_SHIFT;

	dev_dbg(clk->dev, "write configuration: %#x\n", val);

	hsdk_pll_write(clk, CGU_PLL_CTRL, val);
}