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
struct clk_main_rc_osc {unsigned long accuracy; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 struct clk_main_rc_osc* to_clk_main_rc_osc (struct clk_hw*) ; 

__attribute__((used)) static unsigned long clk_main_rc_osc_recalc_accuracy(struct clk_hw *hw,
						     unsigned long parent_acc)
{
	struct clk_main_rc_osc *osc = to_clk_main_rc_osc(hw);

	return osc->accuracy;
}