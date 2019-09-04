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
struct msm_dsi_pll {int dummy; } ;
struct dsi_pll_10nm {int /*<<< orphan*/  id; struct clk_hw_onecell_data* hw_data; } ;
struct clk_hw_onecell_data {TYPE_1__** hws; } ;
struct clk {int dummy; } ;
struct TYPE_2__ {struct clk* clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ) ; 
 size_t DSI_BYTE_PLL_CLK ; 
 size_t DSI_PIXEL_PLL_CLK ; 
 struct dsi_pll_10nm* to_pll_10nm (struct msm_dsi_pll*) ; 

__attribute__((used)) static int dsi_pll_10nm_get_provider(struct msm_dsi_pll *pll,
				     struct clk **byte_clk_provider,
				     struct clk **pixel_clk_provider)
{
	struct dsi_pll_10nm *pll_10nm = to_pll_10nm(pll);
	struct clk_hw_onecell_data *hw_data = pll_10nm->hw_data;

	DBG("DSI PLL%d", pll_10nm->id);

	if (byte_clk_provider)
		*byte_clk_provider = hw_data->hws[DSI_BYTE_PLL_CLK]->clk;
	if (pixel_clk_provider)
		*pixel_clk_provider = hw_data->hws[DSI_PIXEL_PLL_CLK]->clk;

	return 0;
}