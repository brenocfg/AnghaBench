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
typedef  int u32 ;
struct ti_clk_mux {int num_parents; int flags; int /*<<< orphan*/  bit_shift; int /*<<< orphan*/  parents; int /*<<< orphan*/  reg; int /*<<< orphan*/  module; } ;
struct ti_clk {int /*<<< orphan*/  name; struct ti_clk_mux* data; } ;
struct clk_omap_reg {int /*<<< orphan*/ * ptr; int /*<<< orphan*/  offset; int /*<<< orphan*/  index; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int CLKF_INDEX_STARTS_AT_ONE ; 
 int CLKF_SET_RATE_PARENT ; 
 int /*<<< orphan*/  CLK_MUX_INDEX_ONE ; 
 int CLK_SET_RATE_NO_REPARENT ; 
 int CLK_SET_RATE_PARENT ; 
 int /*<<< orphan*/  EINVAL ; 
 struct clk* _register_mux (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct clk_omap_reg*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int fls (int) ; 

struct clk *ti_clk_register_mux(struct ti_clk *setup)
{
	struct ti_clk_mux *mux;
	u32 flags;
	u8 mux_flags = 0;
	struct clk_omap_reg reg;
	u32 mask;

	mux = setup->data;
	flags = CLK_SET_RATE_NO_REPARENT;

	mask = mux->num_parents;
	if (!(mux->flags & CLKF_INDEX_STARTS_AT_ONE))
		mask--;

	mask = (1 << fls(mask)) - 1;
	reg.index = mux->module;
	reg.offset = mux->reg;
	reg.ptr = NULL;

	if (mux->flags & CLKF_INDEX_STARTS_AT_ONE)
		mux_flags |= CLK_MUX_INDEX_ONE;

	if (mux->flags & CLKF_SET_RATE_PARENT)
		flags |= CLK_SET_RATE_PARENT;

	return _register_mux(NULL, setup->name, mux->parents, mux->num_parents,
			     flags, &reg, mux->bit_shift, mask, -EINVAL,
			     mux_flags, NULL);
}