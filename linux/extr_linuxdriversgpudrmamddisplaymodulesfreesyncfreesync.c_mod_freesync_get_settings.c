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
struct mod_freesync {int dummy; } ;
struct TYPE_8__ {unsigned int mid_point_in_us; unsigned int frames_to_insert; unsigned int inserted_frame_duration_in_us; } ;
struct TYPE_7__ {unsigned int min_window; unsigned int max_window; } ;
struct freesync_state {unsigned int vmin; unsigned int vmax; TYPE_4__ btr; TYPE_3__ time; } ;
struct dc_stream_state {int dummy; } ;
struct core_freesync {TYPE_2__* map; } ;
struct TYPE_6__ {struct freesync_state state; TYPE_1__* caps; } ;
struct TYPE_5__ {scalar_t__ supported; } ;

/* Variables and functions */
 struct core_freesync* MOD_FREESYNC_TO_CORE (struct mod_freesync*) ; 
 unsigned int map_index_from_stream (struct core_freesync*,struct dc_stream_state*) ; 

void mod_freesync_get_settings(struct mod_freesync *mod_freesync,
		struct dc_stream_state **streams, int num_streams,
		unsigned int *v_total_min, unsigned int *v_total_max,
		unsigned int *event_triggers,
		unsigned int *window_min, unsigned int *window_max,
		unsigned int *lfc_mid_point_in_us,
		unsigned int *inserted_frames,
		unsigned int *inserted_duration_in_us)
{
	unsigned int stream_index, map_index;
	struct core_freesync *core_freesync = NULL;

	if (mod_freesync == NULL)
		return;

	core_freesync = MOD_FREESYNC_TO_CORE(mod_freesync);

	for (stream_index = 0; stream_index < num_streams; stream_index++) {

		map_index = map_index_from_stream(core_freesync,
						streams[stream_index]);

		if (core_freesync->map[map_index].caps->supported) {
			struct freesync_state state =
					core_freesync->map[map_index].state;
			*v_total_min = state.vmin;
			*v_total_max = state.vmax;
			*event_triggers = 0;
			*window_min = state.time.min_window;
			*window_max = state.time.max_window;
			*lfc_mid_point_in_us = state.btr.mid_point_in_us;
			*inserted_frames = state.btr.frames_to_insert;
			*inserted_duration_in_us =
					state.btr.inserted_frame_duration_in_us;
		}

	}
}