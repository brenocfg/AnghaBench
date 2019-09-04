#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct mod_freesync {int dummy; } ;
struct TYPE_10__ {int ramp_is_active; } ;
struct TYPE_9__ {scalar_t__ frames_to_insert; scalar_t__ frame_counter; unsigned int inserted_frame_duration_in_us; scalar_t__ btr_active; } ;
struct TYPE_8__ {unsigned int vmin; } ;
struct freesync_state {int fullscreen; int video; TYPE_4__ static_ramp; TYPE_3__ btr; TYPE_2__ freesync_range; int /*<<< orphan*/  nominal_refresh_rate_in_micro_hz; } ;
struct dc_stream_state {int dummy; } ;
struct dc_static_screen_events {int overlay_update; int surface_update; int /*<<< orphan*/  member_0; } ;
struct core_freesync {scalar_t__ num_entities; int /*<<< orphan*/  dc; TYPE_6__* map; } ;
struct TYPE_11__ {scalar_t__ enable_for_static; scalar_t__ enable_for_gaming; } ;
struct TYPE_12__ {TYPE_5__ user_enable; TYPE_1__* caps; struct freesync_state state; } ;
struct TYPE_7__ {int supported; scalar_t__ btr_supported; } ;

/* Variables and functions */
 struct core_freesync* MOD_FREESYNC_TO_CORE (struct mod_freesync*) ; 
 int /*<<< orphan*/  adjust_vmin_vmax (struct core_freesync*,struct dc_stream_state**,int,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  calc_v_total_for_static_ramp (struct core_freesync*,struct dc_stream_state*,unsigned int,unsigned int*) ; 
 int /*<<< orphan*/  dc_stream_set_static_screen_events (int /*<<< orphan*/ ,struct dc_stream_state**,int,struct dc_static_screen_events*) ; 
 scalar_t__ div64_u64 (unsigned long long,int /*<<< orphan*/ ) ; 
 unsigned int map_index_from_stream (struct core_freesync*,struct dc_stream_state*) ; 
 int /*<<< orphan*/  set_freesync_on_streams (struct core_freesync*,struct dc_stream_state**,int) ; 
 int /*<<< orphan*/  update_stream_freesync_context (struct core_freesync*,struct dc_stream_state*) ; 

void mod_freesync_handle_v_update(struct mod_freesync *mod_freesync,
		struct dc_stream_state **streams, int num_streams)
{
	unsigned int index, v_total, inserted_frame_v_total = 0;
	unsigned int min_frame_duration_in_ns, vmax, vmin = 0;
	struct freesync_state *state;
	struct core_freesync *core_freesync = NULL;
	struct dc_static_screen_events triggers = {0};

	if (mod_freesync == NULL)
		return;

	core_freesync = MOD_FREESYNC_TO_CORE(mod_freesync);

	if (core_freesync->num_entities == 0)
		return;

	index = map_index_from_stream(core_freesync,
		streams[0]);

	if (core_freesync->map[index].caps->supported == false)
		return;

	state = &core_freesync->map[index].state;

	/* Below the Range Logic */

	/* Only execute if in fullscreen mode */
	if (state->fullscreen == true &&
		core_freesync->map[index].user_enable.enable_for_gaming &&
		core_freesync->map[index].caps->btr_supported &&
		state->btr.btr_active) {

		/* TODO: pass in flag for Pre-DCE12 ASIC
		 * in order for frame variable duration to take affect,
		 * it needs to be done one VSYNC early, which is at
		 * frameCounter == 1.
		 * For DCE12 and newer updates to V_TOTAL_MIN/MAX
		 * will take affect on current frame
		 */
		if (state->btr.frames_to_insert == state->btr.frame_counter) {

			min_frame_duration_in_ns = ((unsigned int) (div64_u64(
					(1000000000ULL * 1000000),
					state->nominal_refresh_rate_in_micro_hz)));

			vmin = state->freesync_range.vmin;

			inserted_frame_v_total = vmin;

			if (min_frame_duration_in_ns / 1000)
				inserted_frame_v_total =
					state->btr.inserted_frame_duration_in_us *
					vmin / (min_frame_duration_in_ns / 1000);

			/* Set length of inserted frames as v_total_max*/
			vmax = inserted_frame_v_total;
			vmin = inserted_frame_v_total;

			/* Program V_TOTAL */
			adjust_vmin_vmax(core_freesync, streams,
						num_streams, index,
						vmin, vmax);
		}

		if (state->btr.frame_counter > 0)
			state->btr.frame_counter--;

		/* Restore FreeSync */
		if (state->btr.frame_counter == 0)
			set_freesync_on_streams(core_freesync, streams, num_streams);
	}

	/* If in fullscreen freesync mode or in video, do not program
	 * static screen ramp values
	 */
	if (state->fullscreen == true || state->video == true) {

		state->static_ramp.ramp_is_active = false;

		return;
	}

	/* Gradual Static Screen Ramping Logic */

	/* Execute if ramp is active and user enabled freesync static screen*/
	if (state->static_ramp.ramp_is_active &&
		core_freesync->map[index].user_enable.enable_for_static) {

		calc_v_total_for_static_ramp(core_freesync, streams[0],
				index, &v_total);

		/* Update the freesync context for the stream */
		update_stream_freesync_context(core_freesync, streams[0]);

		/* Program static screen ramp values */
		adjust_vmin_vmax(core_freesync, streams,
					num_streams, index,
					v_total,
					v_total);

		triggers.overlay_update = true;
		triggers.surface_update = true;

		dc_stream_set_static_screen_events(core_freesync->dc, streams,
						   num_streams, &triggers);
	}
}