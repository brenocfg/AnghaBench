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
struct ti_sn_bridge {int /*<<< orphan*/  connector; int /*<<< orphan*/  panel; struct mipi_dsi_device* dsi; int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; int /*<<< orphan*/  host_node; } ;
struct mipi_dsi_host {int dummy; } ;
struct mipi_dsi_device_info {char* type; int /*<<< orphan*/ * node; int /*<<< orphan*/  channel; } ;
struct mipi_dsi_device {int lanes; int /*<<< orphan*/  mode_flags; int /*<<< orphan*/  format; } ;
struct drm_bridge {int /*<<< orphan*/  encoder; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DPPLL_CLK_SRC_DSICLK ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_eDP ; 
 int ENODEV ; 
 scalar_t__ IS_ERR (struct mipi_dsi_device*) ; 
 int /*<<< orphan*/  MIPI_DSI_CLOCK_NON_CONTINUOUS ; 
 int /*<<< orphan*/  MIPI_DSI_FMT_RGB888 ; 
 int /*<<< orphan*/  MIPI_DSI_MODE_VIDEO ; 
 int PTR_ERR (struct mipi_dsi_device*) ; 
 int /*<<< orphan*/  SN_DPPLL_SRC_REG ; 
 struct ti_sn_bridge* bridge_to_ti_sn_bridge (struct drm_bridge*) ; 
 int /*<<< orphan*/  drm_connector_attach_encoder (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_connector_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_connector_helper_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int drm_connector_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_panel_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int mipi_dsi_attach (struct mipi_dsi_device*) ; 
 struct mipi_dsi_device* mipi_dsi_device_register_full (struct mipi_dsi_host*,struct mipi_dsi_device_info const*) ; 
 int /*<<< orphan*/  mipi_dsi_device_unregister (struct mipi_dsi_device*) ; 
 struct mipi_dsi_host* of_find_mipi_dsi_host_by_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ti_sn_bridge_connector_funcs ; 
 int /*<<< orphan*/  ti_sn_bridge_connector_helper_funcs ; 

__attribute__((used)) static int ti_sn_bridge_attach(struct drm_bridge *bridge)
{
	int ret, val;
	struct ti_sn_bridge *pdata = bridge_to_ti_sn_bridge(bridge);
	struct mipi_dsi_host *host;
	struct mipi_dsi_device *dsi;
	const struct mipi_dsi_device_info info = { .type = "ti_sn_bridge",
						   .channel = 0,
						   .node = NULL,
						 };

	ret = drm_connector_init(bridge->dev, &pdata->connector,
				 &ti_sn_bridge_connector_funcs,
				 DRM_MODE_CONNECTOR_eDP);
	if (ret) {
		DRM_ERROR("Failed to initialize connector with drm\n");
		return ret;
	}

	drm_connector_helper_add(&pdata->connector,
				 &ti_sn_bridge_connector_helper_funcs);
	drm_connector_attach_encoder(&pdata->connector, bridge->encoder);

	/*
	 * TODO: ideally finding host resource and dsi dev registration needs
	 * to be done in bridge probe. But some existing DSI host drivers will
	 * wait for any of the drm_bridge/drm_panel to get added to the global
	 * bridge/panel list, before completing their probe. So if we do the
	 * dsi dev registration part in bridge probe, before populating in
	 * the global bridge list, then it will cause deadlock as dsi host probe
	 * will never complete, neither our bridge probe. So keeping it here
	 * will satisfy most of the existing host drivers. Once the host driver
	 * is fixed we can move the below code to bridge probe safely.
	 */
	host = of_find_mipi_dsi_host_by_node(pdata->host_node);
	if (!host) {
		DRM_ERROR("failed to find dsi host\n");
		ret = -ENODEV;
		goto err_dsi_host;
	}

	dsi = mipi_dsi_device_register_full(host, &info);
	if (IS_ERR(dsi)) {
		DRM_ERROR("failed to create dsi device\n");
		ret = PTR_ERR(dsi);
		goto err_dsi_host;
	}

	/* TODO: setting to 4 lanes always for now */
	dsi->lanes = 4;
	dsi->format = MIPI_DSI_FMT_RGB888;
	dsi->mode_flags = MIPI_DSI_MODE_VIDEO;

	/* check if continuous dsi clock is required or not */
	pm_runtime_get_sync(pdata->dev);
	regmap_read(pdata->regmap, SN_DPPLL_SRC_REG, &val);
	pm_runtime_put(pdata->dev);
	if (!(val & DPPLL_CLK_SRC_DSICLK))
		dsi->mode_flags |= MIPI_DSI_CLOCK_NON_CONTINUOUS;

	ret = mipi_dsi_attach(dsi);
	if (ret < 0) {
		DRM_ERROR("failed to attach dsi to host\n");
		goto err_dsi_attach;
	}
	pdata->dsi = dsi;

	/* attach panel to bridge */
	drm_panel_attach(pdata->panel, &pdata->connector);

	return 0;

err_dsi_attach:
	mipi_dsi_device_unregister(dsi);
err_dsi_host:
	drm_connector_cleanup(&pdata->connector);
	return ret;
}