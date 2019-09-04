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
struct mid_intel_hdmi_priv {int has_hdmi_sink; int has_hdmi_audio; } ;
struct gma_encoder {TYPE_1__* i2c_bus; struct mid_intel_hdmi_priv* dev_priv; } ;
struct edid {int input; } ;
struct drm_connector {int dummy; } ;
typedef  enum drm_connector_status { ____Placeholder_drm_connector_status } drm_connector_status ;
struct TYPE_2__ {int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int DRM_EDID_INPUT_DIGITAL ; 
 int connector_status_connected ; 
 int connector_status_disconnected ; 
 int drm_detect_hdmi_monitor (struct edid*) ; 
 int drm_detect_monitor_audio (struct edid*) ; 
 struct edid* drm_get_edid (struct drm_connector*,int /*<<< orphan*/ *) ; 
 struct gma_encoder* gma_attached_encoder (struct drm_connector*) ; 
 int /*<<< orphan*/  kfree (struct edid*) ; 

__attribute__((used)) static enum drm_connector_status cdv_hdmi_detect(
				struct drm_connector *connector, bool force)
{
	struct gma_encoder *gma_encoder = gma_attached_encoder(connector);
	struct mid_intel_hdmi_priv *hdmi_priv = gma_encoder->dev_priv;
	struct edid *edid = NULL;
	enum drm_connector_status status = connector_status_disconnected;

	edid = drm_get_edid(connector, &gma_encoder->i2c_bus->adapter);

	hdmi_priv->has_hdmi_sink = false;
	hdmi_priv->has_hdmi_audio = false;
	if (edid) {
		if (edid->input & DRM_EDID_INPUT_DIGITAL) {
			status = connector_status_connected;
			hdmi_priv->has_hdmi_sink =
						drm_detect_hdmi_monitor(edid);
			hdmi_priv->has_hdmi_audio =
						drm_detect_monitor_audio(edid);
		}
		kfree(edid);
	}
	return status;
}