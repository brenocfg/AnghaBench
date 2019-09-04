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
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct timing_generator {TYPE_3__* funcs; } ;
struct resource_context {TYPE_2__* pipe_ctx; } ;
struct dc_stream_state {TYPE_4__* ctx; } ;
struct dc {TYPE_5__* current_state; } ;
struct TYPE_10__ {struct resource_context res_ctx; } ;
struct TYPE_9__ {struct dc* dc; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* get_frame_count ) (struct timing_generator*) ;} ;
struct TYPE_6__ {struct timing_generator* tg; } ;
struct TYPE_7__ {struct dc_stream_state const* stream; TYPE_1__ stream_res; } ;

/* Variables and functions */
 size_t MAX_PIPES ; 
 int /*<<< orphan*/  stub1 (struct timing_generator*) ; 

uint32_t dc_stream_get_vblank_counter(const struct dc_stream_state *stream)
{
	uint8_t i;
	struct dc  *core_dc = stream->ctx->dc;
	struct resource_context *res_ctx =
		&core_dc->current_state->res_ctx;

	for (i = 0; i < MAX_PIPES; i++) {
		struct timing_generator *tg = res_ctx->pipe_ctx[i].stream_res.tg;

		if (res_ctx->pipe_ctx[i].stream != stream)
			continue;

		return tg->funcs->get_frame_count(tg);
	}

	return 0;
}