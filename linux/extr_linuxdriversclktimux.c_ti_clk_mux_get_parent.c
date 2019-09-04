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
typedef  int u8 ;
typedef  int u32 ;
struct clk_omap_mux {int shift; int mask; int* table; int flags; int /*<<< orphan*/  reg; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {int (* clk_readl ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int CLK_MUX_INDEX_BIT ; 
 int CLK_MUX_INDEX_ONE ; 
 int EINVAL ; 
 int clk_hw_get_num_parents (struct clk_hw*) ; 
 int ffs (int) ; 
 int stub1 (int /*<<< orphan*/ *) ; 
 TYPE_1__* ti_clk_ll_ops ; 
 struct clk_omap_mux* to_clk_omap_mux (struct clk_hw*) ; 

__attribute__((used)) static u8 ti_clk_mux_get_parent(struct clk_hw *hw)
{
	struct clk_omap_mux *mux = to_clk_omap_mux(hw);
	int num_parents = clk_hw_get_num_parents(hw);
	u32 val;

	/*
	 * FIXME need a mux-specific flag to determine if val is bitwise or
	 * numeric. e.g. sys_clkin_ck's clksel field is 3 bits wide, but ranges
	 * from 0x1 to 0x7 (index starts at one)
	 * OTOH, pmd_trace_clk_mux_ck uses a separate bit for each clock, so
	 * val = 0x4 really means "bit 2, index starts at bit 0"
	 */
	val = ti_clk_ll_ops->clk_readl(&mux->reg) >> mux->shift;
	val &= mux->mask;

	if (mux->table) {
		int i;

		for (i = 0; i < num_parents; i++)
			if (mux->table[i] == val)
				return i;
		return -EINVAL;
	}

	if (val && (mux->flags & CLK_MUX_INDEX_BIT))
		val = ffs(val) - 1;

	if (val && (mux->flags & CLK_MUX_INDEX_ONE))
		val--;

	if (val >= num_parents)
		return -EINVAL;

	return val;
}