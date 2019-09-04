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
typedef  int /*<<< orphan*/  u8 ;
struct tegra_clk_pll {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int _p_div_to_hw (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int tegra_pll_p_div_to_hw(struct tegra_clk_pll *pll, u8 p_div)
{
	return _p_div_to_hw(&pll->hw, p_div);
}