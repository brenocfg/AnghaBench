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
struct mipi_dsi_host {TYPE_1__* dev; } ;
struct mipi_dsi_device {scalar_t__ lanes; int /*<<< orphan*/  mode_flags; int /*<<< orphan*/  format; int /*<<< orphan*/  channel; } ;
struct dw_mipi_dsi_plat_data {scalar_t__ max_data_lanes; int /*<<< orphan*/  priv_data; TYPE_2__* host_ops; } ;
struct dw_mipi_dsi {scalar_t__ lanes; int /*<<< orphan*/  bridge; struct drm_bridge* panel_bridge; int /*<<< orphan*/  mode_flags; int /*<<< orphan*/  format; int /*<<< orphan*/  channel; int /*<<< orphan*/  dev; struct dw_mipi_dsi_plat_data* plat_data; } ;
struct drm_panel {int dummy; } ;
struct drm_bridge {int dummy; } ;
struct TYPE_4__ {int (* attach ) (int /*<<< orphan*/ ,struct mipi_dsi_device*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_DSI ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct drm_bridge*) ; 
 int PTR_ERR (struct drm_bridge*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  drm_bridge_add (int /*<<< orphan*/ *) ; 
 int drm_of_find_panel_or_bridge (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct drm_panel**,struct drm_bridge**) ; 
 struct drm_bridge* drm_panel_bridge_add (struct drm_panel*,int /*<<< orphan*/ ) ; 
 struct dw_mipi_dsi* host_to_dsi (struct mipi_dsi_host*) ; 
 int stub1 (int /*<<< orphan*/ ,struct mipi_dsi_device*) ; 

__attribute__((used)) static int dw_mipi_dsi_host_attach(struct mipi_dsi_host *host,
				   struct mipi_dsi_device *device)
{
	struct dw_mipi_dsi *dsi = host_to_dsi(host);
	const struct dw_mipi_dsi_plat_data *pdata = dsi->plat_data;
	struct drm_bridge *bridge;
	struct drm_panel *panel;
	int ret;

	if (device->lanes > dsi->plat_data->max_data_lanes) {
		dev_err(dsi->dev, "the number of data lanes(%u) is too many\n",
			device->lanes);
		return -EINVAL;
	}

	dsi->lanes = device->lanes;
	dsi->channel = device->channel;
	dsi->format = device->format;
	dsi->mode_flags = device->mode_flags;

	ret = drm_of_find_panel_or_bridge(host->dev->of_node, 1, 0,
					  &panel, &bridge);
	if (ret)
		return ret;

	if (panel) {
		bridge = drm_panel_bridge_add(panel, DRM_MODE_CONNECTOR_DSI);
		if (IS_ERR(bridge))
			return PTR_ERR(bridge);
	}

	dsi->panel_bridge = bridge;

	drm_bridge_add(&dsi->bridge);

	if (pdata->host_ops && pdata->host_ops->attach) {
		ret = pdata->host_ops->attach(pdata->priv_data, device);
		if (ret < 0)
			return ret;
	}

	return 0;
}