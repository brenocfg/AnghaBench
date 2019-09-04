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
struct TYPE_5__ {unsigned int vmin; } ;
struct TYPE_4__ {int program_fixed; int /*<<< orphan*/  fixed_active; } ;
struct freesync_state {TYPE_2__ freesync_range; TYPE_1__ fixed_refresh; } ;
struct dc_stream_state {int dummy; } ;
struct core_freesync {TYPE_3__* map; } ;
struct TYPE_6__ {struct freesync_state state; } ;

/* Variables and functions */
 int /*<<< orphan*/  adjust_vmin_vmax (struct core_freesync*,struct dc_stream_state**,unsigned int,int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  set_freesync_on_streams (struct core_freesync*,struct dc_stream_state**,int) ; 

__attribute__((used)) static void apply_fixed_refresh(struct core_freesync *core_freesync,
		struct dc_stream_state *stream, unsigned int map_index)
{
	unsigned int vmin = 0, vmax = 0;
	struct freesync_state *state = &core_freesync->map[map_index].state;

	if (!state->fixed_refresh.program_fixed)
		return;

	state->fixed_refresh.program_fixed = false;

	/* Program Fixed Refresh */

	/* Fixed Refresh set to "not active" so disengage */
	if (!state->fixed_refresh.fixed_active) {
		set_freesync_on_streams(core_freesync, &stream, 1);

	/* Fixed Refresh set to "active" so engage (fix to max) */
	} else {

		vmin = state->freesync_range.vmin;
		vmax = vmin;
		adjust_vmin_vmax(core_freesync, &stream, map_index,
					1, vmin, vmax);
	}
}