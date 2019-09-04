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
struct clk_pllv3 {int div_shift; int div_mask; int /*<<< orphan*/  base; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int readl_relaxed (int /*<<< orphan*/ ) ; 
 struct clk_pllv3* to_clk_pllv3 (struct clk_hw*) ; 

__attribute__((used)) static unsigned long clk_pllv3_recalc_rate(struct clk_hw *hw,
					   unsigned long parent_rate)
{
	struct clk_pllv3 *pll = to_clk_pllv3(hw);
	u32 div = (readl_relaxed(pll->base) >> pll->div_shift)  & pll->div_mask;

	return (div == 1) ? parent_rate * 22 : parent_rate * 20;
}