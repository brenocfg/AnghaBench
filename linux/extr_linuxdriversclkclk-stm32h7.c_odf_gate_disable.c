#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct clk_hw {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* disable ) (struct clk_hw*) ;int /*<<< orphan*/  (* is_enabled ) (struct clk_hw*) ;} ;

/* Variables and functions */
 TYPE_1__ clk_gate_ops ; 
 struct clk_hw* clk_hw_get_parent (struct clk_hw*) ; 
 int /*<<< orphan*/  pll_disable (struct clk_hw*) ; 
 int /*<<< orphan*/  pll_enable (struct clk_hw*) ; 
 int pll_is_enabled (struct clk_hw*) ; 
 int /*<<< orphan*/  stub1 (struct clk_hw*) ; 
 int /*<<< orphan*/  stub2 (struct clk_hw*) ; 

__attribute__((used)) static void odf_gate_disable(struct clk_hw *hw)
{
	struct clk_hw *hwp;
	int pll_status;

	if (!clk_gate_ops.is_enabled(hw))
		return;

	hwp = clk_hw_get_parent(hw);

	pll_status = pll_is_enabled(hwp);

	if (pll_status)
		pll_disable(hwp);

	clk_gate_ops.disable(hw);

	if (pll_status)
		pll_enable(hwp);
}