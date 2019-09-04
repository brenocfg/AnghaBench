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
struct mmp_clk_gate {int flags; scalar_t__ lock; int /*<<< orphan*/  reg; int /*<<< orphan*/  val_enable; int /*<<< orphan*/  mask; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int MMP_CLK_GATE_NEED_DELAY ; 
 unsigned long clk_hw_get_rate (struct clk_hw*) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (scalar_t__,unsigned long) ; 
 struct mmp_clk_gate* to_clk_mmp_gate (struct clk_hw*) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mmp_clk_gate_enable(struct clk_hw *hw)
{
	struct mmp_clk_gate *gate = to_clk_mmp_gate(hw);
	unsigned long flags = 0;
	unsigned long rate;
	u32 tmp;

	if (gate->lock)
		spin_lock_irqsave(gate->lock, flags);

	tmp = readl(gate->reg);
	tmp &= ~gate->mask;
	tmp |= gate->val_enable;
	writel(tmp, gate->reg);

	if (gate->lock)
		spin_unlock_irqrestore(gate->lock, flags);

	if (gate->flags & MMP_CLK_GATE_NEED_DELAY) {
		rate = clk_hw_get_rate(hw);
		/* Need delay 2 cycles. */
		udelay(2000000/rate);
	}

	return 0;
}