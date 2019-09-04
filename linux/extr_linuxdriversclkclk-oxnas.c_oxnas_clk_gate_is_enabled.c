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
struct clk_oxnas_gate {int /*<<< orphan*/  bit; int /*<<< orphan*/  regmap; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 unsigned int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLK_STAT_REGOFFSET ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 struct clk_oxnas_gate* to_clk_oxnas_gate (struct clk_hw*) ; 

__attribute__((used)) static int oxnas_clk_gate_is_enabled(struct clk_hw *hw)
{
	struct clk_oxnas_gate *std = to_clk_oxnas_gate(hw);
	int ret;
	unsigned int val;

	ret = regmap_read(std->regmap, CLK_STAT_REGOFFSET, &val);
	if (ret < 0)
		return ret;

	return val & BIT(std->bit);
}