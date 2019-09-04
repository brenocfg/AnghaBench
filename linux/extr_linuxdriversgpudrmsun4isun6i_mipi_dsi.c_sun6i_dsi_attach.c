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
struct sun6i_dsi {int /*<<< orphan*/  panel; struct mipi_dsi_device* device; } ;
struct mipi_dsi_host {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;
struct mipi_dsi_device {int /*<<< orphan*/  name; TYPE_1__ dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct sun6i_dsi* host_to_sun6i_dsi (struct mipi_dsi_host*) ; 
 int /*<<< orphan*/  of_drm_find_panel (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sun6i_dsi_attach(struct mipi_dsi_host *host,
			    struct mipi_dsi_device *device)
{
	struct sun6i_dsi *dsi = host_to_sun6i_dsi(host);

	dsi->device = device;
	dsi->panel = of_drm_find_panel(device->dev.of_node);
	if (IS_ERR(dsi->panel))
		return PTR_ERR(dsi->panel);

	dev_info(host->dev, "Attached device %s\n", device->name);

	return 0;
}