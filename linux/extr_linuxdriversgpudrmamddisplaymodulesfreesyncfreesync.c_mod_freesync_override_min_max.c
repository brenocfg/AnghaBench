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
struct mod_freesync_caps {int supported; unsigned int min_refresh_in_micro_hz; unsigned int max_refresh_in_micro_hz; } ;
struct mod_freesync {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  vmax; int /*<<< orphan*/  vmin; } ;
struct freesync_state {unsigned int nominal_refresh_rate_in_micro_hz; TYPE_3__ freesync_range; } ;
struct dc_stream_state {TYPE_4__* sink; } ;
struct core_freesync {TYPE_2__* map; } ;
struct TYPE_8__ {int /*<<< orphan*/  sink_signal; } ;
struct TYPE_6__ {TYPE_1__* caps; struct freesync_state state; } ;
struct TYPE_5__ {unsigned int min_refresh_in_micro_hz; } ;

/* Variables and functions */
 struct core_freesync* MOD_FREESYNC_TO_CORE (struct mod_freesync*) ; 
 int /*<<< orphan*/  adjust_vmin_vmax (struct core_freesync*,struct dc_stream_state**,int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  calc_freesync_range (struct core_freesync*,struct dc_stream_state*,struct freesync_state*,unsigned int,unsigned int) ; 
 scalar_t__ dc_is_embedded_signal (int /*<<< orphan*/ ) ; 
 unsigned int map_index_from_stream (struct core_freesync*,struct dc_stream_state*) ; 
 int /*<<< orphan*/  update_stream (struct core_freesync*,struct dc_stream_state*) ; 

bool mod_freesync_override_min_max(struct mod_freesync *mod_freesync,
		struct dc_stream_state *streams,
		unsigned int min_refresh,
		unsigned int max_refresh,
		struct mod_freesync_caps *caps)
{
	unsigned int index = 0;
	struct core_freesync *core_freesync;
	struct freesync_state *state;

	if (mod_freesync == NULL)
		return false;

	core_freesync = MOD_FREESYNC_TO_CORE(mod_freesync);
	index = map_index_from_stream(core_freesync, streams);
	state = &core_freesync->map[index].state;

	if (max_refresh == 0)
		max_refresh = state->nominal_refresh_rate_in_micro_hz;

	if (min_refresh == 0) {
		/* Restore defaults */
		calc_freesync_range(core_freesync, streams, state,
			core_freesync->map[index].caps->
			min_refresh_in_micro_hz,
			state->nominal_refresh_rate_in_micro_hz);
	} else {
		calc_freesync_range(core_freesync, streams,
				state,
				min_refresh,
				max_refresh);

		/* Program vtotal min/max */
		adjust_vmin_vmax(core_freesync, &streams, 1, index,
				state->freesync_range.vmin,
				state->freesync_range.vmax);
	}

	if (min_refresh != 0 &&
			dc_is_embedded_signal(streams->sink->sink_signal) &&
			(max_refresh - min_refresh >= 10000000)) {
		caps->supported = true;
		caps->min_refresh_in_micro_hz = min_refresh;
		caps->max_refresh_in_micro_hz = max_refresh;
	}

	/* Update the stream */
	update_stream(core_freesync, streams);

	return true;
}