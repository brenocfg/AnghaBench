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
struct meson_clk_pll_data {int /*<<< orphan*/  rst; scalar_t__ init_count; int /*<<< orphan*/  init_regs; } ;
struct clk_regmap {int /*<<< orphan*/  map; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 struct meson_clk_pll_data* meson_clk_pll_data (struct clk_regmap*) ; 
 int /*<<< orphan*/  meson_parm_write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  regmap_multi_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 struct clk_regmap* to_clk_regmap (struct clk_hw*) ; 

__attribute__((used)) static void meson_clk_pll_init(struct clk_hw *hw)
{
	struct clk_regmap *clk = to_clk_regmap(hw);
	struct meson_clk_pll_data *pll = meson_clk_pll_data(clk);

	if (pll->init_count) {
		meson_parm_write(clk->map, &pll->rst, 1);
		regmap_multi_reg_write(clk->map, pll->init_regs,
				       pll->init_count);
		meson_parm_write(clk->map, &pll->rst, 0);
	}
}