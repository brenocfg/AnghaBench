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
struct lpc32xx_pll_clk {int /*<<< orphan*/  enable; int /*<<< orphan*/  reg; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_regmap ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct lpc32xx_pll_clk* to_lpc32xx_pll_clk (struct clk_hw*) ; 

__attribute__((used)) static void clk_pll_disable(struct clk_hw *hw)
{
	struct lpc32xx_pll_clk *clk = to_lpc32xx_pll_clk(hw);

	regmap_update_bits(clk_regmap, clk->reg, clk->enable, 0x0);
}