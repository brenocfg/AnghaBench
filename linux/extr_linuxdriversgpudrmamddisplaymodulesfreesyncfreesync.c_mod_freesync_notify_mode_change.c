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
struct mod_freesync {int dummy; } ;
struct freesync_state {unsigned int nominal_refresh_rate_in_micro_hz; } ;
struct TYPE_4__ {unsigned long long pix_clk_khz; int /*<<< orphan*/  v_total; int /*<<< orphan*/  h_total; } ;
struct dc_stream_state {TYPE_1__ timing; } ;
struct dc_static_screen_events {int overlay_update; int surface_update; int /*<<< orphan*/  member_0; } ;
struct core_freesync {int /*<<< orphan*/  dc; TYPE_3__* map; } ;
struct TYPE_6__ {TYPE_2__* caps; struct freesync_state state; } ;
struct TYPE_5__ {int /*<<< orphan*/  min_refresh_in_micro_hz; scalar_t__ supported; } ;

/* Variables and functions */
 struct core_freesync* MOD_FREESYNC_TO_CORE (struct mod_freesync*) ; 
 int /*<<< orphan*/  calc_freesync_range (struct core_freesync*,struct dc_stream_state*,struct freesync_state*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  dc_stream_set_static_screen_events (int /*<<< orphan*/ ,struct dc_stream_state**,int,struct dc_static_screen_events*) ; 
 unsigned long long div_u64 (unsigned long long,int /*<<< orphan*/ ) ; 
 unsigned int map_index_from_stream (struct core_freesync*,struct dc_stream_state*) ; 
 int /*<<< orphan*/  set_freesync_on_streams (struct core_freesync*,struct dc_stream_state**,int) ; 
 int /*<<< orphan*/  update_stream (struct core_freesync*,struct dc_stream_state*) ; 

void mod_freesync_notify_mode_change(struct mod_freesync *mod_freesync,
		struct dc_stream_state **streams, int num_streams)
{
	unsigned int stream_index, map_index;
	struct freesync_state *state;
	struct core_freesync *core_freesync = NULL;
	struct dc_static_screen_events triggers = {0};
	unsigned long long temp = 0;

	if (mod_freesync == NULL)
		return;

	core_freesync = MOD_FREESYNC_TO_CORE(mod_freesync);

	for (stream_index = 0; stream_index < num_streams; stream_index++) {
		map_index = map_index_from_stream(core_freesync,
				streams[stream_index]);

		state = &core_freesync->map[map_index].state;

		/* Update the field rate for new timing */
		temp = streams[stream_index]->timing.pix_clk_khz;
		temp *= 1000ULL * 1000ULL * 1000ULL;
		temp = div_u64(temp,
				streams[stream_index]->timing.h_total);
		temp = div_u64(temp,
				streams[stream_index]->timing.v_total);
		state->nominal_refresh_rate_in_micro_hz =
				(unsigned int) temp;

		if (core_freesync->map[map_index].caps->supported) {

			/* Update the stream */
			update_stream(core_freesync, streams[stream_index]);

			/* Calculate vmin/vmax and refresh rate for
			 * current mode
			 */
			calc_freesync_range(core_freesync, *streams, state,
				core_freesync->map[map_index].caps->
				min_refresh_in_micro_hz,
				state->nominal_refresh_rate_in_micro_hz);

			/* Update mask */
			triggers.overlay_update = true;
			triggers.surface_update = true;

			dc_stream_set_static_screen_events(core_freesync->dc,
							   streams, num_streams,
							   &triggers);
		}
	}

	/* Program freesync according to current state*/
	set_freesync_on_streams(core_freesync, streams, num_streams);
}