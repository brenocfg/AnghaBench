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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct tegra_sdmmc_mux {int /*<<< orphan*/  reg; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int SDMMC_MUL ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 int get_div_field (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl_relaxed (int /*<<< orphan*/ ) ; 
 struct tegra_sdmmc_mux* to_clk_sdmmc_mux (struct clk_hw*) ; 

__attribute__((used)) static unsigned long clk_sdmmc_mux_recalc_rate(struct clk_hw *hw,
					       unsigned long parent_rate)
{
	struct tegra_sdmmc_mux *sdmmc_mux = to_clk_sdmmc_mux(hw);
	u32 val;
	int div;
	u64 rate = parent_rate;

	val = readl_relaxed(sdmmc_mux->reg);
	div = get_div_field(val);

	div += SDMMC_MUL;

	rate *= SDMMC_MUL;
	rate += div - 1;
	do_div(rate, div);

	return rate;
}