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
struct drm_connector {int dummy; } ;
struct drm_encoder {scalar_t__ possible_crtcs; } ;
struct dw_mipi_dsi {struct drm_connector connector; struct drm_encoder encoder; struct device* dev; } ;
struct drm_device {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (struct device*,char*) ; 
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_DSI ; 
 int /*<<< orphan*/  DRM_MODE_ENCODER_DSI ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  drm_connector_attach_encoder (struct drm_connector*,struct drm_encoder*) ; 
 int /*<<< orphan*/  drm_connector_helper_add (struct drm_connector*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_connector_init (struct drm_device*,struct drm_connector*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_encoder_helper_add (struct drm_encoder*,int /*<<< orphan*/ *) ; 
 int drm_encoder_init (struct drm_device*,struct drm_encoder*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ drm_of_find_possible_crtcs (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dw_mipi_dsi_atomic_connector_funcs ; 
 int /*<<< orphan*/  dw_mipi_dsi_connector_helper_funcs ; 
 int /*<<< orphan*/  dw_mipi_dsi_encoder_funcs ; 
 int /*<<< orphan*/  dw_mipi_dsi_encoder_helper_funcs ; 

__attribute__((used)) static int dw_mipi_dsi_register(struct drm_device *drm,
				struct dw_mipi_dsi *dsi)
{
	struct drm_encoder *encoder = &dsi->encoder;
	struct drm_connector *connector = &dsi->connector;
	struct device *dev = dsi->dev;
	int ret;

	encoder->possible_crtcs = drm_of_find_possible_crtcs(drm,
							     dev->of_node);
	/*
	 * If we failed to find the CRTC(s) which this encoder is
	 * supposed to be connected to, it's because the CRTC has
	 * not been registered yet.  Defer probing, and hope that
	 * the required CRTC is added later.
	 */
	if (encoder->possible_crtcs == 0)
		return -EPROBE_DEFER;

	drm_encoder_helper_add(&dsi->encoder,
			       &dw_mipi_dsi_encoder_helper_funcs);
	ret = drm_encoder_init(drm, &dsi->encoder, &dw_mipi_dsi_encoder_funcs,
			       DRM_MODE_ENCODER_DSI, NULL);
	if (ret) {
		DRM_DEV_ERROR(dev, "Failed to initialize encoder with drm\n");
		return ret;
	}

	drm_connector_helper_add(connector,
				 &dw_mipi_dsi_connector_helper_funcs);

	drm_connector_init(drm, &dsi->connector,
			   &dw_mipi_dsi_atomic_connector_funcs,
			   DRM_MODE_CONNECTOR_DSI);

	drm_connector_attach_encoder(connector, encoder);

	return 0;
}