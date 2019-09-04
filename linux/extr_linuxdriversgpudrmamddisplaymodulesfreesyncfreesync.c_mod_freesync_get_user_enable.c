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
struct mod_freesync_user_enable {int dummy; } ;
struct mod_freesync {int dummy; } ;
struct dc_stream_state {int dummy; } ;
struct core_freesync {TYPE_1__* map; } ;
struct TYPE_2__ {struct mod_freesync_user_enable user_enable; } ;

/* Variables and functions */
 struct core_freesync* MOD_FREESYNC_TO_CORE (struct mod_freesync*) ; 
 unsigned int map_index_from_stream (struct core_freesync*,struct dc_stream_state*) ; 

bool mod_freesync_get_user_enable(struct mod_freesync *mod_freesync,
		struct dc_stream_state *stream,
		struct mod_freesync_user_enable *user_enable)
{
	unsigned int index = 0;
	struct core_freesync *core_freesync = NULL;

	if (mod_freesync == NULL)
		return false;

	core_freesync = MOD_FREESYNC_TO_CORE(mod_freesync);
	index = map_index_from_stream(core_freesync, stream);

	*user_enable = core_freesync->map[index].user_enable;

	return true;
}