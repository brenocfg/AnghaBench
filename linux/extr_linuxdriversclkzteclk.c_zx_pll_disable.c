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
struct clk_zx_pll {int pd_bit; int /*<<< orphan*/  reg_base; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int readl_relaxed (int /*<<< orphan*/ ) ; 
 struct clk_zx_pll* to_clk_zx_pll (struct clk_hw*) ; 
 int /*<<< orphan*/  writel_relaxed (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zx_pll_disable(struct clk_hw *hw)
{
	struct clk_zx_pll *zx_pll = to_clk_zx_pll(hw);
	u32 reg;

	if (zx_pll->pd_bit > 31)
		return;

	reg = readl_relaxed(zx_pll->reg_base);
	writel_relaxed(reg | BIT(zx_pll->pd_bit), zx_pll->reg_base);
}