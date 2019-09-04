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
struct dc_stream_state {int dummy; } ;
struct core_freesync {int /*<<< orphan*/  dc; TYPE_2__* map; } ;
struct TYPE_3__ {unsigned int vmin; unsigned int vmax; } ;
struct TYPE_4__ {TYPE_1__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  dc_stream_adjust_vmin_vmax (int /*<<< orphan*/ ,struct dc_stream_state**,int,unsigned int,unsigned int) ; 

__attribute__((used)) static void adjust_vmin_vmax(struct core_freesync *core_freesync,
				struct dc_stream_state **streams,
				int num_streams,
				int map_index,
				unsigned int v_total_min,
				unsigned int v_total_max)
{
	if (num_streams == 0 || streams == NULL || num_streams > 1)
		return;

	core_freesync->map[map_index].state.vmin = v_total_min;
	core_freesync->map[map_index].state.vmax = v_total_max;

	dc_stream_adjust_vmin_vmax(core_freesync->dc, streams,
				num_streams, v_total_min,
				v_total_max);
}