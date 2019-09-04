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

/* Variables and functions */
 int CLK_GATE_SET_TO_DISABLE ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void clk_gate_toggle(const struct sprd_gate *sg, bool en)
{
	const struct sprd_clk_common *common = &sg->common;
	unsigned int reg;
	bool set = sg->flags & CLK_GATE_SET_TO_DISABLE ? true : false;

	set ^= en;

	regmap_read(common->regmap, common->reg, &reg);

	if (set)
		reg |= sg->enable_mask;
	else
		reg &= ~sg->enable_mask;

	regmap_write(common->regmap, common->reg, reg);
}