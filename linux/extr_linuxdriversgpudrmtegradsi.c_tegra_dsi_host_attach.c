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
struct TYPE_3__ {scalar_t__ dev; } ;
struct tegra_output {TYPE_1__ connector; int /*<<< orphan*/ * panel; } ;
struct tegra_dsi {struct tegra_output output; int /*<<< orphan*/  master; int /*<<< orphan*/  dev; scalar_t__ slave; int /*<<< orphan*/  lanes; int /*<<< orphan*/  format; int /*<<< orphan*/  flags; } ;
struct mipi_dsi_host {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  of_node; } ;
struct mipi_dsi_device {TYPE_2__ dev; int /*<<< orphan*/  lanes; int /*<<< orphan*/  format; int /*<<< orphan*/  mode_flags; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_name (TYPE_2__*) ; 
 int /*<<< orphan*/  drm_helper_hpd_irq_event (scalar_t__) ; 
 int /*<<< orphan*/  drm_panel_attach (int /*<<< orphan*/ *,TYPE_1__*) ; 
 struct tegra_dsi* host_to_tegra (struct mipi_dsi_host*) ; 
 int /*<<< orphan*/ * of_drm_find_panel (int /*<<< orphan*/ ) ; 
 int tegra_dsi_ganged_setup (struct tegra_dsi*) ; 

__attribute__((used)) static int tegra_dsi_host_attach(struct mipi_dsi_host *host,
				 struct mipi_dsi_device *device)
{
	struct tegra_dsi *dsi = host_to_tegra(host);

	dsi->flags = device->mode_flags;
	dsi->format = device->format;
	dsi->lanes = device->lanes;

	if (dsi->slave) {
		int err;

		dev_dbg(dsi->dev, "attaching dual-channel device %s\n",
			dev_name(&device->dev));

		err = tegra_dsi_ganged_setup(dsi);
		if (err < 0) {
			dev_err(dsi->dev, "failed to set up ganged mode: %d\n",
				err);
			return err;
		}
	}

	/*
	 * Slaves don't have a panel associated with them, so they provide
	 * merely the second channel.
	 */
	if (!dsi->master) {
		struct tegra_output *output = &dsi->output;

		output->panel = of_drm_find_panel(device->dev.of_node);
		if (IS_ERR(output->panel))
			output->panel = NULL;

		if (output->panel && output->connector.dev) {
			drm_panel_attach(output->panel, &output->connector);
			drm_helper_hpd_irq_event(output->connector.dev);
		}
	}

	return 0;
}