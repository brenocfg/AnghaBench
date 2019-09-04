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
struct dsi_pll_28nm {struct clk** provided_clks; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 size_t DSI_BYTE_PLL_CLK ; 
 size_t DSI_PIXEL_PLL_CLK ; 
 struct dsi_pll_28nm* to_pll_28nm (struct msm_dsi_pll*) ; 

__attribute__((used)) static int dsi_pll_28nm_get_provider(struct msm_dsi_pll *pll,
				struct clk **byte_clk_provider,
				struct clk **pixel_clk_provider)
{
	struct dsi_pll_28nm *pll_28nm = to_pll_28nm(pll);

	if (byte_clk_provider)
		*byte_clk_provider = pll_28nm->provided_clks[DSI_BYTE_PLL_CLK];
	if (pixel_clk_provider)
		*pixel_clk_provider =
				pll_28nm->provided_clks[DSI_PIXEL_PLL_CLK];

	return 0;
}