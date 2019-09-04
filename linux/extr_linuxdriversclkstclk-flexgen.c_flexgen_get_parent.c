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
typedef  int /*<<< orphan*/  u8 ;
struct clk_hw {int dummy; } ;
struct TYPE_3__ {struct clk_hw hw; } ;
struct flexgen {TYPE_1__ mux; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* get_parent ) (struct clk_hw*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  __clk_hw_set_clk (struct clk_hw*,struct clk_hw*) ; 
 TYPE_2__ clk_mux_ops ; 
 int /*<<< orphan*/  stub1 (struct clk_hw*) ; 
 struct flexgen* to_flexgen (struct clk_hw*) ; 

__attribute__((used)) static u8 flexgen_get_parent(struct clk_hw *hw)
{
	struct flexgen *flexgen = to_flexgen(hw);
	struct clk_hw *mux_hw = &flexgen->mux.hw;

	__clk_hw_set_clk(mux_hw, hw);

	return clk_mux_ops.get_parent(mux_hw);
}