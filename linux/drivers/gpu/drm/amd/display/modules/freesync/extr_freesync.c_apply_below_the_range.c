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
struct TYPE_4__ {int btr_active; unsigned int frame_counter; unsigned int inserted_duration_in_us; unsigned int frames_to_insert; unsigned int mid_point_in_us; } ;
struct TYPE_3__ {void* v_total_max; void* v_total_min; } ;
struct mod_vrr_params {unsigned int max_duration_in_us; unsigned int min_duration_in_us; TYPE_2__ btr; int /*<<< orphan*/  min_refresh_in_uhz; TYPE_1__ adjust; int /*<<< orphan*/  max_refresh_in_uhz; } ;
struct dc_stream_state {int dummy; } ;
struct core_freesync {int dummy; } ;

/* Variables and functions */
 unsigned int BTR_DRIFT_MARGIN ; 
 unsigned int BTR_EXIT_MARGIN ; 
 void* calc_v_total_from_refresh (struct dc_stream_state const*,int /*<<< orphan*/ ) ; 
 scalar_t__ div64_u64 (unsigned long long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void apply_below_the_range(struct core_freesync *core_freesync,
		const struct dc_stream_state *stream,
		unsigned int last_render_time_in_us,
		struct mod_vrr_params *in_out_vrr)
{
	unsigned int inserted_frame_duration_in_us = 0;
	unsigned int mid_point_frames_ceil = 0;
	unsigned int mid_point_frames_floor = 0;
	unsigned int frame_time_in_us = 0;
	unsigned int delta_from_mid_point_in_us_1 = 0xFFFFFFFF;
	unsigned int delta_from_mid_point_in_us_2 = 0xFFFFFFFF;
	unsigned int frames_to_insert = 0;
	unsigned int min_frame_duration_in_ns = 0;
	unsigned int max_render_time_in_us = in_out_vrr->max_duration_in_us;
	unsigned int delta_from_mid_point_delta_in_us;

	min_frame_duration_in_ns = ((unsigned int) (div64_u64(
		(1000000000ULL * 1000000),
		in_out_vrr->max_refresh_in_uhz)));

	/* Program BTR */
	if (last_render_time_in_us + BTR_EXIT_MARGIN < max_render_time_in_us) {
		/* Exit Below the Range */
		if (in_out_vrr->btr.btr_active) {
			in_out_vrr->btr.frame_counter = 0;
			in_out_vrr->btr.btr_active = false;
		}
	} else if (last_render_time_in_us > max_render_time_in_us) {
		/* Enter Below the Range */
		in_out_vrr->btr.btr_active = true;
	}

	/* BTR set to "not active" so disengage */
	if (!in_out_vrr->btr.btr_active) {
		in_out_vrr->btr.inserted_duration_in_us = 0;
		in_out_vrr->btr.frames_to_insert = 0;
		in_out_vrr->btr.frame_counter = 0;

		/* Restore FreeSync */
		in_out_vrr->adjust.v_total_min =
			calc_v_total_from_refresh(stream,
				in_out_vrr->max_refresh_in_uhz);
		in_out_vrr->adjust.v_total_max =
			calc_v_total_from_refresh(stream,
				in_out_vrr->min_refresh_in_uhz);
	/* BTR set to "active" so engage */
	} else {

		/* Calculate number of midPoint frames that could fit within
		 * the render time interval- take ceil of this value
		 */
		mid_point_frames_ceil = (last_render_time_in_us +
				in_out_vrr->btr.mid_point_in_us - 1) /
					in_out_vrr->btr.mid_point_in_us;

		if (mid_point_frames_ceil > 0) {
			frame_time_in_us = last_render_time_in_us /
				mid_point_frames_ceil;
			delta_from_mid_point_in_us_1 =
				(in_out_vrr->btr.mid_point_in_us >
				frame_time_in_us) ?
				(in_out_vrr->btr.mid_point_in_us - frame_time_in_us) :
				(frame_time_in_us - in_out_vrr->btr.mid_point_in_us);
		}

		/* Calculate number of midPoint frames that could fit within
		 * the render time interval- take floor of this value
		 */
		mid_point_frames_floor = last_render_time_in_us /
				in_out_vrr->btr.mid_point_in_us;

		if (mid_point_frames_floor > 0) {

			frame_time_in_us = last_render_time_in_us /
				mid_point_frames_floor;
			delta_from_mid_point_in_us_2 =
				(in_out_vrr->btr.mid_point_in_us >
				frame_time_in_us) ?
				(in_out_vrr->btr.mid_point_in_us - frame_time_in_us) :
				(frame_time_in_us - in_out_vrr->btr.mid_point_in_us);
		}

		/* Choose number of frames to insert based on how close it
		 * can get to the mid point of the variable range.
		 */
		if (delta_from_mid_point_in_us_1 < delta_from_mid_point_in_us_2) {
			frames_to_insert = mid_point_frames_ceil;
			delta_from_mid_point_delta_in_us = delta_from_mid_point_in_us_2 -
					delta_from_mid_point_in_us_1;
		} else {
			frames_to_insert = mid_point_frames_floor;
			delta_from_mid_point_delta_in_us = delta_from_mid_point_in_us_1 -
					delta_from_mid_point_in_us_2;
		}

		/* Prefer current frame multiplier when BTR is enabled unless it drifts
		 * too far from the midpoint
		 */
		if (in_out_vrr->btr.frames_to_insert != 0 &&
				delta_from_mid_point_delta_in_us < BTR_DRIFT_MARGIN) {
			if (((last_render_time_in_us / in_out_vrr->btr.frames_to_insert) <
					in_out_vrr->max_duration_in_us) &&
				((last_render_time_in_us / in_out_vrr->btr.frames_to_insert) >
					in_out_vrr->min_duration_in_us))
				frames_to_insert = in_out_vrr->btr.frames_to_insert;
		}

		/* Either we've calculated the number of frames to insert,
		 * or we need to insert min duration frames
		 */
		if (last_render_time_in_us / frames_to_insert <
				in_out_vrr->min_duration_in_us){
			frames_to_insert -= (frames_to_insert > 1) ?
					1 : 0;
		}

		if (frames_to_insert > 0)
			inserted_frame_duration_in_us = last_render_time_in_us /
							frames_to_insert;

		if (inserted_frame_duration_in_us < in_out_vrr->min_duration_in_us)
			inserted_frame_duration_in_us = in_out_vrr->min_duration_in_us;

		/* Cache the calculated variables */
		in_out_vrr->btr.inserted_duration_in_us =
			inserted_frame_duration_in_us;
		in_out_vrr->btr.frames_to_insert = frames_to_insert;
		in_out_vrr->btr.frame_counter = frames_to_insert;
	}
}