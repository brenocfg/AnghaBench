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
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_branch_check_halt ; 
 int /*<<< orphan*/  clk_branch_toggle (struct clk_hw*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void clk_branch_disable(struct clk_hw *hw)
{
	clk_branch_toggle(hw, false, clk_branch_check_halt);
}