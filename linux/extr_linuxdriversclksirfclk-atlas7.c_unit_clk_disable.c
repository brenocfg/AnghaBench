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
typedef  int u32 ;
struct clk_unit {int regofs; scalar_t__ type; int /*<<< orphan*/  lock; int /*<<< orphan*/  bit; int /*<<< orphan*/  idle_bit; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ CLK_UNIT_NOC_CLOCK ; 
 scalar_t__ CLK_UNIT_NOC_SOCKET ; 
 int SIRFSOC_CLKC_ROOT_CLK_EN0_CLR ; 
 int SIRFSOC_CLKC_ROOT_CLK_EN0_SET ; 
 int SIRFSOC_NOC_CLK_IDLEREQ_CLR ; 
 int SIRFSOC_NOC_CLK_IDLEREQ_SET ; 
 int /*<<< orphan*/  SIRFSOC_NOC_CLK_IDLE_STATUS ; 
 int SIRFSOC_NOC_CLK_SLVRDY_CLR ; 
 int clkc_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clkc_writel (int,int) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 struct clk_unit* to_unitclk (struct clk_hw*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void unit_clk_disable(struct clk_hw *hw)
{
	u32 reg;
	u32 i = 0;
	struct clk_unit *clk = to_unitclk(hw);
	unsigned long flags;

	reg = clk->regofs + SIRFSOC_CLKC_ROOT_CLK_EN0_CLR - SIRFSOC_CLKC_ROOT_CLK_EN0_SET;
	spin_lock_irqsave(clk->lock, flags);
	if (clk->type == CLK_UNIT_NOC_CLOCK) {
		clkc_writel(BIT(clk->idle_bit), SIRFSOC_NOC_CLK_IDLEREQ_SET);
		while (!(clkc_readl(SIRFSOC_NOC_CLK_IDLE_STATUS) &
				BIT(clk->idle_bit)) && (i++ < 100)) {
			cpu_relax();
			udelay(10);
		}

		if (i == 100) {
			pr_err("unit NoC Clock disconnect Error:timeout\n");
			/*once timeout, undo idlereq by CLR*/
			clkc_writel(BIT(clk->idle_bit), SIRFSOC_NOC_CLK_IDLEREQ_CLR);
			goto err;
		}

	} else if (clk->type == CLK_UNIT_NOC_SOCKET)
		clkc_writel(BIT(clk->idle_bit), SIRFSOC_NOC_CLK_SLVRDY_CLR);

	clkc_writel(BIT(clk->bit), reg);
err:
	spin_unlock_irqrestore(clk->lock, flags);
}