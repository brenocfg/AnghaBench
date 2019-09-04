#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_3__ {int /*<<< orphan*/  reg; } ;
struct socfpga_periph_clk {TYPE_1__ hw; } ;
struct clk_hw {TYPE_2__* init; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int CLK_MGR_FREE_MASK ; 
 int CLK_MGR_FREE_SHIFT ; 
 int /*<<< orphan*/  SOCFPGA_MPU_FREE_CLK ; 
 int /*<<< orphan*/  SOCFPGA_NOC_FREE_CLK ; 
 int /*<<< orphan*/  SOCFPGA_SDMMC_FREE_CLK ; 
 int readl (int /*<<< orphan*/ ) ; 
 scalar_t__ streq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct socfpga_periph_clk* to_socfpga_periph_clk (struct clk_hw*) ; 

__attribute__((used)) static u8 clk_periclk_get_parent(struct clk_hw *hwclk)
{
	struct socfpga_periph_clk *socfpgaclk = to_socfpga_periph_clk(hwclk);
	u32 clk_src;

	clk_src = readl(socfpgaclk->hw.reg);
	if (streq(hwclk->init->name, SOCFPGA_MPU_FREE_CLK) ||
	    streq(hwclk->init->name, SOCFPGA_NOC_FREE_CLK) ||
	    streq(hwclk->init->name, SOCFPGA_SDMMC_FREE_CLK))
		return (clk_src >> CLK_MGR_FREE_SHIFT) &
			CLK_MGR_FREE_MASK;
	else
		return 0;
}