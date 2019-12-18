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
typedef  int u16 ;
struct intel_sdvo_connector {int output_flag; } ;
struct intel_sdvo {int attached_output; int has_hdmi_monitor; int has_hdmi_audio; } ;
struct edid {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
struct drm_connector {int /*<<< orphan*/  name; TYPE_1__ base; } ;
typedef  enum drm_connector_status { ____Placeholder_drm_connector_status } drm_connector_status ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,int,...) ; 
 scalar_t__ IS_TMDS (struct intel_sdvo_connector*) ; 
 int /*<<< orphan*/  SDVO_CMD_GET_ATTACHED_DISPLAYS ; 
 int connector_status_connected ; 
 int connector_status_disconnected ; 
 int connector_status_unknown ; 
 struct intel_sdvo* intel_attached_sdvo (struct drm_connector*) ; 
 scalar_t__ intel_sdvo_connector_matches_edid (struct intel_sdvo_connector*,struct edid*) ; 
 struct edid* intel_sdvo_get_analog_edid (struct drm_connector*) ; 
 struct edid* intel_sdvo_get_edid (struct drm_connector*) ; 
 int /*<<< orphan*/  intel_sdvo_get_value (struct intel_sdvo*,int /*<<< orphan*/ ,int*,int) ; 
 int intel_sdvo_tmds_sink_detect (struct drm_connector*) ; 
 int /*<<< orphan*/  kfree (struct edid*) ; 
 struct intel_sdvo_connector* to_intel_sdvo_connector (struct drm_connector*) ; 

__attribute__((used)) static enum drm_connector_status
intel_sdvo_detect(struct drm_connector *connector, bool force)
{
	u16 response;
	struct intel_sdvo *intel_sdvo = intel_attached_sdvo(connector);
	struct intel_sdvo_connector *intel_sdvo_connector = to_intel_sdvo_connector(connector);
	enum drm_connector_status ret;

	DRM_DEBUG_KMS("[CONNECTOR:%d:%s]\n",
		      connector->base.id, connector->name);

	if (!intel_sdvo_get_value(intel_sdvo,
				  SDVO_CMD_GET_ATTACHED_DISPLAYS,
				  &response, 2))
		return connector_status_unknown;

	DRM_DEBUG_KMS("SDVO response %d %d [%x]\n",
		      response & 0xff, response >> 8,
		      intel_sdvo_connector->output_flag);

	if (response == 0)
		return connector_status_disconnected;

	intel_sdvo->attached_output = response;

	intel_sdvo->has_hdmi_monitor = false;
	intel_sdvo->has_hdmi_audio = false;

	if ((intel_sdvo_connector->output_flag & response) == 0)
		ret = connector_status_disconnected;
	else if (IS_TMDS(intel_sdvo_connector))
		ret = intel_sdvo_tmds_sink_detect(connector);
	else {
		struct edid *edid;

		/* if we have an edid check it matches the connection */
		edid = intel_sdvo_get_edid(connector);
		if (edid == NULL)
			edid = intel_sdvo_get_analog_edid(connector);
		if (edid != NULL) {
			if (intel_sdvo_connector_matches_edid(intel_sdvo_connector,
							      edid))
				ret = connector_status_connected;
			else
				ret = connector_status_disconnected;

			kfree(edid);
		} else
			ret = connector_status_connected;
	}

	return ret;
}