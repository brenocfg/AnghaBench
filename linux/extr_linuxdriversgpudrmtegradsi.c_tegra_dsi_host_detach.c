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
struct TYPE_4__ {scalar_t__ dev; } ;
struct tegra_output {TYPE_2__ connector; TYPE_1__* panel; } ;
struct tegra_dsi {struct tegra_output output; } ;
struct mipi_dsi_host {int dummy; } ;
struct mipi_dsi_device {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_helper_hpd_irq_event (scalar_t__) ; 
 struct tegra_dsi* host_to_tegra (struct mipi_dsi_host*) ; 

__attribute__((used)) static int tegra_dsi_host_detach(struct mipi_dsi_host *host,
				 struct mipi_dsi_device *device)
{
	struct tegra_dsi *dsi = host_to_tegra(host);
	struct tegra_output *output = &dsi->output;

	if (output->panel && &device->dev == output->panel->dev) {
		output->panel = NULL;

		if (output->connector.dev)
			drm_helper_hpd_irq_event(output->connector.dev);
	}

	return 0;
}