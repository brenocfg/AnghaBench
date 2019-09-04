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
struct samsung_clk_pll {int /*<<< orphan*/  con_reg; int /*<<< orphan*/  lock_offs; int /*<<< orphan*/  enable_offs; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int readl_relaxed (int /*<<< orphan*/ ) ; 
 struct samsung_clk_pll* to_clk_pll (struct clk_hw*) ; 
 int /*<<< orphan*/  writel_relaxed (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int samsung_pll3xxx_enable(struct clk_hw *hw)
{
	struct samsung_clk_pll *pll = to_clk_pll(hw);
	u32 tmp;

	tmp = readl_relaxed(pll->con_reg);
	tmp |= BIT(pll->enable_offs);
	writel_relaxed(tmp, pll->con_reg);

	/* wait lock time */
	do {
		cpu_relax();
		tmp = readl_relaxed(pll->con_reg);
	} while (!(tmp & BIT(pll->lock_offs)));

	return 0;
}