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
struct drm_connector {int interlace_allowed; int /*<<< orphan*/  polled; } ;
struct hdmi_context {int /*<<< orphan*/  dev; scalar_t__ bridge; int /*<<< orphan*/  drm_dev; struct drm_connector connector; } ;
struct drm_encoder {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_CONNECTOR_POLL_HPD ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_HDMIA ; 
 int drm_bridge_attach (struct drm_encoder*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_connector_attach_encoder (struct drm_connector*,struct drm_encoder*) ; 
 int /*<<< orphan*/  drm_connector_helper_add (struct drm_connector*,int /*<<< orphan*/ *) ; 
 int drm_connector_init (int /*<<< orphan*/ ,struct drm_connector*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct hdmi_context* encoder_to_hdmi (struct drm_encoder*) ; 
 int /*<<< orphan*/  hdmi_connector_funcs ; 
 int /*<<< orphan*/  hdmi_connector_helper_funcs ; 

__attribute__((used)) static int hdmi_create_connector(struct drm_encoder *encoder)
{
	struct hdmi_context *hdata = encoder_to_hdmi(encoder);
	struct drm_connector *connector = &hdata->connector;
	int ret;

	connector->interlace_allowed = true;
	connector->polled = DRM_CONNECTOR_POLL_HPD;

	ret = drm_connector_init(hdata->drm_dev, connector,
			&hdmi_connector_funcs, DRM_MODE_CONNECTOR_HDMIA);
	if (ret) {
		DRM_DEV_ERROR(hdata->dev,
			      "Failed to initialize connector with drm\n");
		return ret;
	}

	drm_connector_helper_add(connector, &hdmi_connector_helper_funcs);
	drm_connector_attach_encoder(connector, encoder);

	if (hdata->bridge) {
		ret = drm_bridge_attach(encoder, hdata->bridge, NULL);
		if (ret)
			DRM_DEV_ERROR(hdata->dev, "Failed to attach bridge\n");
	}

	return ret;
}