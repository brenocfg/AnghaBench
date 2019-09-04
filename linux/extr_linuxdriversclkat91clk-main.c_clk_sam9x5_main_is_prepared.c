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
 int clk_sam9x5_main_ready (int /*<<< orphan*/ ) ; 
 struct clk_sam9x5_main* to_clk_sam9x5_main (struct clk_hw*) ; 

__attribute__((used)) static int clk_sam9x5_main_is_prepared(struct clk_hw *hw)
{
	struct clk_sam9x5_main *clkmain = to_clk_sam9x5_main(hw);

	return clk_sam9x5_main_ready(clkmain->regmap);
}