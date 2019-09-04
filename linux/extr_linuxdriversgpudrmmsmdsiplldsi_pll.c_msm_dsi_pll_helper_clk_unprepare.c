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
struct msm_dsi_pll {int dummy; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dsi_pll_disable (struct msm_dsi_pll*) ; 
 struct msm_dsi_pll* hw_clk_to_pll (struct clk_hw*) ; 

void msm_dsi_pll_helper_clk_unprepare(struct clk_hw *hw)
{
	struct msm_dsi_pll *pll = hw_clk_to_pll(hw);

	dsi_pll_disable(pll);
}