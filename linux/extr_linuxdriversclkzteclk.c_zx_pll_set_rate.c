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
struct zx_pll_config {int /*<<< orphan*/  cfg1; int /*<<< orphan*/  cfg0; } ;
struct clk_zx_pll {scalar_t__ reg_base; struct zx_pll_config* lookup_table; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ CFG0_CFG1_OFFSET ; 
 int rate_to_idx (struct clk_zx_pll*,unsigned long) ; 
 struct clk_zx_pll* to_clk_zx_pll (struct clk_hw*) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int zx_pll_set_rate(struct clk_hw *hw, unsigned long rate,
			   unsigned long parent_rate)
{
	/* Assume current cpu is not running on current PLL */
	struct clk_zx_pll *zx_pll = to_clk_zx_pll(hw);
	const struct zx_pll_config *config;
	int idx;

	idx = rate_to_idx(zx_pll, rate);
	config = &zx_pll->lookup_table[idx];

	writel_relaxed(config->cfg0, zx_pll->reg_base);
	writel_relaxed(config->cfg1, zx_pll->reg_base + CFG0_CFG1_OFFSET);

	return 0;
}