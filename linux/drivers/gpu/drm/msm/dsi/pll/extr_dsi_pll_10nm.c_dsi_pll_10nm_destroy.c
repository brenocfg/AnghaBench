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
struct msm_dsi_pll {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  clk_hw; } ;
struct dsi_pll_10nm {TYPE_1__ base; int /*<<< orphan*/  out_div_clk_hw; int /*<<< orphan*/  bit_clk_hw; int /*<<< orphan*/  byte_clk_hw; int /*<<< orphan*/  by_2_bit_clk_hw; int /*<<< orphan*/  post_out_div_clk_hw; int /*<<< orphan*/  pclk_mux_hw; int /*<<< orphan*/  out_dsiclk_hw; int /*<<< orphan*/  id; TYPE_2__* pdev; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_hw_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_hw_unregister_divider (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_hw_unregister_fixed_factor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_hw_unregister_mux (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_clk_del_provider (int /*<<< orphan*/ ) ; 
 struct dsi_pll_10nm* to_pll_10nm (struct msm_dsi_pll*) ; 

__attribute__((used)) static void dsi_pll_10nm_destroy(struct msm_dsi_pll *pll)
{
	struct dsi_pll_10nm *pll_10nm = to_pll_10nm(pll);
	struct device *dev = &pll_10nm->pdev->dev;

	DBG("DSI PLL%d", pll_10nm->id);
	of_clk_del_provider(dev->of_node);

	clk_hw_unregister_divider(pll_10nm->out_dsiclk_hw);
	clk_hw_unregister_mux(pll_10nm->pclk_mux_hw);
	clk_hw_unregister_fixed_factor(pll_10nm->post_out_div_clk_hw);
	clk_hw_unregister_fixed_factor(pll_10nm->by_2_bit_clk_hw);
	clk_hw_unregister_fixed_factor(pll_10nm->byte_clk_hw);
	clk_hw_unregister_divider(pll_10nm->bit_clk_hw);
	clk_hw_unregister_divider(pll_10nm->out_div_clk_hw);
	clk_hw_unregister(&pll_10nm->base.clk_hw);
}