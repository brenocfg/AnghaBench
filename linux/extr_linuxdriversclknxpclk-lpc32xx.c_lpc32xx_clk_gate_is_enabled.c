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
struct lpc32xx_clk_gate {int flags; int /*<<< orphan*/  bit_idx; int /*<<< orphan*/  reg; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int CLK_GATE_SET_TO_DISABLE ; 
 int /*<<< orphan*/  clk_regmap ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 struct lpc32xx_clk_gate* to_lpc32xx_gate (struct clk_hw*) ; 

__attribute__((used)) static int lpc32xx_clk_gate_is_enabled(struct clk_hw *hw)
{
	struct lpc32xx_clk_gate *clk = to_lpc32xx_gate(hw);
	u32 val;
	bool is_set;

	regmap_read(clk_regmap, clk->reg, &val);
	is_set = val & BIT(clk->bit_idx);

	return (clk->flags & CLK_GATE_SET_TO_DISABLE ? !is_set : is_set);
}