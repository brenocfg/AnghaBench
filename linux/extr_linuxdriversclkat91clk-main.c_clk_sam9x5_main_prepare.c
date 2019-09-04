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
struct regmap {int dummy; } ;
struct clk_sam9x5_main {struct regmap* regmap; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int clk_main_probe_frequency (struct regmap*) ; 
 int /*<<< orphan*/  clk_sam9x5_main_ready (struct regmap*) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 struct clk_sam9x5_main* to_clk_sam9x5_main (struct clk_hw*) ; 

__attribute__((used)) static int clk_sam9x5_main_prepare(struct clk_hw *hw)
{
	struct clk_sam9x5_main *clkmain = to_clk_sam9x5_main(hw);
	struct regmap *regmap = clkmain->regmap;

	while (!clk_sam9x5_main_ready(regmap))
		cpu_relax();

	return clk_main_probe_frequency(regmap);
}