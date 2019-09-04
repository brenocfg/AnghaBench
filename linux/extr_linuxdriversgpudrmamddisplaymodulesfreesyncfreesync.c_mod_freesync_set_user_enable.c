#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct persistent_data_flag {int save_per_edid; int save_per_link; } ;
struct mod_freesync_user_enable {scalar_t__ enable_for_video; scalar_t__ enable_for_static; scalar_t__ enable_for_gaming; } ;
struct mod_freesync {int dummy; } ;
struct dc_stream_state {int /*<<< orphan*/  sink; } ;
struct dc {int /*<<< orphan*/  ctx; } ;
struct core_freesync {TYPE_1__* map; struct dc* dc; } ;
struct TYPE_2__ {struct mod_freesync_user_enable user_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREESYNC_REGISTRY_NAME ; 
 struct core_freesync* MOD_FREESYNC_TO_CORE (struct mod_freesync*) ; 
 int /*<<< orphan*/  dm_write_persistent_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*,int,struct persistent_data_flag*) ; 
 unsigned int map_index_from_stream (struct core_freesync*,struct dc_stream_state*) ; 
 int /*<<< orphan*/  set_freesync_on_streams (struct core_freesync*,struct dc_stream_state**,int) ; 

bool mod_freesync_set_user_enable(struct mod_freesync *mod_freesync,
		struct dc_stream_state **streams, int num_streams,
		struct mod_freesync_user_enable *user_enable)
{
	unsigned int stream_index, map_index;
	int persistent_data = 0;
	struct persistent_data_flag flag;
	struct dc  *dc = NULL;
	struct core_freesync *core_freesync = NULL;

	if (mod_freesync == NULL)
		return false;

	core_freesync = MOD_FREESYNC_TO_CORE(mod_freesync);
	dc = core_freesync->dc;

	flag.save_per_edid = true;
	flag.save_per_link = false;

	for(stream_index = 0; stream_index < num_streams;
			stream_index++){

		map_index = map_index_from_stream(core_freesync,
				streams[stream_index]);

		core_freesync->map[map_index].user_enable = *user_enable;

		/* Write persistent data in registry*/
		if (core_freesync->map[map_index].user_enable.
				enable_for_gaming)
			persistent_data = persistent_data | 1;
		if (core_freesync->map[map_index].user_enable.
				enable_for_static)
			persistent_data = persistent_data | 2;
		if (core_freesync->map[map_index].user_enable.
				enable_for_video)
			persistent_data = persistent_data | 4;

		dm_write_persistent_data(dc->ctx,
					streams[stream_index]->sink,
					FREESYNC_REGISTRY_NAME,
					"userenable",
					&persistent_data,
					sizeof(int),
					&flag);
	}

	set_freesync_on_streams(core_freesync, streams, num_streams);

	return true;
}