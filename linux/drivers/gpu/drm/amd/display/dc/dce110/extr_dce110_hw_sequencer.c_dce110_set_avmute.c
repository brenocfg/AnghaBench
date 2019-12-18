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
struct TYPE_5__ {TYPE_3__* stream_enc; } ;
struct pipe_ctx {TYPE_2__ stream_res; } ;
struct TYPE_6__ {TYPE_1__* funcs; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* set_avmute ) (TYPE_3__*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_3__*,int) ; 

void dce110_set_avmute(struct pipe_ctx *pipe_ctx, bool enable)
{
	if (pipe_ctx != NULL && pipe_ctx->stream_res.stream_enc != NULL)
		pipe_ctx->stream_res.stream_enc->funcs->set_avmute(pipe_ctx->stream_res.stream_enc, enable);
}