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
struct clk_regmap_mux_div {int /*<<< orphan*/  div; int /*<<< orphan*/ * parent_map; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int mux_div_set_src_div (struct clk_regmap_mux_div*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct clk_regmap_mux_div* to_clk_regmap_mux_div (struct clk_hw*) ; 

__attribute__((used)) static int mux_div_set_parent(struct clk_hw *hw, u8 index)
{
	struct clk_regmap_mux_div *md = to_clk_regmap_mux_div(hw);

	return mux_div_set_src_div(md, md->parent_map[index], md->div);
}