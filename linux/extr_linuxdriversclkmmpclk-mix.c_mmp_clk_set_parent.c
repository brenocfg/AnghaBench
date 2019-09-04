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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct mmp_clk_mix_clk_table {scalar_t__ valid; scalar_t__ parent_index; int /*<<< orphan*/  divisor; } ;
struct mmp_clk_mix {int table_size; struct mmp_clk_mix_clk_table* table; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ _get_div_val (struct mmp_clk_mix*,int /*<<< orphan*/ ) ; 
 scalar_t__ _get_mux_val (struct mmp_clk_mix*,scalar_t__) ; 
 int _set_rate (struct mmp_clk_mix*,scalar_t__,scalar_t__,int,int) ; 
 struct mmp_clk_mix* to_clk_mix (struct clk_hw*) ; 

__attribute__((used)) static int mmp_clk_set_parent(struct clk_hw *hw, u8 index)
{
	struct mmp_clk_mix *mix = to_clk_mix(hw);
	struct mmp_clk_mix_clk_table *item;
	int i;
	u32 div_val, mux_val;

	if (mix->table) {
		for (i = 0; i < mix->table_size; i++) {
			item = &mix->table[i];
			if (item->valid == 0)
				continue;
			if (item->parent_index == index)
				break;
		}
		if (i < mix->table_size) {
			div_val = _get_div_val(mix, item->divisor);
			mux_val = _get_mux_val(mix, item->parent_index);
		} else
			return -EINVAL;
	} else {
		mux_val = _get_mux_val(mix, index);
		div_val = 0;
	}

	return _set_rate(mix, mux_val, div_val, 1, div_val ? 1 : 0);
}