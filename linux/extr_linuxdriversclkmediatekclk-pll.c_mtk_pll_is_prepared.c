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
struct mtk_clk_pll {scalar_t__ base_addr; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int CON0_BASE_EN ; 
 scalar_t__ REG_CON0 ; 
 int readl (scalar_t__) ; 
 struct mtk_clk_pll* to_mtk_clk_pll (struct clk_hw*) ; 

__attribute__((used)) static int mtk_pll_is_prepared(struct clk_hw *hw)
{
	struct mtk_clk_pll *pll = to_mtk_clk_pll(hw);

	return (readl(pll->base_addr + REG_CON0) & CON0_BASE_EN) != 0;
}