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
struct TYPE_8__ {void* v_total_max; void* v_total_min; } ;
struct TYPE_7__ {int target_refresh_in_uhz; int fixed_active; scalar_t__ ramping_active; } ;
struct TYPE_5__ {int btr_enabled; int btr_active; int mid_point_in_us; scalar_t__ frame_counter; scalar_t__ frames_to_insert; scalar_t__ inserted_duration_in_us; } ;
struct mod_vrr_params {scalar_t__ state; int supported; unsigned int min_refresh_in_uhz; int max_duration_in_us; unsigned int max_refresh_in_uhz; int min_duration_in_us; TYPE_4__ adjust; TYPE_3__ fixed; TYPE_1__ btr; int /*<<< orphan*/  send_info_frame; } ;
struct mod_freesync_config {unsigned long long min_refresh_in_uhz; unsigned long long max_refresh_in_uhz; scalar_t__ state; int btr; scalar_t__ ramping; int /*<<< orphan*/  vsif_supported; } ;
struct mod_freesync {int dummy; } ;
struct TYPE_6__ {void* v_total; } ;
struct dc_stream_state {TYPE_2__ timing; } ;
struct core_freesync {int dummy; } ;

/* Variables and functions */
 unsigned int MIN_REFRESH_RANGE_IN_US ; 
 struct core_freesync* MOD_FREESYNC_TO_CORE (struct mod_freesync*) ; 
 scalar_t__ VRR_STATE_ACTIVE_FIXED ; 
 scalar_t__ VRR_STATE_ACTIVE_VARIABLE ; 
 scalar_t__ VRR_STATE_DISABLED ; 
 scalar_t__ VRR_STATE_INACTIVE ; 
 scalar_t__ VRR_STATE_UNSUPPORTED ; 
 void* calc_duration_in_us_from_refresh_in_uhz (unsigned int) ; 
 void* calc_v_total_from_refresh (struct dc_stream_state const*,int) ; 
 unsigned long long mod_freesync_calc_nominal_field_rate (struct dc_stream_state const*) ; 
 int /*<<< orphan*/  vrr_settings_require_update (struct core_freesync*,struct mod_freesync_config*,unsigned int,unsigned int,struct mod_vrr_params*) ; 

void mod_freesync_build_vrr_params(struct mod_freesync *mod_freesync,
		const struct dc_stream_state *stream,
		struct mod_freesync_config *in_config,
		struct mod_vrr_params *in_out_vrr)
{
	struct core_freesync *core_freesync = NULL;
	unsigned long long nominal_field_rate_in_uhz = 0;
	unsigned int refresh_range = 0;
	unsigned long long min_refresh_in_uhz = 0;
	unsigned long long max_refresh_in_uhz = 0;

	if (mod_freesync == NULL)
		return;

	core_freesync = MOD_FREESYNC_TO_CORE(mod_freesync);

	/* Calculate nominal field rate for stream */
	nominal_field_rate_in_uhz =
			mod_freesync_calc_nominal_field_rate(stream);

	min_refresh_in_uhz = in_config->min_refresh_in_uhz;
	max_refresh_in_uhz = in_config->max_refresh_in_uhz;

	// Don't allow min > max
	if (min_refresh_in_uhz > max_refresh_in_uhz)
		min_refresh_in_uhz = max_refresh_in_uhz;

	// Full range may be larger than current video timing, so cap at nominal
	if (max_refresh_in_uhz > nominal_field_rate_in_uhz)
		max_refresh_in_uhz = nominal_field_rate_in_uhz;

	// Full range may be larger than current video timing, so cap at nominal
	if (min_refresh_in_uhz > nominal_field_rate_in_uhz)
		min_refresh_in_uhz = nominal_field_rate_in_uhz;

	if (!vrr_settings_require_update(core_freesync,
			in_config, (unsigned int)min_refresh_in_uhz, (unsigned int)max_refresh_in_uhz,
			in_out_vrr))
		return;

	in_out_vrr->state = in_config->state;
	in_out_vrr->send_info_frame = in_config->vsif_supported;

	if (in_config->state == VRR_STATE_UNSUPPORTED) {
		in_out_vrr->state = VRR_STATE_UNSUPPORTED;
		in_out_vrr->supported = false;
		in_out_vrr->adjust.v_total_min = stream->timing.v_total;
		in_out_vrr->adjust.v_total_max = stream->timing.v_total;

		return;

	} else {
		in_out_vrr->min_refresh_in_uhz = (unsigned int)min_refresh_in_uhz;
		in_out_vrr->max_duration_in_us =
				calc_duration_in_us_from_refresh_in_uhz(
						(unsigned int)min_refresh_in_uhz);

		in_out_vrr->max_refresh_in_uhz = (unsigned int)max_refresh_in_uhz;
		in_out_vrr->min_duration_in_us =
				calc_duration_in_us_from_refresh_in_uhz(
						(unsigned int)max_refresh_in_uhz);

		refresh_range = in_out_vrr->max_refresh_in_uhz -
				in_out_vrr->min_refresh_in_uhz;

		in_out_vrr->supported = true;
	}

	in_out_vrr->fixed.ramping_active = in_config->ramping;

	in_out_vrr->btr.btr_enabled = in_config->btr;

	if (in_out_vrr->max_refresh_in_uhz <
			2 * in_out_vrr->min_refresh_in_uhz)
		in_out_vrr->btr.btr_enabled = false;

	in_out_vrr->btr.btr_active = false;
	in_out_vrr->btr.inserted_duration_in_us = 0;
	in_out_vrr->btr.frames_to_insert = 0;
	in_out_vrr->btr.frame_counter = 0;
	in_out_vrr->btr.mid_point_in_us =
				(in_out_vrr->min_duration_in_us +
				 in_out_vrr->max_duration_in_us) / 2;

	if (in_out_vrr->state == VRR_STATE_UNSUPPORTED) {
		in_out_vrr->adjust.v_total_min = stream->timing.v_total;
		in_out_vrr->adjust.v_total_max = stream->timing.v_total;
	} else if (in_out_vrr->state == VRR_STATE_DISABLED) {
		in_out_vrr->adjust.v_total_min = stream->timing.v_total;
		in_out_vrr->adjust.v_total_max = stream->timing.v_total;
	} else if (in_out_vrr->state == VRR_STATE_INACTIVE) {
		in_out_vrr->adjust.v_total_min = stream->timing.v_total;
		in_out_vrr->adjust.v_total_max = stream->timing.v_total;
	} else if (in_out_vrr->state == VRR_STATE_ACTIVE_VARIABLE &&
			refresh_range >= MIN_REFRESH_RANGE_IN_US) {
		in_out_vrr->adjust.v_total_min =
			calc_v_total_from_refresh(stream,
				in_out_vrr->max_refresh_in_uhz);
		in_out_vrr->adjust.v_total_max =
			calc_v_total_from_refresh(stream,
				in_out_vrr->min_refresh_in_uhz);
	} else if (in_out_vrr->state == VRR_STATE_ACTIVE_FIXED) {
		in_out_vrr->fixed.target_refresh_in_uhz =
				in_out_vrr->min_refresh_in_uhz;
		if (in_out_vrr->fixed.ramping_active &&
				in_out_vrr->fixed.fixed_active) {
			/* Do not update vtotals if ramping is already active
			 * in order to continue ramp from current refresh.
			 */
			in_out_vrr->fixed.fixed_active = true;
		} else {
			in_out_vrr->fixed.fixed_active = true;
			in_out_vrr->adjust.v_total_min =
				calc_v_total_from_refresh(stream,
					in_out_vrr->fixed.target_refresh_in_uhz);
			in_out_vrr->adjust.v_total_max =
				in_out_vrr->adjust.v_total_min;
		}
	} else {
		in_out_vrr->state = VRR_STATE_INACTIVE;
		in_out_vrr->adjust.v_total_min = stream->timing.v_total;
		in_out_vrr->adjust.v_total_max = stream->timing.v_total;
	}
}