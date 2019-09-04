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
struct TYPE_6__ {int program_btr; unsigned int mid_point_in_us; unsigned int inserted_frame_duration_in_us; unsigned int frames_to_insert; unsigned int frame_counter; int /*<<< orphan*/  btr_active; } ;
struct TYPE_5__ {unsigned int min_render_time_in_us; } ;
struct freesync_state {TYPE_3__ btr; TYPE_2__ time; int /*<<< orphan*/  nominal_refresh_rate_in_micro_hz; } ;
struct dc_stream_state {int dummy; } ;
struct core_freesync {TYPE_1__* map; } ;
struct TYPE_4__ {struct freesync_state state; } ;

/* Variables and functions */
 scalar_t__ div64_u64 (unsigned long long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_freesync_on_streams (struct core_freesync*,struct dc_stream_state**,int) ; 

__attribute__((used)) static void apply_below_the_range(struct core_freesync *core_freesync,
		struct dc_stream_state *stream, unsigned int map_index,
		unsigned int last_render_time_in_us)
{
	unsigned int inserted_frame_duration_in_us = 0;
	unsigned int mid_point_frames_ceil = 0;
	unsigned int mid_point_frames_floor = 0;
	unsigned int frame_time_in_us = 0;
	unsigned int delta_from_mid_point_in_us_1 = 0xFFFFFFFF;
	unsigned int delta_from_mid_point_in_us_2 = 0xFFFFFFFF;
	unsigned int frames_to_insert = 0;
	unsigned int min_frame_duration_in_ns = 0;
	struct freesync_state *state = &core_freesync->map[map_index].state;

	if (!state->btr.program_btr)
		return;

	state->btr.program_btr = false;

	min_frame_duration_in_ns = ((unsigned int) (div64_u64(
		(1000000000ULL * 1000000),
		state->nominal_refresh_rate_in_micro_hz)));

	/* Program BTR */

	/* BTR set to "not active" so disengage */
	if (!state->btr.btr_active)

		/* Restore FreeSync */
		set_freesync_on_streams(core_freesync, &stream, 1);

	/* BTR set to "active" so engage */
	else {

		/* Calculate number of midPoint frames that could fit within
		 * the render time interval- take ceil of this value
		 */
		mid_point_frames_ceil = (last_render_time_in_us +
			state->btr.mid_point_in_us- 1) /
			state->btr.mid_point_in_us;

		if (mid_point_frames_ceil > 0) {

			frame_time_in_us = last_render_time_in_us /
				mid_point_frames_ceil;
			delta_from_mid_point_in_us_1 =
				(state->btr.mid_point_in_us >
				frame_time_in_us) ?
				(state->btr.mid_point_in_us - frame_time_in_us):
				(frame_time_in_us - state->btr.mid_point_in_us);
		}

		/* Calculate number of midPoint frames that could fit within
		 * the render time interval- take floor of this value
		 */
		mid_point_frames_floor = last_render_time_in_us /
			state->btr.mid_point_in_us;

		if (mid_point_frames_floor > 0) {

			frame_time_in_us = last_render_time_in_us /
				mid_point_frames_floor;
			delta_from_mid_point_in_us_2 =
				(state->btr.mid_point_in_us >
				frame_time_in_us) ?
				(state->btr.mid_point_in_us - frame_time_in_us):
				(frame_time_in_us - state->btr.mid_point_in_us);
		}

		/* Choose number of frames to insert based on how close it
		 * can get to the mid point of the variable range.
		 */
		if (delta_from_mid_point_in_us_1 < delta_from_mid_point_in_us_2)
			frames_to_insert = mid_point_frames_ceil;
		else
			frames_to_insert = mid_point_frames_floor;

		/* Either we've calculated the number of frames to insert,
		 * or we need to insert min duration frames
		 */
		if (frames_to_insert > 0)
			inserted_frame_duration_in_us = last_render_time_in_us /
							frames_to_insert;

		if (inserted_frame_duration_in_us <
			state->time.min_render_time_in_us)

			inserted_frame_duration_in_us =
				state->time.min_render_time_in_us;

		/* Cache the calculated variables */
		state->btr.inserted_frame_duration_in_us =
			inserted_frame_duration_in_us;
		state->btr.frames_to_insert = frames_to_insert;
		state->btr.frame_counter = frames_to_insert;

	}
}