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
struct sun4i_hdmi {int /*<<< orphan*/  cec_adap; scalar_t__ hdmi_monitor; int /*<<< orphan*/  i2c; scalar_t__ ddc_i2c; } ;
struct edid {int dummy; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,char*) ; 
 int /*<<< orphan*/  cec_s_phys_addr_from_edid (int /*<<< orphan*/ ,struct edid*) ; 
 int drm_add_edid_modes (struct drm_connector*,struct edid*) ; 
 struct sun4i_hdmi* drm_connector_to_sun4i_hdmi (struct drm_connector*) ; 
 int /*<<< orphan*/  drm_connector_update_edid_property (struct drm_connector*,struct edid*) ; 
 scalar_t__ drm_detect_hdmi_monitor (struct edid*) ; 
 struct edid* drm_get_edid (struct drm_connector*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct edid*) ; 

__attribute__((used)) static int sun4i_hdmi_get_modes(struct drm_connector *connector)
{
	struct sun4i_hdmi *hdmi = drm_connector_to_sun4i_hdmi(connector);
	struct edid *edid;
	int ret;

	edid = drm_get_edid(connector, hdmi->ddc_i2c ?: hdmi->i2c);
	if (!edid)
		return 0;

	hdmi->hdmi_monitor = drm_detect_hdmi_monitor(edid);
	DRM_DEBUG_DRIVER("Monitor is %s monitor\n",
			 hdmi->hdmi_monitor ? "an HDMI" : "a DVI");

	drm_connector_update_edid_property(connector, edid);
	cec_s_phys_addr_from_edid(hdmi->cec_adap, edid);
	ret = drm_add_edid_modes(connector, edid);
	kfree(edid);

	return ret;
}