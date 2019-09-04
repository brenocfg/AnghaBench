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
struct msm_dsi_phy {TYPE_1__* pdev; int /*<<< orphan*/  ahb_clk; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dsi_phy_disable_resource(struct msm_dsi_phy *phy)
{
	clk_disable_unprepare(phy->ahb_clk);
	pm_runtime_put_autosuspend(&phy->pdev->dev);
}