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
struct pic32_sys_clk {int slew_div; TYPE_1__* core; int /*<<< orphan*/  slew_reg; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 int SLEW_DIV ; 
 int SLEW_DIV_SHIFT ; 
 int SLEW_DOWNEN ; 
 int SLEW_UPEN ; 
 struct pic32_sys_clk* clkhw_to_sys_clk (struct clk_hw*) ; 
 struct clk_hw* pic32_sclk_hw ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sclk_init(struct clk_hw *hw)
{
	struct pic32_sys_clk *sclk = clkhw_to_sys_clk(hw);
	unsigned long flags;
	u32 v;

	/* Maintain reference to this clk, required in spll_clk_set_rate() */
	pic32_sclk_hw = hw;

	/* apply slew divider on both up and down scaling */
	if (sclk->slew_div) {
		spin_lock_irqsave(&sclk->core->reg_lock, flags);
		v = readl(sclk->slew_reg);
		v &= ~(SLEW_DIV << SLEW_DIV_SHIFT);
		v |= sclk->slew_div << SLEW_DIV_SHIFT;
		v |= SLEW_DOWNEN | SLEW_UPEN;
		writel(v, sclk->slew_reg);
		spin_unlock_irqrestore(&sclk->core->reg_lock, flags);
	}
}