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
struct TYPE_2__ {int (* set_rate ) (struct clk_hw*,unsigned long,unsigned long) ;} ;

/* Variables and functions */
 TYPE_1__ clk_divider_ops ; 
 struct clk_hw* clk_hw_get_parent (struct clk_hw*) ; 
 int /*<<< orphan*/  pll_disable (struct clk_hw*) ; 
 int /*<<< orphan*/  pll_enable (struct clk_hw*) ; 
 int pll_is_enabled (struct clk_hw*) ; 
 int stub1 (struct clk_hw*,unsigned long,unsigned long) ; 

__attribute__((used)) static int odf_divider_set_rate(struct clk_hw *hw, unsigned long rate,
		unsigned long parent_rate)
{
	struct clk_hw *hwp;
	int pll_status;
	int ret;

	hwp = clk_hw_get_parent(hw);

	pll_status = pll_is_enabled(hwp);

	if (pll_status)
		pll_disable(hwp);

	ret = clk_divider_ops.set_rate(hw, rate, parent_rate);

	if (pll_status)
		pll_enable(hwp);

	return ret;
}