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
struct timing_generator {TYPE_4__* funcs; } ;
struct resource_context {TYPE_3__* pipe_ctx; } ;
struct dc_stream_state {TYPE_5__* ctx; } ;
struct dc {TYPE_1__* current_state; } ;
struct TYPE_10__ {struct dc* dc; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* get_scanoutpos ) (struct timing_generator*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct TYPE_7__ {struct timing_generator* tg; } ;
struct TYPE_8__ {struct dc_stream_state const* stream; TYPE_2__ stream_res; } ;
struct TYPE_6__ {struct resource_context res_ctx; } ;

/* Variables and functions */
 size_t MAX_PIPES ; 
 int /*<<< orphan*/  stub1 (struct timing_generator*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool dc_stream_get_scanoutpos(const struct dc_stream_state *stream,
				  uint32_t *v_blank_start,
				  uint32_t *v_blank_end,
				  uint32_t *h_position,
				  uint32_t *v_position)
{
	uint8_t i;
	bool ret = false;
	struct dc  *core_dc = stream->ctx->dc;
	struct resource_context *res_ctx =
		&core_dc->current_state->res_ctx;

	for (i = 0; i < MAX_PIPES; i++) {
		struct timing_generator *tg = res_ctx->pipe_ctx[i].stream_res.tg;

		if (res_ctx->pipe_ctx[i].stream != stream)
			continue;

		tg->funcs->get_scanoutpos(tg,
					  v_blank_start,
					  v_blank_end,
					  h_position,
					  v_position);

		ret = true;
		break;
	}

	return ret;
}