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
struct mmp_clk_mix_clk_table {unsigned long rate; int valid; unsigned long divisor; int /*<<< orphan*/  parent_index; } ;
struct clk_hw {int dummy; } ;
struct mmp_clk_mix {struct clk_hw hw; } ;

/* Variables and functions */
 struct clk_hw* clk_hw_get_parent_by_index (struct clk_hw*,int /*<<< orphan*/ ) ; 
 unsigned long clk_hw_get_rate (struct clk_hw*) ; 

__attribute__((used)) static void _filter_clk_table(struct mmp_clk_mix *mix,
				struct mmp_clk_mix_clk_table *table,
				unsigned int table_size)
{
	int i;
	struct mmp_clk_mix_clk_table *item;
	struct clk_hw *parent, *hw;
	unsigned long parent_rate;

	hw = &mix->hw;

	for (i = 0; i < table_size; i++) {
		item = &table[i];
		parent = clk_hw_get_parent_by_index(hw, item->parent_index);
		parent_rate = clk_hw_get_rate(parent);
		if (parent_rate % item->rate) {
			item->valid = 0;
		} else {
			item->divisor = parent_rate / item->rate;
			item->valid = 1;
		}
	}
}