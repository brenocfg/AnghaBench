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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct ti_clk_divider {int flags; int /*<<< orphan*/  bit_shift; int /*<<< orphan*/  parent; int /*<<< orphan*/  reg; int /*<<< orphan*/  module; } ;
struct ti_clk {int /*<<< orphan*/  name; struct ti_clk_divider* data; } ;
struct clk_omap_reg {int /*<<< orphan*/  offset; int /*<<< orphan*/  index; } ;
struct clk_div_table {int dummy; } ;
typedef  struct clk_div_table const clk ;

/* Variables and functions */
 int CLKF_INDEX_POWER_OF_TWO ; 
 int CLKF_INDEX_STARTS_AT_ONE ; 
 int CLKF_SET_RATE_PARENT ; 
 int /*<<< orphan*/  CLK_DIVIDER_ONE_BASED ; 
 int /*<<< orphan*/  CLK_DIVIDER_POWER_OF_TWO ; 
 int /*<<< orphan*/  CLK_SET_RATE_PARENT ; 
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ IS_ERR (struct clk_div_table const*) ; 
 struct clk_div_table* _get_div_table_from_setup (struct ti_clk_divider*,int /*<<< orphan*/ *) ; 
 struct clk_div_table* _register_divider (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct clk_omap_reg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct clk_div_table const*) ; 
 int /*<<< orphan*/  kfree (struct clk_div_table const*) ; 

struct clk *ti_clk_register_divider(struct ti_clk *setup)
{
	struct ti_clk_divider *div = setup->data;
	struct clk_omap_reg reg = {
		.index = div->module,
		.offset = div->reg,
	};
	u8 width;
	u32 flags = 0;
	u8 div_flags = 0;
	const struct clk_div_table *table;
	struct clk *clk;

	if (div->flags & CLKF_INDEX_STARTS_AT_ONE)
		div_flags |= CLK_DIVIDER_ONE_BASED;

	if (div->flags & CLKF_INDEX_POWER_OF_TWO)
		div_flags |= CLK_DIVIDER_POWER_OF_TWO;

	if (div->flags & CLKF_SET_RATE_PARENT)
		flags |= CLK_SET_RATE_PARENT;

	table = _get_div_table_from_setup(div, &width);
	if (IS_ERR(table))
		return (struct clk *)table;

	clk = _register_divider(NULL, setup->name, div->parent,
				flags, &reg, div->bit_shift,
				width, -EINVAL, div_flags, table);

	if (IS_ERR(clk))
		kfree(table);

	return clk;
}