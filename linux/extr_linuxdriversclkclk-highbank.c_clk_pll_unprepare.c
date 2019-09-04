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
struct hb_clk {int /*<<< orphan*/  reg; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HB_PLL_RESET ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 
 struct hb_clk* to_hb_clk (struct clk_hw*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void clk_pll_unprepare(struct clk_hw *hwclk)
{
	struct hb_clk *hbclk = to_hb_clk(hwclk);
	u32 reg;

	reg = readl(hbclk->reg);
	reg |= HB_PLL_RESET;
	writel(reg, hbclk->reg);
}