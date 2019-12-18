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
struct dsi_data {int vdds_dsi_enabled; int /*<<< orphan*/ * vdds_dsi_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  component_del (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsi_component_ops ; 
 int /*<<< orphan*/  dsi_uninit_output (struct dsi_data*) ; 
 int /*<<< orphan*/  of_platform_depopulate (int /*<<< orphan*/ *) ; 
 struct dsi_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dsi_remove(struct platform_device *pdev)
{
	struct dsi_data *dsi = platform_get_drvdata(pdev);

	component_del(&pdev->dev, &dsi_component_ops);

	dsi_uninit_output(dsi);

	of_platform_depopulate(&pdev->dev);

	pm_runtime_disable(&pdev->dev);

	if (dsi->vdds_dsi_reg != NULL && dsi->vdds_dsi_enabled) {
		regulator_disable(dsi->vdds_dsi_reg);
		dsi->vdds_dsi_enabled = false;
	}

	return 0;
}