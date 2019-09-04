#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int const id; } ;
struct dc_link {TYPE_4__ link_id; TYPE_2__* dc; TYPE_3__* link_enc; } ;
struct audio_support {int /*<<< orphan*/  hdmi_audio_native; } ;
typedef  enum signal_type { ____Placeholder_signal_type } signal_type ;
typedef  enum dc_detect_reason { ____Placeholder_dc_detect_reason } dc_detect_reason ;
struct TYPE_7__ {int /*<<< orphan*/  id; } ;
struct TYPE_6__ {TYPE_1__* res_pool; } ;
struct TYPE_5__ {struct audio_support audio_support; } ;

/* Variables and functions */
#define  CONNECTOR_ID_DISPLAY_PORT 129 
#define  CONNECTOR_ID_HDMI_TYPE_A 128 
 int const CONNECTOR_ID_PCIE ; 
 int DETECT_REASON_HPDRX ; 
 int SIGNAL_TYPE_DVI_SINGLE_LINK ; 
 int /*<<< orphan*/  dm_helpers_is_dp_sink_present (struct dc_link*) ; 
 int get_basic_signal_type (int /*<<< orphan*/ ,TYPE_4__) ; 

__attribute__((used)) static enum signal_type link_detect_sink(
	struct dc_link *link,
	enum dc_detect_reason reason)
{
	enum signal_type result = get_basic_signal_type(
		link->link_enc->id, link->link_id);

	/* Internal digital encoder will detect only dongles
	 * that require digital signal */

	/* Detection mechanism is different
	 * for different native connectors.
	 * LVDS connector supports only LVDS signal;
	 * PCIE is a bus slot, the actual connector needs to be detected first;
	 * eDP connector supports only eDP signal;
	 * HDMI should check straps for audio */

	/* PCIE detects the actual connector on add-on board */

	if (link->link_id.id == CONNECTOR_ID_PCIE) {
		/* ZAZTODO implement PCIE add-on card detection */
	}

	switch (link->link_id.id) {
	case CONNECTOR_ID_HDMI_TYPE_A: {
		/* check audio support:
		 * if native HDMI is not supported, switch to DVI */
		struct audio_support *aud_support = &link->dc->res_pool->audio_support;

		if (!aud_support->hdmi_audio_native)
			if (link->link_id.id == CONNECTOR_ID_HDMI_TYPE_A)
				result = SIGNAL_TYPE_DVI_SINGLE_LINK;
	}
	break;
	case CONNECTOR_ID_DISPLAY_PORT: {
		/* DP HPD short pulse. Passive DP dongle will not
		 * have short pulse
		 */
		if (reason != DETECT_REASON_HPDRX) {
			/* Check whether DP signal detected: if not -
			 * we assume signal is DVI; it could be corrected
			 * to HDMI after dongle detection
			 */
			if (!dm_helpers_is_dp_sink_present(link))
				result = SIGNAL_TYPE_DVI_SINGLE_LINK;
		}
	}
	break;
	default:
	break;
	}

	return result;
}