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
struct stm32_pll_obj {int /*<<< orphan*/  lock; int /*<<< orphan*/  reg; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PLL_ON ; 
 int /*<<< orphan*/  readl_relaxed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 struct stm32_pll_obj* to_pll (struct clk_hw*) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pll_disable(struct clk_hw *hw)
{
	struct stm32_pll_obj *clk_elem = to_pll(hw);
	u32 reg;
	unsigned long flags = 0;

	spin_lock_irqsave(clk_elem->lock, flags);

	reg = readl_relaxed(clk_elem->reg);
	reg &= ~PLL_ON;
	writel_relaxed(reg, clk_elem->reg);

	spin_unlock_irqrestore(clk_elem->lock, flags);
}