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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_unregister (struct clk*) ; 
 int /*<<< orphan*/  of_clk_del_provider (int /*<<< orphan*/ ) ; 

void msm_dsi_pll_helper_unregister_clks(struct platform_device *pdev,
					struct clk **clks, u32 num_clks)
{
	of_clk_del_provider(pdev->dev.of_node);

	if (!num_clks || !clks)
		return;

	do {
		clk_unregister(clks[--num_clks]);
		clks[num_clks] = NULL;
	} while (num_clks);
}