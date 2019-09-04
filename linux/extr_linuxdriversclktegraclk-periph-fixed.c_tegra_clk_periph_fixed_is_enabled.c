#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct tegra_clk_periph_fixed {int num; TYPE_1__* regs; scalar_t__ base; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {scalar_t__ rst_reg; scalar_t__ enb_reg; } ;

/* Variables and functions */
 int readl (scalar_t__) ; 
 struct tegra_clk_periph_fixed* to_tegra_clk_periph_fixed (struct clk_hw*) ; 

__attribute__((used)) static int tegra_clk_periph_fixed_is_enabled(struct clk_hw *hw)
{
	struct tegra_clk_periph_fixed *fixed = to_tegra_clk_periph_fixed(hw);
	u32 mask = 1 << (fixed->num % 32), value;

	value = readl(fixed->base + fixed->regs->enb_reg);
	if (value & mask) {
		value = readl(fixed->base + fixed->regs->rst_reg);
		if ((value & mask) == 0)
			return 1;
	}

	return 0;
}