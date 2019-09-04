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
struct clk_pll {int id; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ SRC_PLLCR ; 
 int SRC_PLLCR_PLL1EN ; 
 int SRC_PLLCR_PLL1OVER ; 
 int SRC_PLLCR_PLL2EN ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ src_base ; 
 int /*<<< orphan*/  src_lock ; 
 struct clk_pll* to_pll (struct clk_hw*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void pll_clk_disable(struct clk_hw *hw)
{
	struct clk_pll *pll = to_pll(hw);
	u32 val;

	spin_lock(&src_lock);
	val = readl(src_base + SRC_PLLCR);
	if (pll->id == 1) {
		if (val & SRC_PLLCR_PLL1OVER) {
			val &= ~SRC_PLLCR_PLL1EN;
			writel(val, src_base + SRC_PLLCR);
		}
	} else if (pll->id == 2) {
		val &= ~SRC_PLLCR_PLL2EN;
		writel(val, src_base + SRC_PLLCR);
	}
	spin_unlock(&src_lock);
}