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
typedef  size_t u8 ;
struct clk_regmap_mux {unsigned int shift; int /*<<< orphan*/  reg; TYPE_1__* parent_map; scalar_t__ width; } ;
struct clk_regmap {int /*<<< orphan*/  regmap; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {size_t cfg; } ;

/* Variables and functions */
 unsigned int GENMASK (scalar_t__,unsigned int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 struct clk_regmap* to_clk_regmap (struct clk_hw*) ; 
 struct clk_regmap_mux* to_clk_regmap_mux (struct clk_hw*) ; 

__attribute__((used)) static int mux_set_parent(struct clk_hw *hw, u8 index)
{
	struct clk_regmap_mux *mux = to_clk_regmap_mux(hw);
	struct clk_regmap *clkr = to_clk_regmap(hw);
	unsigned int mask = GENMASK(mux->width + mux->shift - 1, mux->shift);
	unsigned int val;

	if (mux->parent_map)
		index = mux->parent_map[index].cfg;

	val = index;
	val <<= mux->shift;

	return regmap_update_bits(clkr->regmap, mux->reg, mask, val);
}