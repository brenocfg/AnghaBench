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
struct lpc32xx_clk {int enable_mask; int /*<<< orphan*/  reg; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_ddram_is_enabled (struct clk_hw*) ; 
 int /*<<< orphan*/  clk_regmap ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 struct lpc32xx_clk* to_lpc32xx_clk (struct clk_hw*) ; 

__attribute__((used)) static unsigned long clk_ddram_recalc_rate(struct clk_hw *hw,
					   unsigned long parent_rate)
{
	struct lpc32xx_clk *clk = to_lpc32xx_clk(hw);
	u32 val;

	if (!clk_ddram_is_enabled(hw))
		return 0;

	regmap_read(clk_regmap, clk->reg, &val);
	val &= clk->enable_mask;

	return parent_rate / (val >> 7);
}