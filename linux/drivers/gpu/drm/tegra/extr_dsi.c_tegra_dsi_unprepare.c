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
struct tegra_dsi {int /*<<< orphan*/  dev; int /*<<< orphan*/  mipi; struct tegra_dsi* slave; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int tegra_mipi_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra_dsi_unprepare(struct tegra_dsi *dsi)
{
	int err;

	if (dsi->slave)
		tegra_dsi_unprepare(dsi->slave);

	err = tegra_mipi_disable(dsi->mipi);
	if (err < 0)
		dev_err(dsi->dev, "failed to disable MIPI calibration: %d\n",
			err);

	pm_runtime_put(dsi->dev);
}