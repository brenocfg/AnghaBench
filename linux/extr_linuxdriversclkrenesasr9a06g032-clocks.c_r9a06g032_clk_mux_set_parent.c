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
struct r9a06g032_clk_bitsel {int /*<<< orphan*/  selector; int /*<<< orphan*/  clocks; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_rdesc_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct r9a06g032_clk_bitsel* to_clk_bitselect (struct clk_hw*) ; 

__attribute__((used)) static int r9a06g032_clk_mux_set_parent(struct clk_hw *hw, u8 index)
{
	struct r9a06g032_clk_bitsel *set = to_clk_bitselect(hw);

	/* a single bit in the register selects one of two parent clocks */
	clk_rdesc_set(set->clocks, set->selector, !!index);

	return 0;
}