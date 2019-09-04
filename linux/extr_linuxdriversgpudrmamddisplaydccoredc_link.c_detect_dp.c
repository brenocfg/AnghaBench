#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct display_sink_capability {scalar_t__ transaction_type; void* signal; } ;
struct TYPE_4__ {int /*<<< orphan*/  SINK_COUNT; } ;
struct TYPE_5__ {TYPE_1__ bits; } ;
struct TYPE_6__ {scalar_t__ dongle_type; TYPE_2__ sink_count; } ;
struct dc_link {scalar_t__ type; int /*<<< orphan*/  ddc; TYPE_3__ dpcd_caps; int /*<<< orphan*/  ctx; } ;
struct audio_support {int dummy; } ;
typedef  enum dc_detect_reason { ____Placeholder_dc_detect_reason } dc_detect_reason ;

/* Variables and functions */
 scalar_t__ DDC_TRANSACTION_TYPE_I2C_OVER_AUX ; 
 int DETECT_REASON_BOOT ; 
 scalar_t__ DISPLAY_DONGLE_DP_HDMI_CONVERTER ; 
 void* SIGNAL_TYPE_DISPLAY_PORT ; 
 void* SIGNAL_TYPE_DISPLAY_PORT_MST ; 
 int /*<<< orphan*/  dal_ddc_service_set_transaction_type (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ dc_connection_active_dongle ; 
 scalar_t__ dc_connection_mst_branch ; 
 scalar_t__ dc_connection_single ; 
 int /*<<< orphan*/  detect_dp_sink_caps (struct dc_link*) ; 
 int /*<<< orphan*/  dm_helpers_dp_mst_start_top_mgr (int /*<<< orphan*/ ,struct dc_link*,int) ; 
 int /*<<< orphan*/  dm_helpers_dp_update_branch_info (int /*<<< orphan*/ ,struct dc_link*) ; 
 void* dp_passive_dongle_detection (int /*<<< orphan*/ ,struct display_sink_capability*,struct audio_support*) ; 
 scalar_t__ get_ddc_transaction_type (void*) ; 
 scalar_t__ is_dp_active_dongle (struct dc_link*) ; 
 scalar_t__ is_mst_supported (struct dc_link*) ; 
 void* link_detect_sink (struct dc_link*,int) ; 
 int /*<<< orphan*/  link_disconnect_sink (struct dc_link*) ; 

__attribute__((used)) static bool detect_dp(
	struct dc_link *link,
	struct display_sink_capability *sink_caps,
	bool *converter_disable_audio,
	struct audio_support *audio_support,
	enum dc_detect_reason reason)
{
	bool boot = false;
	sink_caps->signal = link_detect_sink(link, reason);
	sink_caps->transaction_type =
		get_ddc_transaction_type(sink_caps->signal);

	if (sink_caps->transaction_type == DDC_TRANSACTION_TYPE_I2C_OVER_AUX) {
		sink_caps->signal = SIGNAL_TYPE_DISPLAY_PORT;
		if (!detect_dp_sink_caps(link))
			return false;

		if (is_mst_supported(link)) {
			sink_caps->signal = SIGNAL_TYPE_DISPLAY_PORT_MST;
			link->type = dc_connection_mst_branch;

			dal_ddc_service_set_transaction_type(
							link->ddc,
							sink_caps->transaction_type);

			/*
			 * This call will initiate MST topology discovery. Which
			 * will detect MST ports and add new DRM connector DRM
			 * framework. Then read EDID via remote i2c over aux. In
			 * the end, will notify DRM detect result and save EDID
			 * into DRM framework.
			 *
			 * .detect is called by .fill_modes.
			 * .fill_modes is called by user mode ioctl
			 * DRM_IOCTL_MODE_GETCONNECTOR.
			 *
			 * .get_modes is called by .fill_modes.
			 *
			 * call .get_modes, AMDGPU DM implementation will create
			 * new dc_sink and add to dc_link. For long HPD plug
			 * in/out, MST has its own handle.
			 *
			 * Therefore, just after dc_create, link->sink is not
			 * created for MST until user mode app calls
			 * DRM_IOCTL_MODE_GETCONNECTOR.
			 *
			 * Need check ->sink usages in case ->sink = NULL
			 * TODO: s3 resume check
			 */
			if (reason == DETECT_REASON_BOOT)
				boot = true;

			dm_helpers_dp_update_branch_info(
				link->ctx,
				link);

			if (!dm_helpers_dp_mst_start_top_mgr(
				link->ctx,
				link, boot)) {
				/* MST not supported */
				link->type = dc_connection_single;
				sink_caps->signal = SIGNAL_TYPE_DISPLAY_PORT;
			}
		}

		if (link->type != dc_connection_mst_branch &&
			is_dp_active_dongle(link)) {
			/* DP active dongles */
			link->type = dc_connection_active_dongle;
			if (!link->dpcd_caps.sink_count.bits.SINK_COUNT) {
				/*
				 * active dongle unplug processing for short irq
				 */
				link_disconnect_sink(link);
				return true;
			}

			if (link->dpcd_caps.dongle_type != DISPLAY_DONGLE_DP_HDMI_CONVERTER)
				*converter_disable_audio = true;
		}
	} else {
		/* DP passive dongles */
		sink_caps->signal = dp_passive_dongle_detection(link->ddc,
				sink_caps,
				audio_support);
	}

	return true;
}