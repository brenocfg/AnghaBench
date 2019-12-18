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
struct sun4i_rgb {struct drm_encoder encoder; scalar_t__ bridge; int /*<<< orphan*/  connector; scalar_t__ panel; struct sun4i_tcon* tcon; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  crtc; } ;
struct TYPE_3__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_Unknown ; 
 int /*<<< orphan*/  DRM_MODE_ENCODER_NONE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 struct sun4i_rgb* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int drm_bridge_attach (struct drm_encoder*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_connector_attach_encoder (int /*<<< orphan*/ *,struct drm_encoder*) ; 
 int /*<<< orphan*/  drm_connector_helper_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int drm_connector_init (struct drm_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_crtc_mask (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_encoder_cleanup (struct drm_encoder*) ; 
 int /*<<< orphan*/  drm_encoder_helper_add (struct drm_encoder*,int /*<<< orphan*/ *) ; 
 int drm_encoder_init (struct drm_device*,struct drm_encoder*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int drm_of_find_panel_or_bridge (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 int drm_panel_attach (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sun4i_rgb_con_funcs ; 
 int /*<<< orphan*/  sun4i_rgb_con_helper_funcs ; 
 int /*<<< orphan*/  sun4i_rgb_enc_funcs ; 
 int /*<<< orphan*/  sun4i_rgb_enc_helper_funcs ; 

int sun4i_rgb_init(struct drm_device *drm, struct sun4i_tcon *tcon)
{
	struct drm_encoder *encoder;
	struct sun4i_rgb *rgb;
	int ret;

	rgb = devm_kzalloc(drm->dev, sizeof(*rgb), GFP_KERNEL);
	if (!rgb)
		return -ENOMEM;
	rgb->tcon = tcon;
	encoder = &rgb->encoder;

	ret = drm_of_find_panel_or_bridge(tcon->dev->of_node, 1, 0,
					  &rgb->panel, &rgb->bridge);
	if (ret) {
		dev_info(drm->dev, "No panel or bridge found... RGB output disabled\n");
		return 0;
	}

	drm_encoder_helper_add(&rgb->encoder,
			       &sun4i_rgb_enc_helper_funcs);
	ret = drm_encoder_init(drm,
			       &rgb->encoder,
			       &sun4i_rgb_enc_funcs,
			       DRM_MODE_ENCODER_NONE,
			       NULL);
	if (ret) {
		dev_err(drm->dev, "Couldn't initialise the rgb encoder\n");
		goto err_out;
	}

	/* The RGB encoder can only work with the TCON channel 0 */
	rgb->encoder.possible_crtcs = drm_crtc_mask(&tcon->crtc->crtc);

	if (rgb->panel) {
		drm_connector_helper_add(&rgb->connector,
					 &sun4i_rgb_con_helper_funcs);
		ret = drm_connector_init(drm, &rgb->connector,
					 &sun4i_rgb_con_funcs,
					 DRM_MODE_CONNECTOR_Unknown);
		if (ret) {
			dev_err(drm->dev, "Couldn't initialise the rgb connector\n");
			goto err_cleanup_connector;
		}

		drm_connector_attach_encoder(&rgb->connector,
						  &rgb->encoder);

		ret = drm_panel_attach(rgb->panel, &rgb->connector);
		if (ret) {
			dev_err(drm->dev, "Couldn't attach our panel\n");
			goto err_cleanup_connector;
		}
	}

	if (rgb->bridge) {
		ret = drm_bridge_attach(encoder, rgb->bridge, NULL);
		if (ret) {
			dev_err(drm->dev, "Couldn't attach our bridge\n");
			goto err_cleanup_connector;
		}
	}

	return 0;

err_cleanup_connector:
	drm_encoder_cleanup(&rgb->encoder);
err_out:
	return ret;
}