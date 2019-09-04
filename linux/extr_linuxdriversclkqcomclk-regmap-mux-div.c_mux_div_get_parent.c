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
typedef  size_t u32 ;
struct clk_regmap_mux_div {size_t* parent_map; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 char* clk_hw_get_name (struct clk_hw*) ; 
 size_t clk_hw_get_num_parents (struct clk_hw*) ; 
 int /*<<< orphan*/  mux_div_get_src_div (struct clk_regmap_mux_div*,size_t*,size_t*) ; 
 int /*<<< orphan*/  pr_err (char*,char const*,size_t) ; 
 struct clk_regmap_mux_div* to_clk_regmap_mux_div (struct clk_hw*) ; 

__attribute__((used)) static u8 mux_div_get_parent(struct clk_hw *hw)
{
	struct clk_regmap_mux_div *md = to_clk_regmap_mux_div(hw);
	const char *name = clk_hw_get_name(hw);
	u32 i, div, src = 0;

	mux_div_get_src_div(md, &src, &div);

	for (i = 0; i < clk_hw_get_num_parents(hw); i++)
		if (src == md->parent_map[i])
			return i;

	pr_err("%s: Can't find parent with src %d\n", name, src);
	return 0;
}