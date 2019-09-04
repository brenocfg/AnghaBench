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
struct clk_rm9200_main {int /*<<< orphan*/  regmap; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int clk_main_probe_frequency (int /*<<< orphan*/ ) ; 
 struct clk_rm9200_main* to_clk_rm9200_main (struct clk_hw*) ; 

__attribute__((used)) static int clk_rm9200_main_prepare(struct clk_hw *hw)
{
	struct clk_rm9200_main *clkmain = to_clk_rm9200_main(hw);

	return clk_main_probe_frequency(clkmain->regmap);
}