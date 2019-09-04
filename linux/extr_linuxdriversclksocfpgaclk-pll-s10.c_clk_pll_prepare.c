#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  reg; } ;
struct socfpga_pll {TYPE_1__ hw; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOCFPGA_PLL_RESET_MASK ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 
 struct socfpga_pll* to_socfpga_clk (struct clk_hw*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int clk_pll_prepare(struct clk_hw *hwclk)
{
	struct socfpga_pll *socfpgaclk = to_socfpga_clk(hwclk);
	u32 reg;

	/* Bring PLL out of reset */
	reg = readl(socfpgaclk->hw.reg);
	reg |= SOCFPGA_PLL_RESET_MASK;
	writel(reg, socfpgaclk->hw.reg);

	return 0;
}