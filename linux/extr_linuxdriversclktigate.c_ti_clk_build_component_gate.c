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
struct ti_clk_gate {int flags; int /*<<< orphan*/  bit_shift; int /*<<< orphan*/  reg; int /*<<< orphan*/  module; } ;
struct clk_omap_reg {int /*<<< orphan*/  offset; int /*<<< orphan*/  index; } ;
struct clk_hw_omap_ops {int dummy; } ;
struct clk_hw {int dummy; } ;
struct clk_hw_omap {struct clk_hw hw; struct clk_hw_omap_ops const* ops; int /*<<< orphan*/  enable_bit; int /*<<< orphan*/  enable_reg; } ;

/* Variables and functions */
 int CLKF_INTERFACE ; 
 int CLKF_NO_WAIT ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct clk_hw* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct clk_hw_omap_ops clkhwops_iclk_wait ; 
 struct clk_hw_omap_ops clkhwops_wait ; 
 struct clk_hw_omap* kzalloc (int,int /*<<< orphan*/ ) ; 

struct clk_hw *ti_clk_build_component_gate(struct ti_clk_gate *setup)
{
	struct clk_hw_omap *gate;
	struct clk_omap_reg *reg;
	const struct clk_hw_omap_ops *ops = &clkhwops_wait;

	if (!setup)
		return NULL;

	gate = kzalloc(sizeof(*gate), GFP_KERNEL);
	if (!gate)
		return ERR_PTR(-ENOMEM);

	reg = (struct clk_omap_reg *)&gate->enable_reg;
	reg->index = setup->module;
	reg->offset = setup->reg;

	gate->enable_bit = setup->bit_shift;

	if (setup->flags & CLKF_NO_WAIT)
		ops = NULL;

	if (setup->flags & CLKF_INTERFACE)
		ops = &clkhwops_iclk_wait;

	gate->ops = ops;

	return &gate->hw;
}