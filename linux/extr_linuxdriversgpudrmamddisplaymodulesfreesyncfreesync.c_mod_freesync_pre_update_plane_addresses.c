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
struct mod_freesync {int dummy; } ;
struct dc_stream_state {int dummy; } ;
struct core_freesync {TYPE_5__* map; } ;
struct TYPE_8__ {unsigned int prev_time_stamp_in_us; } ;
struct TYPE_9__ {TYPE_3__ time; scalar_t__ fullscreen; } ;
struct TYPE_6__ {scalar_t__ enable_for_gaming; } ;
struct TYPE_10__ {TYPE_4__ state; TYPE_2__* caps; TYPE_1__ user_enable; } ;
struct TYPE_7__ {scalar_t__ btr_supported; scalar_t__ supported; } ;

/* Variables and functions */
 struct core_freesync* MOD_FREESYNC_TO_CORE (struct mod_freesync*) ; 
 int /*<<< orphan*/  apply_below_the_range (struct core_freesync*,struct dc_stream_state*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  apply_fixed_refresh (struct core_freesync*,struct dc_stream_state*,unsigned int) ; 
 unsigned int map_index_from_stream (struct core_freesync*,struct dc_stream_state*) ; 
 int /*<<< orphan*/  update_timestamps (struct core_freesync*,struct dc_stream_state*,unsigned int,unsigned int) ; 

void mod_freesync_pre_update_plane_addresses(struct mod_freesync *mod_freesync,
		struct dc_stream_state **streams, int num_streams,
		unsigned int curr_time_stamp_in_us)
{
	unsigned int stream_index, map_index, last_render_time_in_us = 0;
	struct core_freesync *core_freesync = NULL;

	if (mod_freesync == NULL)
		return;

	core_freesync = MOD_FREESYNC_TO_CORE(mod_freesync);

	for (stream_index = 0; stream_index < num_streams; stream_index++) {

		map_index = map_index_from_stream(core_freesync,
						streams[stream_index]);

		if (core_freesync->map[map_index].caps->supported) {

			last_render_time_in_us = curr_time_stamp_in_us -
					core_freesync->map[map_index].state.time.
					prev_time_stamp_in_us;

			/* Add the timestamps to the cache and determine
			 * whether BTR program is required
			 */
			update_timestamps(core_freesync, streams[stream_index],
					map_index, last_render_time_in_us);

			if (core_freesync->map[map_index].state.fullscreen &&
				core_freesync->map[map_index].user_enable.
				enable_for_gaming) {

				if (core_freesync->map[map_index].caps->btr_supported) {

					apply_below_the_range(core_freesync,
						streams[stream_index], map_index,
						last_render_time_in_us);
				} else {
					apply_fixed_refresh(core_freesync,
						streams[stream_index], map_index);
				}
			}

			core_freesync->map[map_index].state.time.
				prev_time_stamp_in_us = curr_time_stamp_in_us;
		}

	}
}