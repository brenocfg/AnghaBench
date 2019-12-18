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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct dsi_data {scalar_t__ scp_clk_refcount; int vdds_dsi_enabled; int /*<<< orphan*/ * vdds_dsi_reg; int /*<<< orphan*/  pll; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct dsi_data* dsi_get_dsidrv_data (struct platform_device*) ; 
 int /*<<< orphan*/  dsi_uninit_output (struct platform_device*) ; 
 int /*<<< orphan*/  dss_pll_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_platform_depopulate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ *) ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static void dsi_unbind(struct device *dev, struct device *master, void *data)
{
	struct platform_device *dsidev = to_platform_device(dev);
	struct dsi_data *dsi = dsi_get_dsidrv_data(dsidev);

	of_platform_depopulate(&dsidev->dev);

	WARN_ON(dsi->scp_clk_refcount > 0);

	dss_pll_unregister(&dsi->pll);

	dsi_uninit_output(dsidev);

	pm_runtime_disable(&dsidev->dev);

	if (dsi->vdds_dsi_reg != NULL && dsi->vdds_dsi_enabled) {
		regulator_disable(dsi->vdds_dsi_reg);
		dsi->vdds_dsi_enabled = false;
	}
}