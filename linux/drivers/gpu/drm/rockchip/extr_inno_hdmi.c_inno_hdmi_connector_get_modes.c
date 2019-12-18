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
struct TYPE_2__ {int /*<<< orphan*/  sink_has_audio; int /*<<< orphan*/  sink_is_hdmi; } ;
struct inno_hdmi {TYPE_1__ hdmi_data; int /*<<< orphan*/  ddc; } ;
struct edid {int dummy; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int drm_add_edid_modes (struct drm_connector*,struct edid*) ; 
 int /*<<< orphan*/  drm_connector_update_edid_property (struct drm_connector*,struct edid*) ; 
 int /*<<< orphan*/  drm_detect_hdmi_monitor (struct edid*) ; 
 int /*<<< orphan*/  drm_detect_monitor_audio (struct edid*) ; 
 struct edid* drm_get_edid (struct drm_connector*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct edid*) ; 
 struct inno_hdmi* to_inno_hdmi (struct drm_connector*) ; 

__attribute__((used)) static int inno_hdmi_connector_get_modes(struct drm_connector *connector)
{
	struct inno_hdmi *hdmi = to_inno_hdmi(connector);
	struct edid *edid;
	int ret = 0;

	if (!hdmi->ddc)
		return 0;

	edid = drm_get_edid(connector, hdmi->ddc);
	if (edid) {
		hdmi->hdmi_data.sink_is_hdmi = drm_detect_hdmi_monitor(edid);
		hdmi->hdmi_data.sink_has_audio = drm_detect_monitor_audio(edid);
		drm_connector_update_edid_property(connector, edid);
		ret = drm_add_edid_modes(connector, edid);
		kfree(edid);
	}

	return ret;
}