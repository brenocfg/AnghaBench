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
struct clk_sysctrl {int /*<<< orphan*/  parent_index; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 struct clk_sysctrl* to_clk_sysctrl (struct clk_hw*) ; 

__attribute__((used)) static u8 clk_sysctrl_get_parent(struct clk_hw *hw)
{
	struct clk_sysctrl *clk = to_clk_sysctrl(hw);
	return clk->parent_index;
}