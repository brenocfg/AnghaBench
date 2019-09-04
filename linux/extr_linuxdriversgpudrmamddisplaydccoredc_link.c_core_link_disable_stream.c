#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pipe_ctx {TYPE_3__* stream; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* disable_stream ) (struct pipe_ctx*,int) ;int /*<<< orphan*/  (* blank_stream ) (struct pipe_ctx*) ;} ;
struct dc {TYPE_4__ hwss; } ;
struct TYPE_7__ {scalar_t__ signal; TYPE_1__* sink; TYPE_2__* ctx; } ;
struct TYPE_6__ {struct dc* dc; } ;
struct TYPE_5__ {int /*<<< orphan*/  link; } ;

/* Variables and functions */
 scalar_t__ SIGNAL_TYPE_DISPLAY_PORT_MST ; 
 int /*<<< orphan*/  deallocate_mst_payload (struct pipe_ctx*) ; 
 int /*<<< orphan*/  disable_link (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct pipe_ctx*) ; 
 int /*<<< orphan*/  stub2 (struct pipe_ctx*,int) ; 

void core_link_disable_stream(struct pipe_ctx *pipe_ctx, int option)
{
	struct dc  *core_dc = pipe_ctx->stream->ctx->dc;

	core_dc->hwss.blank_stream(pipe_ctx);

	if (pipe_ctx->stream->signal == SIGNAL_TYPE_DISPLAY_PORT_MST)
		deallocate_mst_payload(pipe_ctx);

	core_dc->hwss.disable_stream(pipe_ctx, option);

	disable_link(pipe_ctx->stream->sink->link, pipe_ctx->stream->signal);
}