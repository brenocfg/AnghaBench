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
struct tegra_dsi {struct tegra_dsi* slave; int /*<<< orphan*/  dev; int /*<<< orphan*/  mipi; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int tegra_dsi_pad_calibrate (struct tegra_dsi*) ; 
 int tegra_mipi_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra_dsi_prepare(struct tegra_dsi *dsi)
{
	int err;

	pm_runtime_get_sync(dsi->dev);

	err = tegra_mipi_enable(dsi->mipi);
	if (err < 0)
		dev_err(dsi->dev, "failed to enable MIPI calibration: %d\n",
			err);

	err = tegra_dsi_pad_calibrate(dsi);
	if (err < 0)
		dev_err(dsi->dev, "MIPI calibration failed: %d\n", err);

	if (dsi->slave)
		tegra_dsi_prepare(dsi->slave);
}