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
struct dc_stream_state {int dummy; } ;
struct core_freesync {unsigned int num_entities; TYPE_1__* map; } ;
struct TYPE_2__ {struct dc_stream_state* stream; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 

__attribute__((used)) static unsigned int map_index_from_stream(struct core_freesync *core_freesync,
		struct dc_stream_state *stream)
{
	unsigned int index = 0;

	for (index = 0; index < core_freesync->num_entities; index++) {
		if (core_freesync->map[index].stream == stream) {
			return index;
		}
	}
	/* Could not find stream requested */
	ASSERT(false);
	return index;
}