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
struct clk_hw {int dummy; } ;
struct aspeed_clk_gate {long flags; int /*<<< orphan*/  lock; int /*<<< orphan*/  map; int /*<<< orphan*/  clock_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASPEED_CLK_STOP_CTRL ; 
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 long CLK_GATE_SET_TO_DISABLE ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 struct aspeed_clk_gate* to_aspeed_clk_gate (struct clk_hw*) ; 

__attribute__((used)) static void aspeed_clk_disable(struct clk_hw *hw)
{
	struct aspeed_clk_gate *gate = to_aspeed_clk_gate(hw);
	unsigned long flags;
	u32 clk = BIT(gate->clock_idx);
	u32 enval;

	spin_lock_irqsave(gate->lock, flags);

	enval = (gate->flags & CLK_GATE_SET_TO_DISABLE) ? clk : 0;
	regmap_update_bits(gate->map, ASPEED_CLK_STOP_CTRL, clk, enval);

	spin_unlock_irqrestore(gate->lock, flags);
}