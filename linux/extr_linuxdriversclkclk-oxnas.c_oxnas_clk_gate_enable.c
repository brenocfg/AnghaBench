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
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLK_SET_REGOFFSET ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct clk_oxnas_gate* to_clk_oxnas_gate (struct clk_hw*) ; 

__attribute__((used)) static int oxnas_clk_gate_enable(struct clk_hw *hw)
{
	struct clk_oxnas_gate *std = to_clk_oxnas_gate(hw);

	regmap_write(std->regmap, CLK_SET_REGOFFSET, BIT(std->bit));

	return 0;
}