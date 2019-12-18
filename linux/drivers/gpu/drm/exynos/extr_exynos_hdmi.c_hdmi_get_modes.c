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
struct hdmi_context {int dvi_mode; int /*<<< orphan*/  notifier; int /*<<< orphan*/  dev; int /*<<< orphan*/  ddc_adpt; } ;
struct edid {int /*<<< orphan*/  height_cm; int /*<<< orphan*/  width_cm; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_DEBUG_KMS (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int /*<<< orphan*/  cec_notifier_set_phys_addr_from_edid (int /*<<< orphan*/ ,struct edid*) ; 
 struct hdmi_context* connector_to_hdmi (struct drm_connector*) ; 
 int drm_add_edid_modes (struct drm_connector*,struct edid*) ; 
 int /*<<< orphan*/  drm_connector_update_edid_property (struct drm_connector*,struct edid*) ; 
 int /*<<< orphan*/  drm_detect_hdmi_monitor (struct edid*) ; 
 struct edid* drm_get_edid (struct drm_connector*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct edid*) ; 

__attribute__((used)) static int hdmi_get_modes(struct drm_connector *connector)
{
	struct hdmi_context *hdata = connector_to_hdmi(connector);
	struct edid *edid;
	int ret;

	if (!hdata->ddc_adpt)
		return -ENODEV;

	edid = drm_get_edid(connector, hdata->ddc_adpt);
	if (!edid)
		return -ENODEV;

	hdata->dvi_mode = !drm_detect_hdmi_monitor(edid);
	DRM_DEV_DEBUG_KMS(hdata->dev, "%s : width[%d] x height[%d]\n",
			  (hdata->dvi_mode ? "dvi monitor" : "hdmi monitor"),
			  edid->width_cm, edid->height_cm);

	drm_connector_update_edid_property(connector, edid);
	cec_notifier_set_phys_addr_from_edid(hdata->notifier, edid);

	ret = drm_add_edid_modes(connector, edid);

	kfree(edid);

	return ret;
}