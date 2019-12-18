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
struct TYPE_9__ {TYPE_5__* tg; } ;
struct pipe_ctx {TYPE_4__ stream_res; TYPE_2__* stream; } ;
struct dc_static_screen_events {scalar_t__ force_trigger; scalar_t__ cursor_update; scalar_t__ surface_update; scalar_t__ overlay_update; } ;
struct dc {scalar_t__ fbc_compressor; } ;
struct TYPE_10__ {TYPE_3__* funcs; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* set_static_screen_control ) (TYPE_5__*,unsigned int) ;} ;
struct TYPE_7__ {TYPE_1__* ctx; } ;
struct TYPE_6__ {struct dc* dc; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_5__*,unsigned int) ; 

__attribute__((used)) static void set_static_screen_control(struct pipe_ctx **pipe_ctx,
		int num_pipes, const struct dc_static_screen_events *events)
{
	unsigned int i;
	unsigned int value = 0;

	if (events->overlay_update)
		value |= 0x100;
	if (events->surface_update)
		value |= 0x80;
	if (events->cursor_update)
		value |= 0x2;
	if (events->force_trigger)
		value |= 0x1;

	if (num_pipes) {
		struct dc *dc = pipe_ctx[0]->stream->ctx->dc;

		if (dc->fbc_compressor)
			value |= 0x84;
	}

	for (i = 0; i < num_pipes; i++)
		pipe_ctx[i]->stream_res.tg->funcs->
			set_static_screen_control(pipe_ctx[i]->stream_res.tg, value);
}