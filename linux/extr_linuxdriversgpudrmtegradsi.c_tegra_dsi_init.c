#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int possible_crtcs; } ;
struct TYPE_11__ {int /*<<< orphan*/  dpms; } ;
struct TYPE_9__ {TYPE_2__ encoder; TYPE_4__ connector; int /*<<< orphan*/  dev; } ;
struct tegra_dsi {TYPE_1__ output; int /*<<< orphan*/  dev; int /*<<< orphan*/  master; } ;
struct host1x_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  parent; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_DSI ; 
 int /*<<< orphan*/  DRM_MODE_DPMS_OFF ; 
 int /*<<< orphan*/  DRM_MODE_ENCODER_DSI ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct drm_device* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_connector_attach_encoder (TYPE_4__*,TYPE_2__*) ; 
 int /*<<< orphan*/  drm_connector_helper_add (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_connector_init (struct drm_device*,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_connector_register (TYPE_4__*) ; 
 int /*<<< orphan*/  drm_encoder_helper_add (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_encoder_init (struct drm_device*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct tegra_dsi* host1x_client_to_dsi (struct host1x_client*) ; 
 int /*<<< orphan*/  tegra_dsi_connector_funcs ; 
 int /*<<< orphan*/  tegra_dsi_connector_helper_funcs ; 
 int /*<<< orphan*/  tegra_dsi_encoder_funcs ; 
 int /*<<< orphan*/  tegra_dsi_encoder_helper_funcs ; 
 int tegra_output_init (struct drm_device*,TYPE_1__*) ; 

__attribute__((used)) static int tegra_dsi_init(struct host1x_client *client)
{
	struct drm_device *drm = dev_get_drvdata(client->parent);
	struct tegra_dsi *dsi = host1x_client_to_dsi(client);
	int err;

	/* Gangsters must not register their own outputs. */
	if (!dsi->master) {
		dsi->output.dev = client->dev;

		drm_connector_init(drm, &dsi->output.connector,
				   &tegra_dsi_connector_funcs,
				   DRM_MODE_CONNECTOR_DSI);
		drm_connector_helper_add(&dsi->output.connector,
					 &tegra_dsi_connector_helper_funcs);
		dsi->output.connector.dpms = DRM_MODE_DPMS_OFF;

		drm_encoder_init(drm, &dsi->output.encoder,
				 &tegra_dsi_encoder_funcs,
				 DRM_MODE_ENCODER_DSI, NULL);
		drm_encoder_helper_add(&dsi->output.encoder,
				       &tegra_dsi_encoder_helper_funcs);

		drm_connector_attach_encoder(&dsi->output.connector,
						  &dsi->output.encoder);
		drm_connector_register(&dsi->output.connector);

		err = tegra_output_init(drm, &dsi->output);
		if (err < 0)
			dev_err(dsi->dev, "failed to initialize output: %d\n",
				err);

		dsi->output.encoder.possible_crtcs = 0x3;
	}

	return 0;
}