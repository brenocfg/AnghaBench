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
struct clk_hw {TYPE_1__* init; } ;
struct clk_dmn {int /*<<< orphan*/  regofs; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int BIT (int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  WARN_ON (unsigned long) ; 
 int clkc_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clkc_writel (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 struct clk_dmn* to_dmnclk (struct clk_hw*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int dmn_clk_set_rate(struct clk_hw *hw, unsigned long rate,
	unsigned long parent_rate)
{
	struct clk_dmn *clk = to_dmnclk(hw);
	unsigned long fin;
	unsigned ratio, wait, hold, reg;
	unsigned bits = (strcmp(hw->init->name, "mem") == 0) ? 3 : 4;

	fin = parent_rate;
	ratio = fin / rate;

	if (unlikely(ratio < 2 || ratio > BIT(bits + 1)))
		return -EINVAL;

	WARN_ON(fin % rate);

	wait = (ratio >> 1) - 1;
	hold = ratio - wait - 2;

	reg = clkc_readl(clk->regofs);
	reg &= ~(((BIT(bits) - 1) << 16) | ((BIT(bits) - 1) << 20));
	reg |= (wait << 16) | (hold << 20) | BIT(25);
	clkc_writel(reg, clk->regofs);

	/* waiting FCD been effective */
	while (clkc_readl(clk->regofs) & BIT(25))
		cpu_relax();

	return 0;
}