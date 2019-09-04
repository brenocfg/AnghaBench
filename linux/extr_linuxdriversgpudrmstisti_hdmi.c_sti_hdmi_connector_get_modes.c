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
struct sti_hdmi_connector {struct sti_hdmi* hdmi; } ;
struct sti_hdmi {int /*<<< orphan*/  notifier; scalar_t__ hdmi_monitor; int /*<<< orphan*/  ddc_adapt; } ;
struct edid {int /*<<< orphan*/  height_cm; int /*<<< orphan*/  width_cm; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  cec_notifier_set_phys_addr_from_edid (int /*<<< orphan*/ ,struct edid*) ; 
 int drm_add_edid_modes (struct drm_connector*,struct edid*) ; 
 int /*<<< orphan*/  drm_connector_update_edid_property (struct drm_connector*,struct edid*) ; 
 scalar_t__ drm_detect_hdmi_monitor (struct edid*) ; 
 struct edid* drm_get_edid (struct drm_connector*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct edid*) ; 
 struct sti_hdmi_connector* to_sti_hdmi_connector (struct drm_connector*) ; 

__attribute__((used)) static int sti_hdmi_connector_get_modes(struct drm_connector *connector)
{
	struct sti_hdmi_connector *hdmi_connector
		= to_sti_hdmi_connector(connector);
	struct sti_hdmi *hdmi = hdmi_connector->hdmi;
	struct edid *edid;
	int count;

	DRM_DEBUG_DRIVER("\n");

	edid = drm_get_edid(connector, hdmi->ddc_adapt);
	if (!edid)
		goto fail;

	hdmi->hdmi_monitor = drm_detect_hdmi_monitor(edid);
	DRM_DEBUG_KMS("%s : %dx%d cm\n",
		      (hdmi->hdmi_monitor ? "hdmi monitor" : "dvi monitor"),
		      edid->width_cm, edid->height_cm);
	cec_notifier_set_phys_addr_from_edid(hdmi->notifier, edid);

	count = drm_add_edid_modes(connector, edid);
	drm_connector_update_edid_property(connector, edid);

	kfree(edid);
	return count;

fail:
	DRM_ERROR("Can't read HDMI EDID\n");
	return 0;
}