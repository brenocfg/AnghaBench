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
struct mod_freesync {int dummy; } ;
struct dc_stream_state {int dummy; } ;
struct core_freesync {int num_entities; TYPE_1__* map; } ;
struct TYPE_2__ {int /*<<< orphan*/ * stream; } ;

/* Variables and functions */
 struct core_freesync* MOD_FREESYNC_TO_CORE (struct mod_freesync*) ; 
 int /*<<< orphan*/  dc_stream_release (int /*<<< orphan*/ *) ; 
 unsigned int map_index_from_stream (struct core_freesync*,struct dc_stream_state*) ; 

bool mod_freesync_remove_stream(struct mod_freesync *mod_freesync,
		struct dc_stream_state *stream)
{
	int i = 0;
	struct core_freesync *core_freesync = NULL;
	unsigned int index = 0;

	if (mod_freesync == NULL)
		return false;

	core_freesync = MOD_FREESYNC_TO_CORE(mod_freesync);
	index = map_index_from_stream(core_freesync, stream);

	dc_stream_release(core_freesync->map[index].stream);
	core_freesync->map[index].stream = NULL;
	/* To remove this entity, shift everything after down */
	for (i = index; i < core_freesync->num_entities - 1; i++)
		core_freesync->map[i] = core_freesync->map[i + 1];
	core_freesync->num_entities--;
	return true;
}