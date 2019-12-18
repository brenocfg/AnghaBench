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
struct sun4i_tcon {TYPE_2__* crtc; TYPE_1__* dev; } ;
struct drm_encoder {int /*<<< orphan*/  possible_crtcs; } ;
struct sun4i_lvds {struct drm_encoder encoder; int /*<<< orphan*/  connector; scalar_t__ panel; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;
struct drm_bridge {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  crtc; } ;
struct TYPE_3__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_LVDS ; 
 int /*<<< orphan*/  DRM_MODE_ENCODER_LVDS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 struct sun4i_lvds* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int drm_bridge_attach (struct drm_encoder*,struct drm_bridge*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_connector_attach_encoder (int /*<<< orphan*/ *,struct drm_encoder*) ; 
 int /*<<< orphan*/  drm_connector_helper_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int drm_connector_init (struct drm_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_crtc_mask (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_encoder_cleanup (struct drm_encoder*) ; 
 int /*<<< orphan*/  drm_encoder_helper_add (struct drm_encoder*,int /*<<< orphan*/ *) ; 
 int drm_encoder_init (struct drm_device*,struct drm_encoder*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int drm_of_find_panel_or_bridge (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__*,struct drm_bridge**) ; 
 int drm_panel_attach (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sun4i_lvds_con_funcs ; 
 int /*<<< orphan*/  sun4i_lvds_con_helper_funcs ; 
 int /*<<< orphan*/  sun4i_lvds_enc_funcs ; 
 int /*<<< orphan*/  sun4i_lvds_enc_helper_funcs ; 

int sun4i_lvds_init(struct drm_device *drm, struct sun4i_tcon *tcon)
{
	struct drm_encoder *encoder;
	struct drm_bridge *bridge;
	struct sun4i_lvds *lvds;
	int ret;

	lvds = devm_kzalloc(drm->dev, sizeof(*lvds), GFP_KERNEL);
	if (!lvds)
		return -ENOMEM;
	encoder = &lvds->encoder;

	ret = drm_of_find_panel_or_bridge(tcon->dev->of_node, 1, 0,
					  &lvds->panel, &bridge);
	if (ret) {
		dev_info(drm->dev, "No panel or bridge found... LVDS output disabled\n");
		return 0;
	}

	drm_encoder_helper_add(&lvds->encoder,
			       &sun4i_lvds_enc_helper_funcs);
	ret = drm_encoder_init(drm,
			       &lvds->encoder,
			       &sun4i_lvds_enc_funcs,
			       DRM_MODE_ENCODER_LVDS,
			       NULL);
	if (ret) {
		dev_err(drm->dev, "Couldn't initialise the lvds encoder\n");
		goto err_out;
	}

	/* The LVDS encoder can only work with the TCON channel 0 */
	lvds->encoder.possible_crtcs = drm_crtc_mask(&tcon->crtc->crtc);

	if (lvds->panel) {
		drm_connector_helper_add(&lvds->connector,
					 &sun4i_lvds_con_helper_funcs);
		ret = drm_connector_init(drm, &lvds->connector,
					 &sun4i_lvds_con_funcs,
					 DRM_MODE_CONNECTOR_LVDS);
		if (ret) {
			dev_err(drm->dev, "Couldn't initialise the lvds connector\n");
			goto err_cleanup_connector;
		}

		drm_connector_attach_encoder(&lvds->connector,
						  &lvds->encoder);

		ret = drm_panel_attach(lvds->panel, &lvds->connector);
		if (ret) {
			dev_err(drm->dev, "Couldn't attach our panel\n");
			goto err_cleanup_connector;
		}
	}

	if (bridge) {
		ret = drm_bridge_attach(encoder, bridge, NULL);
		if (ret) {
			dev_err(drm->dev, "Couldn't attach our bridge\n");
			goto err_cleanup_connector;
		}
	}

	return 0;

err_cleanup_connector:
	drm_encoder_cleanup(&lvds->encoder);
err_out:
	return ret;
}