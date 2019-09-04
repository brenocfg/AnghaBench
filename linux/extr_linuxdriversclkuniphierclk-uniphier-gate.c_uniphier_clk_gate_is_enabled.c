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
struct uniphier_clk_gate {int /*<<< orphan*/  bit; int /*<<< orphan*/  reg; int /*<<< orphan*/  regmap; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 unsigned int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 scalar_t__ regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 struct uniphier_clk_gate* to_uniphier_clk_gate (struct clk_hw*) ; 

__attribute__((used)) static int uniphier_clk_gate_is_enabled(struct clk_hw *hw)
{
	struct uniphier_clk_gate *gate = to_uniphier_clk_gate(hw);
	unsigned int val;

	if (regmap_read(gate->regmap, gate->reg, &val) < 0)
		pr_warn("is_enabled() may return wrong result\n");

	return !!(val & BIT(gate->bit));
}