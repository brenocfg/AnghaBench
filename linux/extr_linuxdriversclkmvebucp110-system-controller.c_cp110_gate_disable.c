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
struct cp110_gate_clk {int /*<<< orphan*/  bit_idx; int /*<<< orphan*/  regmap; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CP110_PM_CLOCK_GATING_REG ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cp110_gate_clk* to_cp110_gate_clk (struct clk_hw*) ; 

__attribute__((used)) static void cp110_gate_disable(struct clk_hw *hw)
{
	struct cp110_gate_clk *gate = to_cp110_gate_clk(hw);

	regmap_update_bits(gate->regmap, CP110_PM_CLOCK_GATING_REG,
			   BIT(gate->bit_idx), 0);
}