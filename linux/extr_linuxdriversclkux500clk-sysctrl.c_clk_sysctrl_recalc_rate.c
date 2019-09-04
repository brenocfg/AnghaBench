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
struct clk_sysctrl {unsigned long rate; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 struct clk_sysctrl* to_clk_sysctrl (struct clk_hw*) ; 

__attribute__((used)) static unsigned long clk_sysctrl_recalc_rate(struct clk_hw *hw,
					unsigned long parent_rate)
{
	struct clk_sysctrl *clk = to_clk_sysctrl(hw);
	return clk->rate;
}