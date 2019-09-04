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
struct ti_clk_divider {int flags; int /*<<< orphan*/  bit_shift; int /*<<< orphan*/  reg; int /*<<< orphan*/  module; } ;
struct clk_omap_reg {int /*<<< orphan*/  offset; int /*<<< orphan*/  index; } ;
struct clk_hw {int dummy; } ;
struct clk_omap_divider {struct clk_hw hw; int /*<<< orphan*/  latch; int /*<<< orphan*/  shift; int /*<<< orphan*/  table; int /*<<< orphan*/  width; int /*<<< orphan*/  flags; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int CLKF_INDEX_POWER_OF_TWO ; 
 int CLKF_INDEX_STARTS_AT_ONE ; 
 int /*<<< orphan*/  CLK_DIVIDER_ONE_BASED ; 
 int /*<<< orphan*/  CLK_DIVIDER_POWER_OF_TWO ; 
 int /*<<< orphan*/  EINVAL ; 
 int ENOMEM ; 
 struct clk_hw* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _get_div_table_from_setup (struct ti_clk_divider*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct clk_omap_divider*) ; 
 struct clk_omap_divider* kzalloc (int,int /*<<< orphan*/ ) ; 

struct clk_hw *ti_clk_build_component_div(struct ti_clk_divider *setup)
{
	struct clk_omap_divider *div;
	struct clk_omap_reg *reg;
	int ret;

	if (!setup)
		return NULL;

	div = kzalloc(sizeof(*div), GFP_KERNEL);
	if (!div)
		return ERR_PTR(-ENOMEM);

	reg = (struct clk_omap_reg *)&div->reg;
	reg->index = setup->module;
	reg->offset = setup->reg;

	if (setup->flags & CLKF_INDEX_STARTS_AT_ONE)
		div->flags |= CLK_DIVIDER_ONE_BASED;

	if (setup->flags & CLKF_INDEX_POWER_OF_TWO)
		div->flags |= CLK_DIVIDER_POWER_OF_TWO;

	div->table = _get_div_table_from_setup(setup, &div->width);
	if (IS_ERR(div->table)) {
		ret = PTR_ERR(div->table);
		kfree(div);
		return ERR_PTR(ret);
	}


	div->shift = setup->bit_shift;
	div->latch = -EINVAL;

	return &div->hw;
}