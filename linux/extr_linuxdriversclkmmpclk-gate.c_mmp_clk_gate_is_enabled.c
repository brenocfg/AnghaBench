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
struct mmp_clk_gate {int mask; int val_enable; scalar_t__ lock; int /*<<< orphan*/  reg; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (scalar_t__,unsigned long) ; 
 struct mmp_clk_gate* to_clk_mmp_gate (struct clk_hw*) ; 

__attribute__((used)) static int mmp_clk_gate_is_enabled(struct clk_hw *hw)
{
	struct mmp_clk_gate *gate = to_clk_mmp_gate(hw);
	unsigned long flags = 0;
	u32 tmp;

	if (gate->lock)
		spin_lock_irqsave(gate->lock, flags);

	tmp = readl(gate->reg);

	if (gate->lock)
		spin_unlock_irqrestore(gate->lock, flags);

	return (tmp & gate->mask) == gate->val_enable;
}