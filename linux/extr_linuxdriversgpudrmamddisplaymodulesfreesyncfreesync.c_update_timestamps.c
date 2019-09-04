#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int btr_active; int program_btr; scalar_t__ frame_counter; } ;
struct TYPE_9__ {int fixed_active; scalar_t__ frame_counter; int program_fixed; } ;
struct TYPE_6__ {unsigned int* render_times; size_t render_times_index; unsigned int max_render_time_in_us; } ;
struct freesync_state {TYPE_5__ btr; TYPE_4__ fixed_refresh; TYPE_1__ time; } ;
struct dc_stream_state {int dummy; } ;
struct core_freesync {TYPE_3__* map; } ;
struct TYPE_8__ {TYPE_2__* caps; struct freesync_state state; } ;
struct TYPE_7__ {scalar_t__ btr_supported; } ;

/* Variables and functions */
 unsigned int BTR_EXIT_MARGIN ; 
 scalar_t__ FIXED_REFRESH_ENTER_FRAME_COUNT ; 
 scalar_t__ FIXED_REFRESH_EXIT_FRAME_COUNT ; 
 size_t RENDER_TIMES_MAX_COUNT ; 

__attribute__((used)) static void update_timestamps(struct core_freesync *core_freesync,
		const struct dc_stream_state *stream, unsigned int map_index,
		unsigned int last_render_time_in_us)
{
	struct freesync_state *state = &core_freesync->map[map_index].state;

	state->time.render_times[state->time.render_times_index] =
			last_render_time_in_us;
	state->time.render_times_index++;

	if (state->time.render_times_index >= RENDER_TIMES_MAX_COUNT)
		state->time.render_times_index = 0;

	if (last_render_time_in_us + BTR_EXIT_MARGIN <
		state->time.max_render_time_in_us) {

		/* Exit Below the Range */
		if (state->btr.btr_active) {

			state->btr.program_btr = true;
			state->btr.btr_active = false;
			state->btr.frame_counter = 0;

		/* Exit Fixed Refresh mode */
		} else if (state->fixed_refresh.fixed_active) {

			state->fixed_refresh.frame_counter++;

			if (state->fixed_refresh.frame_counter >
					FIXED_REFRESH_EXIT_FRAME_COUNT) {
				state->fixed_refresh.frame_counter = 0;
				state->fixed_refresh.program_fixed = true;
				state->fixed_refresh.fixed_active = false;
			}
		}

	} else if (last_render_time_in_us > state->time.max_render_time_in_us) {

		/* Enter Below the Range */
		if (!state->btr.btr_active &&
			core_freesync->map[map_index].caps->btr_supported) {

			state->btr.program_btr = true;
			state->btr.btr_active = true;

		/* Enter Fixed Refresh mode */
		} else if (!state->fixed_refresh.fixed_active &&
			!core_freesync->map[map_index].caps->btr_supported) {

			state->fixed_refresh.frame_counter++;

			if (state->fixed_refresh.frame_counter >
					FIXED_REFRESH_ENTER_FRAME_COUNT) {
				state->fixed_refresh.frame_counter = 0;
				state->fixed_refresh.program_fixed = true;
				state->fixed_refresh.fixed_active = true;
			}
		}
	}

	/* When Below the Range is active, must react on every frame */
	if (state->btr.btr_active)
		state->btr.program_btr = true;
}