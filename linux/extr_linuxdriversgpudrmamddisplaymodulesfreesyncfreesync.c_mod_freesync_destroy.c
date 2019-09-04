#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mod_freesync {int dummy; } ;
struct core_freesync {int num_entities; struct core_freesync* map; scalar_t__ stream; } ;

/* Variables and functions */
 struct core_freesync* MOD_FREESYNC_TO_CORE (struct mod_freesync*) ; 
 int /*<<< orphan*/  dc_stream_release (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct core_freesync*) ; 

void mod_freesync_destroy(struct mod_freesync *mod_freesync)
{
	if (mod_freesync != NULL) {
		int i;
		struct core_freesync *core_freesync =
				MOD_FREESYNC_TO_CORE(mod_freesync);

		for (i = 0; i < core_freesync->num_entities; i++)
			if (core_freesync->map[i].stream)
				dc_stream_release(core_freesync->map[i].stream);

		kfree(core_freesync->map);

		kfree(core_freesync);
	}
}