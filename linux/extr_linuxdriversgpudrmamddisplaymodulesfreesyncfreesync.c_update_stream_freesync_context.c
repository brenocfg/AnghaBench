#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct freesync_context {int enabled; int active; int /*<<< orphan*/  nominal_refresh_in_micro_hz; int /*<<< orphan*/  min_refresh_in_micro_hz; int /*<<< orphan*/  supported; } ;
struct dc_stream_state {struct freesync_context freesync_ctx; } ;
struct core_freesync {TYPE_5__* map; } ;
struct TYPE_7__ {scalar_t__ ramp_is_active; } ;
struct TYPE_9__ {int /*<<< orphan*/  nominal_refresh_rate_in_micro_hz; TYPE_2__ static_ramp; scalar_t__ video; scalar_t__ fullscreen; } ;
struct TYPE_6__ {scalar_t__ enable_for_static; scalar_t__ enable_for_video; scalar_t__ enable_for_gaming; } ;
struct TYPE_10__ {TYPE_4__ state; TYPE_3__* caps; TYPE_1__ user_enable; } ;
struct TYPE_8__ {int /*<<< orphan*/  min_refresh_in_micro_hz; int /*<<< orphan*/  supported; } ;

/* Variables and functions */
 unsigned int map_index_from_stream (struct core_freesync*,struct dc_stream_state*) ; 

__attribute__((used)) static void update_stream_freesync_context(struct core_freesync *core_freesync,
		struct dc_stream_state *stream)
{
	unsigned int index;
	struct freesync_context *ctx;

	ctx = &stream->freesync_ctx;

	index = map_index_from_stream(core_freesync, stream);

	ctx->supported = core_freesync->map[index].caps->supported;
	ctx->enabled = (core_freesync->map[index].user_enable.enable_for_gaming ||
		core_freesync->map[index].user_enable.enable_for_video ||
		core_freesync->map[index].user_enable.enable_for_static);
	ctx->active = (core_freesync->map[index].state.fullscreen ||
		core_freesync->map[index].state.video ||
		core_freesync->map[index].state.static_ramp.ramp_is_active);
	ctx->min_refresh_in_micro_hz =
			core_freesync->map[index].caps->min_refresh_in_micro_hz;
	ctx->nominal_refresh_in_micro_hz = core_freesync->
		map[index].state.nominal_refresh_rate_in_micro_hz;

}