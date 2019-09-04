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
struct flexgen {TYPE_1__ fgate; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* disable ) (struct clk_hw*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  __clk_hw_set_clk (struct clk_hw*,struct clk_hw*) ; 
 TYPE_2__ clk_gate_ops ; 
 int /*<<< orphan*/  clk_hw_get_name (struct clk_hw*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct clk_hw*) ; 
 struct flexgen* to_flexgen (struct clk_hw*) ; 

__attribute__((used)) static void flexgen_disable(struct clk_hw *hw)
{
	struct flexgen *flexgen = to_flexgen(hw);
	struct clk_hw *fgate_hw = &flexgen->fgate.hw;

	/* disable only the final gate */
	__clk_hw_set_clk(fgate_hw, hw);

	clk_gate_ops.disable(fgate_hw);

	pr_debug("%s: flexgen output disabled\n", clk_hw_get_name(hw));
}