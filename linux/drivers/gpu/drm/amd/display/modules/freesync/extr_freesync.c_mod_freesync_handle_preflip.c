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
struct TYPE_4__ {scalar_t__ btr_enabled; } ;
struct mod_vrr_params {scalar_t__ state; TYPE_2__ btr; scalar_t__ supported; } ;
struct mod_freesync {int dummy; } ;
struct dc_stream_state {int dummy; } ;
struct TYPE_3__ {int index; unsigned int prev_update_time_in_us; scalar_t__* time_elapsed_in_us; } ;
struct dc_plane_state {TYPE_1__ time; } ;
struct core_freesync {int dummy; } ;

/* Variables and functions */
 unsigned int DC_PLANE_UPDATE_TIMES_MAX ; 
 struct core_freesync* MOD_FREESYNC_TO_CORE (struct mod_freesync*) ; 
 scalar_t__ VRR_STATE_ACTIVE_VARIABLE ; 
 int /*<<< orphan*/  apply_below_the_range (struct core_freesync*,struct dc_stream_state const*,unsigned int,struct mod_vrr_params*) ; 
 int /*<<< orphan*/  apply_fixed_refresh (struct core_freesync*,struct dc_stream_state const*,unsigned int,struct mod_vrr_params*) ; 

void mod_freesync_handle_preflip(struct mod_freesync *mod_freesync,
		const struct dc_plane_state *plane,
		const struct dc_stream_state *stream,
		unsigned int curr_time_stamp_in_us,
		struct mod_vrr_params *in_out_vrr)
{
	struct core_freesync *core_freesync = NULL;
	unsigned int last_render_time_in_us = 0;
	unsigned int average_render_time_in_us = 0;

	if (mod_freesync == NULL)
		return;

	core_freesync = MOD_FREESYNC_TO_CORE(mod_freesync);

	if (in_out_vrr->supported &&
			in_out_vrr->state == VRR_STATE_ACTIVE_VARIABLE) {
		unsigned int i = 0;
		unsigned int oldest_index = plane->time.index + 1;

		if (oldest_index >= DC_PLANE_UPDATE_TIMES_MAX)
			oldest_index = 0;

		last_render_time_in_us = curr_time_stamp_in_us -
				plane->time.prev_update_time_in_us;

		// Sum off all entries except oldest one
		for (i = 0; i < DC_PLANE_UPDATE_TIMES_MAX; i++) {
			average_render_time_in_us +=
					plane->time.time_elapsed_in_us[i];
		}
		average_render_time_in_us -=
				plane->time.time_elapsed_in_us[oldest_index];

		// Add render time for current flip
		average_render_time_in_us += last_render_time_in_us;
		average_render_time_in_us /= DC_PLANE_UPDATE_TIMES_MAX;

		if (in_out_vrr->btr.btr_enabled) {
			apply_below_the_range(core_freesync,
					stream,
					last_render_time_in_us,
					in_out_vrr);
		} else {
			apply_fixed_refresh(core_freesync,
				stream,
				last_render_time_in_us,
				in_out_vrr);
		}

	}
}