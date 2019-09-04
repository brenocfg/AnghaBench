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
typedef  size_t u8 ;
struct lpc32xx_clk_mux {size_t* table; int mask; int shift; int /*<<< orphan*/  reg; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_regmap ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,size_t) ; 
 struct lpc32xx_clk_mux* to_lpc32xx_mux (struct clk_hw*) ; 

__attribute__((used)) static int clk_mux_set_parent(struct clk_hw *hw, u8 index)
{
	struct lpc32xx_clk_mux *mux = to_lpc32xx_mux(hw);

	if (mux->table)
		index = mux->table[index];

	return regmap_update_bits(clk_regmap, mux->reg,
			  mux->mask << mux->shift, index << mux->shift);
}