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
struct clk_divider {int dummy; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 struct clk_hw* __clk_get_hw (struct clk*) ; 
 int /*<<< orphan*/  clk_unregister (struct clk*) ; 
 int /*<<< orphan*/  kfree (struct clk_divider*) ; 
 struct clk_divider* to_clk_divider (struct clk_hw*) ; 

void clk_unregister_divider(struct clk *clk)
{
	struct clk_divider *div;
	struct clk_hw *hw;

	hw = __clk_get_hw(clk);
	if (!hw)
		return;

	div = to_clk_divider(hw);

	clk_unregister(clk);
	kfree(div);
}