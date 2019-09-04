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
struct sprd_clk_common {int /*<<< orphan*/  reg; int /*<<< orphan*/  regmap; } ;
struct sprd_gate {int flags; unsigned int enable_mask; struct sprd_clk_common common; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int CLK_GATE_SET_TO_DISABLE ; 
 struct sprd_gate* hw_to_sprd_gate (struct clk_hw*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int sprd_gate_is_enabled(struct clk_hw *hw)
{
	struct sprd_gate *sg = hw_to_sprd_gate(hw);
	struct sprd_clk_common *common = &sg->common;
	unsigned int reg;

	regmap_read(common->regmap, common->reg, &reg);

	if (sg->flags & CLK_GATE_SET_TO_DISABLE)
		reg ^= sg->enable_mask;

	reg &= sg->enable_mask;

	return reg ? 1 : 0;
}