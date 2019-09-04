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
struct mipi_dsi_host {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  of_node; } ;
struct mipi_dsi_device {scalar_t__ lanes; TYPE_2__ dev; int /*<<< orphan*/  mode_flags; int /*<<< orphan*/  format; int /*<<< orphan*/  channel; } ;
struct dw_mipi_dsi {scalar_t__ lanes; int /*<<< orphan*/  connector; int /*<<< orphan*/  panel; int /*<<< orphan*/  mode_flags; int /*<<< orphan*/  format; int /*<<< orphan*/  channel; int /*<<< orphan*/  dev; TYPE_1__* pdata; } ;
struct TYPE_3__ {scalar_t__ max_data_lanes; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int EINVAL ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int drm_panel_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct dw_mipi_dsi* host_to_dsi (struct mipi_dsi_host*) ; 
 int /*<<< orphan*/  of_drm_find_panel (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dw_mipi_dsi_host_attach(struct mipi_dsi_host *host,
				   struct mipi_dsi_device *device)
{
	struct dw_mipi_dsi *dsi = host_to_dsi(host);

	if (device->lanes > dsi->pdata->max_data_lanes) {
		DRM_DEV_ERROR(dsi->dev,
			      "the number of data lanes(%u) is too many\n",
			      device->lanes);
		return -EINVAL;
	}

	dsi->lanes = device->lanes;
	dsi->channel = device->channel;
	dsi->format = device->format;
	dsi->mode_flags = device->mode_flags;
	dsi->panel = of_drm_find_panel(device->dev.of_node);
	if (!IS_ERR(dsi->panel))
		return drm_panel_attach(dsi->panel, &dsi->connector);

	return -EINVAL;
}