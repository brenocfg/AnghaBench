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
struct dc_stream_state {int ignore_msa_timing_param; } ;
struct core_freesync {TYPE_2__* map; } ;
struct TYPE_4__ {TYPE_1__* caps; } ;
struct TYPE_3__ {scalar_t__ supported; } ;

/* Variables and functions */
 unsigned int map_index_from_stream (struct core_freesync*,struct dc_stream_state*) ; 
 int /*<<< orphan*/  update_stream_freesync_context (struct core_freesync*,struct dc_stream_state*) ; 

__attribute__((used)) static void update_stream(struct core_freesync *core_freesync,
		struct dc_stream_state *stream)
{
	unsigned int index = map_index_from_stream(core_freesync, stream);
	if (core_freesync->map[index].caps->supported) {
		stream->ignore_msa_timing_param = 1;
		update_stream_freesync_context(core_freesync, stream);
	}
}