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
struct mod_freesync_params {int state; int /*<<< orphan*/  update_duration_in_ns; int /*<<< orphan*/  enable; int /*<<< orphan*/  windowed_fullscreen; } ;
struct mod_freesync {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  update_duration_in_ns; } ;
struct freesync_state {TYPE_3__ time; int /*<<< orphan*/  video; int /*<<< orphan*/  static_screen; int /*<<< orphan*/  windowed_fullscreen; int /*<<< orphan*/  fullscreen; } ;
struct freesync_registry_options {int /*<<< orphan*/  drr_external_supported; int /*<<< orphan*/  drr_internal_supported; } ;
struct dc_stream_state {TYPE_1__* sink; } ;
struct dc_static_screen_events {int overlay_update; int surface_update; int /*<<< orphan*/  member_0; } ;
struct core_freesync {scalar_t__ num_entities; int /*<<< orphan*/  dc; TYPE_2__* map; struct freesync_registry_options opts; } ;
struct TYPE_5__ {struct freesync_state state; } ;
struct TYPE_4__ {int /*<<< orphan*/  sink_signal; } ;

/* Variables and functions */
#define  FREESYNC_STATE_FULLSCREEN 131 
#define  FREESYNC_STATE_NONE 130 
#define  FREESYNC_STATE_STATIC_SCREEN 129 
#define  FREESYNC_STATE_VIDEO 128 
 struct core_freesync* MOD_FREESYNC_TO_CORE (struct mod_freesync*) ; 
 int dc_is_embedded_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dc_stream_set_static_screen_events (int /*<<< orphan*/ ,struct dc_stream_state**,int,struct dc_static_screen_events*) ; 
 unsigned int map_index_from_stream (struct core_freesync*,struct dc_stream_state*) ; 
 int /*<<< orphan*/  set_freesync_on_streams (struct core_freesync*,struct dc_stream_state**,int) ; 
 int /*<<< orphan*/  set_static_ramp_variables (struct core_freesync*,unsigned int,int /*<<< orphan*/ ) ; 

void mod_freesync_update_state(struct mod_freesync *mod_freesync,
		struct dc_stream_state **streams, int num_streams,
		struct mod_freesync_params *freesync_params)
{
	bool freesync_program_required = false;
	unsigned int stream_index;
	struct freesync_state *state;
	struct core_freesync *core_freesync = NULL;
	struct dc_static_screen_events triggers = {0};

	if (mod_freesync == NULL)
		return;

	core_freesync = MOD_FREESYNC_TO_CORE(mod_freesync);

	if (core_freesync->num_entities == 0)
		return;

	for(stream_index = 0; stream_index < num_streams; stream_index++) {

		unsigned int map_index = map_index_from_stream(core_freesync,
				streams[stream_index]);

		bool is_embedded = dc_is_embedded_signal(
				streams[stream_index]->sink->sink_signal);

		struct freesync_registry_options *opts = &core_freesync->opts;

		state = &core_freesync->map[map_index].state;

		switch (freesync_params->state){
		case FREESYNC_STATE_FULLSCREEN:
			state->fullscreen = freesync_params->enable;
			freesync_program_required = true;
			state->windowed_fullscreen =
					freesync_params->windowed_fullscreen;
			break;
		case FREESYNC_STATE_STATIC_SCREEN:
			/* Static screen ramp is disabled by default, but can
			 * be enabled through regkey.
			 */
			if ((is_embedded && opts->drr_internal_supported) ||
				(!is_embedded && opts->drr_external_supported))

				if (state->static_screen !=
						freesync_params->enable) {

					/* Change the state flag */
					state->static_screen =
							freesync_params->enable;

					/* Update static screen ramp */
					set_static_ramp_variables(core_freesync,
						map_index,
						freesync_params->enable);
				}
			/* We program the ramp starting next VUpdate */
			break;
		case FREESYNC_STATE_VIDEO:
			/* Change core variables only if there is a change*/
			if(freesync_params->update_duration_in_ns !=
				state->time.update_duration_in_ns) {

				state->video = freesync_params->enable;
				state->time.update_duration_in_ns =
					freesync_params->update_duration_in_ns;

				freesync_program_required = true;
			}
			break;
		case FREESYNC_STATE_NONE:
			/* handle here to avoid warning */
			break;
		}
	}

	/* Update mask */
	triggers.overlay_update = true;
	triggers.surface_update = true;

	dc_stream_set_static_screen_events(core_freesync->dc, streams,
					   num_streams, &triggers);

	if (freesync_program_required)
		/* Program freesync according to current state*/
		set_freesync_on_streams(core_freesync, streams, num_streams);
}