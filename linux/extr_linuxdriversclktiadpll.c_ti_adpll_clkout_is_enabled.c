#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct clk_hw {int dummy; } ;
struct TYPE_3__ {struct clk_hw hw; } ;
struct ti_adpll_clkout_data {TYPE_1__ gate; } ;
struct TYPE_4__ {int (* is_enabled ) (struct clk_hw*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  __clk_hw_set_clk (struct clk_hw*,struct clk_hw*) ; 
 TYPE_2__ clk_gate_ops ; 
 int stub1 (struct clk_hw*) ; 
 struct ti_adpll_clkout_data* to_clkout (struct clk_hw*) ; 

__attribute__((used)) static int ti_adpll_clkout_is_enabled(struct clk_hw *hw)
{
	struct ti_adpll_clkout_data *co = to_clkout(hw);
	struct clk_hw *gate_hw = &co->gate.hw;

	__clk_hw_set_clk(gate_hw, hw);

	return clk_gate_ops.is_enabled(gate_hw);
}