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
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct msm_dsi_pll {int dummy; } ;
struct dsi_pll_14nm {int num_hws; int /*<<< orphan*/ * hws; struct platform_device* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_hw_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_clk_del_provider (int /*<<< orphan*/ ) ; 
 struct dsi_pll_14nm* to_pll_14nm (struct msm_dsi_pll*) ; 

__attribute__((used)) static void dsi_pll_14nm_destroy(struct msm_dsi_pll *pll)
{
	struct dsi_pll_14nm *pll_14nm = to_pll_14nm(pll);
	struct platform_device *pdev = pll_14nm->pdev;
	int num_hws = pll_14nm->num_hws;

	of_clk_del_provider(pdev->dev.of_node);

	while (num_hws--)
		clk_hw_unregister(pll_14nm->hws[num_hws]);
}