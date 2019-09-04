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
struct dc_stream_state {int dummy; } ;
struct core_freesync {TYPE_3__* map; } ;
struct TYPE_4__ {unsigned int vmin; unsigned int vmax; } ;
struct TYPE_5__ {TYPE_1__ freesync_range; } ;
struct TYPE_6__ {TYPE_2__ state; } ;

/* Variables and functions */
 struct core_freesync* MOD_FREESYNC_TO_CORE (struct mod_freesync*) ; 
 unsigned int map_index_from_stream (struct core_freesync*,struct dc_stream_state*) ; 

bool mod_freesync_get_vmin_vmax(struct mod_freesync *mod_freesync,
		struct dc_stream_state *stream,
		unsigned int *vmin,
		unsigned int *vmax)
{
	unsigned int index = 0;
	struct core_freesync *core_freesync = NULL;

	if (mod_freesync == NULL)
		return false;

	core_freesync = MOD_FREESYNC_TO_CORE(mod_freesync);
	index = map_index_from_stream(core_freesync, stream);

	*vmin =
		core_freesync->map[index].state.freesync_range.vmin;
	*vmax =
		core_freesync->map[index].state.freesync_range.vmax;

	return true;
}