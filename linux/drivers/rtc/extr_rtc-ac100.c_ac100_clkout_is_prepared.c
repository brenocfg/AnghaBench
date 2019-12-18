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
struct ac100_clkout {int /*<<< orphan*/  offset; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 unsigned int AC100_CLKOUT_EN ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 struct ac100_clkout* to_ac100_clkout (struct clk_hw*) ; 

__attribute__((used)) static int ac100_clkout_is_prepared(struct clk_hw *hw)
{
	struct ac100_clkout *clk = to_ac100_clkout(hw);
	unsigned int reg;

	regmap_read(clk->regmap, clk->offset, &reg);

	return reg & AC100_CLKOUT_EN;
}