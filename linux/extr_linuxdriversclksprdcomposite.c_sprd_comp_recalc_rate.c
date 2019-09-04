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
struct sprd_comp {int /*<<< orphan*/  div; int /*<<< orphan*/  common; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 struct sprd_comp* hw_to_sprd_comp (struct clk_hw*) ; 
 unsigned long sprd_div_helper_recalc_rate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static unsigned long sprd_comp_recalc_rate(struct clk_hw *hw,
					  unsigned long parent_rate)
{
	struct sprd_comp *cc = hw_to_sprd_comp(hw);

	return sprd_div_helper_recalc_rate(&cc->common, &cc->div, parent_rate);
}