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
struct clk_sam9x5_main {int /*<<< orphan*/  regmap; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 unsigned long clk_main_recalc_rate (int /*<<< orphan*/ ,unsigned long) ; 
 struct clk_sam9x5_main* to_clk_sam9x5_main (struct clk_hw*) ; 

__attribute__((used)) static unsigned long clk_sam9x5_main_recalc_rate(struct clk_hw *hw,
						 unsigned long parent_rate)
{
	struct clk_sam9x5_main *clkmain = to_clk_sam9x5_main(hw);

	return clk_main_recalc_rate(clkmain->regmap, parent_rate);
}