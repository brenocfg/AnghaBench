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
struct dsi_pll_28nm {int dummy; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  POLL_MAX_READS ; 
 int /*<<< orphan*/  POLL_TIMEOUT_US ; 
 struct msm_dsi_pll* hw_clk_to_pll (struct clk_hw*) ; 
 int pll_28nm_poll_for_ready (struct dsi_pll_28nm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dsi_pll_28nm* to_pll_28nm (struct msm_dsi_pll*) ; 

__attribute__((used)) static int dsi_pll_28nm_clk_is_enabled(struct clk_hw *hw)
{
	struct msm_dsi_pll *pll = hw_clk_to_pll(hw);
	struct dsi_pll_28nm *pll_28nm = to_pll_28nm(pll);

	return pll_28nm_poll_for_ready(pll_28nm, POLL_MAX_READS,
					POLL_TIMEOUT_US);
}