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
struct clk_hw {int /*<<< orphan*/ * core; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_core_reparent (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void clk_hw_reparent(struct clk_hw *hw, struct clk_hw *new_parent)
{
	if (!hw)
		return;

	clk_core_reparent(hw->core, !new_parent ? NULL : new_parent->core);
}