#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  possible_crtcs; } ;
struct sun6i_dsi {TYPE_1__ encoder; int /*<<< orphan*/  connector; int /*<<< orphan*/  panel; int /*<<< orphan*/  dev; struct sun4i_drv* drv; } ;
struct sun4i_drv {int dummy; } ;
struct drm_device {struct sun4i_drv* dev_private; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_DSI ; 
 int /*<<< orphan*/  DRM_MODE_ENCODER_DSI ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct sun6i_dsi* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  drm_connector_attach_encoder (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  drm_connector_helper_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int drm_connector_init (struct drm_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_encoder_cleanup (TYPE_1__*) ; 
 int /*<<< orphan*/  drm_encoder_helper_add (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int drm_encoder_init (struct drm_device*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_panel_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sun6i_dsi_connector_funcs ; 
 int /*<<< orphan*/  sun6i_dsi_connector_helper_funcs ; 
 int /*<<< orphan*/  sun6i_dsi_enc_funcs ; 
 int /*<<< orphan*/  sun6i_dsi_enc_helper_funcs ; 

__attribute__((used)) static int sun6i_dsi_bind(struct device *dev, struct device *master,
			 void *data)
{
	struct drm_device *drm = data;
	struct sun4i_drv *drv = drm->dev_private;
	struct sun6i_dsi *dsi = dev_get_drvdata(dev);
	int ret;

	if (!dsi->panel)
		return -EPROBE_DEFER;

	dsi->drv = drv;

	drm_encoder_helper_add(&dsi->encoder,
			       &sun6i_dsi_enc_helper_funcs);
	ret = drm_encoder_init(drm,
			       &dsi->encoder,
			       &sun6i_dsi_enc_funcs,
			       DRM_MODE_ENCODER_DSI,
			       NULL);
	if (ret) {
		dev_err(dsi->dev, "Couldn't initialise the DSI encoder\n");
		return ret;
	}
	dsi->encoder.possible_crtcs = BIT(0);

	drm_connector_helper_add(&dsi->connector,
				 &sun6i_dsi_connector_helper_funcs);
	ret = drm_connector_init(drm, &dsi->connector,
				 &sun6i_dsi_connector_funcs,
				 DRM_MODE_CONNECTOR_DSI);
	if (ret) {
		dev_err(dsi->dev,
			"Couldn't initialise the DSI connector\n");
		goto err_cleanup_connector;
	}

	drm_connector_attach_encoder(&dsi->connector, &dsi->encoder);
	drm_panel_attach(dsi->panel, &dsi->connector);

	return 0;

err_cleanup_connector:
	drm_encoder_cleanup(&dsi->encoder);
	return ret;
}