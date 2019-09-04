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
struct TYPE_4__ {int (* set_parent ) (struct clk_hw*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  __clk_hw_set_clk (struct clk_hw*,struct clk_hw*) ; 
 TYPE_2__ clk_mux_ops ; 
 int stub1 (struct clk_hw*,int /*<<< orphan*/ ) ; 
 struct flexgen* to_flexgen (struct clk_hw*) ; 

__attribute__((used)) static int flexgen_set_parent(struct clk_hw *hw, u8 index)
{
	struct flexgen *flexgen = to_flexgen(hw);
	struct clk_hw *mux_hw = &flexgen->mux.hw;

	__clk_hw_set_clk(mux_hw, hw);

	return clk_mux_ops.set_parent(mux_hw, index);
}