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
typedef  int /*<<< orphan*/  u32 ;
struct clk_unit {scalar_t__ type; int /*<<< orphan*/  lock; int /*<<< orphan*/  idle_bit; int /*<<< orphan*/  bit; int /*<<< orphan*/  regofs; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ CLK_UNIT_NOC_CLOCK ; 
 scalar_t__ CLK_UNIT_NOC_SOCKET ; 
 int /*<<< orphan*/  SIRFSOC_NOC_CLK_IDLEREQ_CLR ; 
 int /*<<< orphan*/  SIRFSOC_NOC_CLK_SLVRDY_SET ; 
 int /*<<< orphan*/  clkc_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 struct clk_unit* to_unitclk (struct clk_hw*) ; 

__attribute__((used)) static int unit_clk_enable(struct clk_hw *hw)
{
	u32 reg;
	struct clk_unit *clk = to_unitclk(hw);
	unsigned long flags;

	reg = clk->regofs;

	spin_lock_irqsave(clk->lock, flags);
	clkc_writel(BIT(clk->bit), reg);
	if (clk->type == CLK_UNIT_NOC_CLOCK)
		clkc_writel(BIT(clk->idle_bit), SIRFSOC_NOC_CLK_IDLEREQ_CLR);
	else if (clk->type == CLK_UNIT_NOC_SOCKET)
		clkc_writel(BIT(clk->idle_bit), SIRFSOC_NOC_CLK_SLVRDY_SET);

	spin_unlock_irqrestore(clk->lock, flags);
	return 0;
}