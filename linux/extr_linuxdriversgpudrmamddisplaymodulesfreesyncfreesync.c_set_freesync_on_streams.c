#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  update_duration_in_ns; } ;
struct TYPE_10__ {int vmin; int vmax; } ;
struct TYPE_9__ {int fixed_active; } ;
struct freesync_state {int fullscreen; int video; TYPE_6__ time; TYPE_3__ freesync_range; TYPE_2__ fixed_refresh; } ;
struct TYPE_14__ {int v_total; } ;
struct dc_stream_state {TYPE_7__ timing; } ;
struct core_freesync {TYPE_5__* map; } ;
struct TYPE_11__ {int enable_for_gaming; scalar_t__ enable_for_video; } ;
struct TYPE_12__ {TYPE_4__ user_enable; TYPE_1__* caps; struct freesync_state state; } ;
struct TYPE_8__ {scalar_t__ supported; } ;

/* Variables and functions */
 int /*<<< orphan*/  adjust_vmin_vmax (struct core_freesync*,struct dc_stream_state**,int,unsigned int,int,int) ; 
 int /*<<< orphan*/  calc_v_total_from_duration (struct dc_stream_state*,int /*<<< orphan*/ ,int*) ; 
 unsigned int map_index_from_stream (struct core_freesync*,struct dc_stream_state*) ; 
 int /*<<< orphan*/  reset_freesync_state_variables (struct freesync_state*) ; 
 int /*<<< orphan*/  update_stream_freesync_context (struct core_freesync*,struct dc_stream_state*) ; 

__attribute__((used)) static bool set_freesync_on_streams(struct core_freesync *core_freesync,
		struct dc_stream_state **streams, int num_streams)
{
	int v_total_nominal = 0, v_total_min = 0, v_total_max = 0;
	unsigned int stream_idx, map_index = 0;
	struct freesync_state *state;

	if (num_streams == 0 || streams == NULL || num_streams > 1)
		return false;

	for (stream_idx = 0; stream_idx < num_streams; stream_idx++) {

		map_index = map_index_from_stream(core_freesync,
				streams[stream_idx]);

		state = &core_freesync->map[map_index].state;

		if (core_freesync->map[map_index].caps->supported) {

			/* Fullscreen has the topmost priority. If the
			 * fullscreen bit is set, we are in a fullscreen
			 * application where it should not matter if it is
			 * static screen. We should not check the static_screen
			 * or video bit.
			 *
			 * Special cases of fullscreen include btr and fixed
			 * refresh. We program btr on every flip and involves
			 * programming full range right before the last inserted frame.
			 * However, we do not want to program the full freesync range
			 * when fixed refresh is active, because we only program
			 * that logic once and this will override it.
			 */
			if (core_freesync->map[map_index].user_enable.
				enable_for_gaming == true &&
				state->fullscreen == true &&
				state->fixed_refresh.fixed_active == false) {
				/* Enable freesync */

				v_total_min = state->freesync_range.vmin;
				v_total_max = state->freesync_range.vmax;

				/* Update the freesync context for the stream */
				update_stream_freesync_context(core_freesync,
						streams[stream_idx]);

				adjust_vmin_vmax(core_freesync, streams,
						num_streams, map_index,
						v_total_min,
						v_total_max);

				return true;

			} else if (core_freesync->map[map_index].user_enable.
				enable_for_video && state->video == true) {
				/* Enable 48Hz feature */

				calc_v_total_from_duration(streams[stream_idx],
					state->time.update_duration_in_ns,
					&v_total_nominal);

				/* Program only if v_total_nominal is in range*/
				if (v_total_nominal >=
					streams[stream_idx]->timing.v_total) {

					/* Update the freesync context for
					 * the stream
					 */
					update_stream_freesync_context(
						core_freesync,
						streams[stream_idx]);

					adjust_vmin_vmax(
						core_freesync, streams,
						num_streams, map_index,
						v_total_nominal,
						v_total_nominal);
				}
				return true;

			} else {
				/* Disable freesync */
				v_total_nominal = streams[stream_idx]->
					timing.v_total;

				/* Update the freesync context for
				 * the stream
				 */
				update_stream_freesync_context(
					core_freesync,
					streams[stream_idx]);

				adjust_vmin_vmax(core_freesync, streams,
						num_streams, map_index,
						v_total_nominal,
						v_total_nominal);

				/* Reset the cached variables */
				reset_freesync_state_variables(state);

				return true;
			}
		} else {
			/* Disable freesync */
			v_total_nominal = streams[stream_idx]->
				timing.v_total;
			/*
			 * we have to reset drr always even sink does
			 * not support freesync because a former stream has
			 * be programmed
			 */
			adjust_vmin_vmax(core_freesync, streams,
						num_streams, map_index,
						v_total_nominal,
						v_total_nominal);
			/* Reset the cached variables */
			reset_freesync_state_variables(state);
		}

	}

	return false;
}