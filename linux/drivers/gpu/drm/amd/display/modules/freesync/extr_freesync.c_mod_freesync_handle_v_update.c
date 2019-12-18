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
struct TYPE_6__ {int ramping_active; } ;
struct TYPE_5__ {void* v_total_max; void* v_total_min; } ;
struct TYPE_4__ {scalar_t__ frames_to_insert; scalar_t__ frame_counter; int /*<<< orphan*/  inserted_duration_in_us; scalar_t__ btr_active; } ;
struct mod_vrr_params {int supported; scalar_t__ state; TYPE_3__ fixed; int /*<<< orphan*/  min_refresh_in_uhz; TYPE_2__ adjust; int /*<<< orphan*/  max_refresh_in_uhz; TYPE_1__ btr; } ;
struct mod_freesync {int dummy; } ;
struct dc_stream_state {int dummy; } ;
struct core_freesync {int dummy; } ;

/* Variables and functions */
 struct core_freesync* MOD_FREESYNC_TO_CORE (struct mod_freesync*) ; 
 scalar_t__ VRR_STATE_ACTIVE_FIXED ; 
 scalar_t__ VRR_STATE_ACTIVE_VARIABLE ; 
 void* calc_v_total_from_duration (struct dc_stream_state const*,struct mod_vrr_params*,int /*<<< orphan*/ ) ; 
 void* calc_v_total_from_refresh (struct dc_stream_state const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_v_total_for_static_ramp (struct core_freesync*,struct dc_stream_state const*,struct mod_vrr_params*) ; 

void mod_freesync_handle_v_update(struct mod_freesync *mod_freesync,
		const struct dc_stream_state *stream,
		struct mod_vrr_params *in_out_vrr)
{
	struct core_freesync *core_freesync = NULL;

	if ((mod_freesync == NULL) || (stream == NULL) || (in_out_vrr == NULL))
		return;

	core_freesync = MOD_FREESYNC_TO_CORE(mod_freesync);

	if (in_out_vrr->supported == false)
		return;

	/* Below the Range Logic */

	/* Only execute if in fullscreen mode */
	if (in_out_vrr->state == VRR_STATE_ACTIVE_VARIABLE &&
					in_out_vrr->btr.btr_active) {
		/* TODO: pass in flag for Pre-DCE12 ASIC
		 * in order for frame variable duration to take affect,
		 * it needs to be done one VSYNC early, which is at
		 * frameCounter == 1.
		 * For DCE12 and newer updates to V_TOTAL_MIN/MAX
		 * will take affect on current frame
		 */
		if (in_out_vrr->btr.frames_to_insert ==
				in_out_vrr->btr.frame_counter) {
			in_out_vrr->adjust.v_total_min =
				calc_v_total_from_duration(stream,
				in_out_vrr,
				in_out_vrr->btr.inserted_duration_in_us);
			in_out_vrr->adjust.v_total_max =
				in_out_vrr->adjust.v_total_min;
		}

		if (in_out_vrr->btr.frame_counter > 0)
			in_out_vrr->btr.frame_counter--;

		/* Restore FreeSync */
		if (in_out_vrr->btr.frame_counter == 0) {
			in_out_vrr->adjust.v_total_min =
				calc_v_total_from_refresh(stream,
				in_out_vrr->max_refresh_in_uhz);
			in_out_vrr->adjust.v_total_max =
				calc_v_total_from_refresh(stream,
				in_out_vrr->min_refresh_in_uhz);
		}
	}

	/* If in fullscreen freesync mode or in video, do not program
	 * static screen ramp values
	 */
	if (in_out_vrr->state == VRR_STATE_ACTIVE_VARIABLE)
		in_out_vrr->fixed.ramping_active = false;

	/* Gradual Static Screen Ramping Logic */
	/* Execute if ramp is active and user enabled freesync static screen*/
	if (in_out_vrr->state == VRR_STATE_ACTIVE_FIXED &&
				in_out_vrr->fixed.ramping_active) {
		update_v_total_for_static_ramp(
				core_freesync, stream, in_out_vrr);
	}
}