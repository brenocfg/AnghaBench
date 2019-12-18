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
typedef  int uint16_t ;
struct psb_intel_sdvo_connector {int output_flag; } ;
struct TYPE_4__ {int needs_tv_clock; } ;
struct TYPE_3__ {int output_flags; } ;
struct psb_intel_sdvo {int attached_output; int has_hdmi_monitor; int has_hdmi_audio; int is_tv; int is_lvds; int /*<<< orphan*/ * sdvo_lvds_fixed_mode; TYPE_2__ base; TYPE_1__ caps; } ;
struct edid {int input; } ;
struct drm_connector {int dummy; } ;
typedef  enum drm_connector_status { ____Placeholder_drm_connector_status } drm_connector_status ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,int,int) ; 
 int DRM_EDID_INPUT_DIGITAL ; 
 scalar_t__ IS_TMDS (struct psb_intel_sdvo_connector*) ; 
 int /*<<< orphan*/  SDVO_CMD_GET_ATTACHED_DISPLAYS ; 
 int SDVO_LVDS_MASK ; 
 int SDVO_OUTPUT_CVBS0 ; 
 int SDVO_OUTPUT_SVID0 ; 
 int SDVO_TV_MASK ; 
 int connector_status_connected ; 
 int connector_status_disconnected ; 
 int connector_status_unknown ; 
 struct psb_intel_sdvo* intel_attached_sdvo (struct drm_connector*) ; 
 int /*<<< orphan*/  kfree (struct edid*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 struct edid* psb_intel_sdvo_get_analog_edid (struct drm_connector*) ; 
 struct edid* psb_intel_sdvo_get_edid (struct drm_connector*) ; 
 int psb_intel_sdvo_hdmi_sink_detect (struct drm_connector*) ; 
 int /*<<< orphan*/  psb_intel_sdvo_read_response (struct psb_intel_sdvo*,int*,int) ; 
 int /*<<< orphan*/  psb_intel_sdvo_write_cmd (struct psb_intel_sdvo*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct psb_intel_sdvo_connector* to_psb_intel_sdvo_connector (struct drm_connector*) ; 

__attribute__((used)) static enum drm_connector_status
psb_intel_sdvo_detect(struct drm_connector *connector, bool force)
{
	uint16_t response;
	struct psb_intel_sdvo *psb_intel_sdvo = intel_attached_sdvo(connector);
	struct psb_intel_sdvo_connector *psb_intel_sdvo_connector = to_psb_intel_sdvo_connector(connector);
	enum drm_connector_status ret;

	if (!psb_intel_sdvo_write_cmd(psb_intel_sdvo,
				  SDVO_CMD_GET_ATTACHED_DISPLAYS, NULL, 0))
		return connector_status_unknown;

	/* add 30ms delay when the output type might be TV */
	if (psb_intel_sdvo->caps.output_flags &
	    (SDVO_OUTPUT_SVID0 | SDVO_OUTPUT_CVBS0))
		mdelay(30);

	if (!psb_intel_sdvo_read_response(psb_intel_sdvo, &response, 2))
		return connector_status_unknown;

	DRM_DEBUG_KMS("SDVO response %d %d [%x]\n",
		      response & 0xff, response >> 8,
		      psb_intel_sdvo_connector->output_flag);

	if (response == 0)
		return connector_status_disconnected;

	psb_intel_sdvo->attached_output = response;

	psb_intel_sdvo->has_hdmi_monitor = false;
	psb_intel_sdvo->has_hdmi_audio = false;

	if ((psb_intel_sdvo_connector->output_flag & response) == 0)
		ret = connector_status_disconnected;
	else if (IS_TMDS(psb_intel_sdvo_connector))
		ret = psb_intel_sdvo_hdmi_sink_detect(connector);
	else {
		struct edid *edid;

		/* if we have an edid check it matches the connection */
		edid = psb_intel_sdvo_get_edid(connector);
		if (edid == NULL)
			edid = psb_intel_sdvo_get_analog_edid(connector);
		if (edid != NULL) {
			if (edid->input & DRM_EDID_INPUT_DIGITAL)
				ret = connector_status_disconnected;
			else
				ret = connector_status_connected;
			kfree(edid);
		} else
			ret = connector_status_connected;
	}

	/* May update encoder flag for like clock for SDVO TV, etc.*/
	if (ret == connector_status_connected) {
		psb_intel_sdvo->is_tv = false;
		psb_intel_sdvo->is_lvds = false;
		psb_intel_sdvo->base.needs_tv_clock = false;

		if (response & SDVO_TV_MASK) {
			psb_intel_sdvo->is_tv = true;
			psb_intel_sdvo->base.needs_tv_clock = true;
		}
		if (response & SDVO_LVDS_MASK)
			psb_intel_sdvo->is_lvds = psb_intel_sdvo->sdvo_lvds_fixed_mode != NULL;
	}

	return ret;
}