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
struct mod_freesync_params {int enable; int /*<<< orphan*/  windowed_fullscreen; int /*<<< orphan*/  update_duration_in_ns; int /*<<< orphan*/  state; } ;
struct mod_freesync {int dummy; } ;
struct dc_stream_state {int dummy; } ;
struct core_freesync {TYPE_3__* map; } ;
struct TYPE_4__ {int /*<<< orphan*/  update_duration_in_ns; } ;
struct TYPE_5__ {int /*<<< orphan*/  windowed_fullscreen; TYPE_1__ time; scalar_t__ video; scalar_t__ static_screen; scalar_t__ fullscreen; } ;
struct TYPE_6__ {TYPE_2__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREESYNC_STATE_FULLSCREEN ; 
 int /*<<< orphan*/  FREESYNC_STATE_NONE ; 
 int /*<<< orphan*/  FREESYNC_STATE_STATIC_SCREEN ; 
 int /*<<< orphan*/  FREESYNC_STATE_VIDEO ; 
 struct core_freesync* MOD_FREESYNC_TO_CORE (struct mod_freesync*) ; 
 unsigned int map_index_from_stream (struct core_freesync*,struct dc_stream_state*) ; 

bool mod_freesync_get_state(struct mod_freesync *mod_freesync,
		struct dc_stream_state *stream,
		struct mod_freesync_params *freesync_params)
{
	unsigned int index = 0;
	struct core_freesync *core_freesync = NULL;

	if (mod_freesync == NULL)
		return false;

	core_freesync = MOD_FREESYNC_TO_CORE(mod_freesync);
	index = map_index_from_stream(core_freesync, stream);

	if (core_freesync->map[index].state.fullscreen) {
		freesync_params->state = FREESYNC_STATE_FULLSCREEN;
		freesync_params->enable = true;
	} else if (core_freesync->map[index].state.static_screen) {
		freesync_params->state = FREESYNC_STATE_STATIC_SCREEN;
		freesync_params->enable = true;
	} else if (core_freesync->map[index].state.video) {
		freesync_params->state = FREESYNC_STATE_VIDEO;
		freesync_params->enable = true;
	} else {
		freesync_params->state = FREESYNC_STATE_NONE;
		freesync_params->enable = false;
	}

	freesync_params->update_duration_in_ns =
		core_freesync->map[index].state.time.update_duration_in_ns;

	freesync_params->windowed_fullscreen =
			core_freesync->map[index].state.windowed_fullscreen;

	return true;
}