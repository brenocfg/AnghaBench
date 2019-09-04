#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_7__* stream_enc; } ;
struct pipe_ctx {TYPE_4__ stream_res; struct dc_stream_state* stream; } ;
struct dc_stream_state {int /*<<< orphan*/  signal; TYPE_5__* sink; } ;
struct dc_link {TYPE_2__* dc; TYPE_6__* local_sink; } ;
struct TYPE_14__ {TYPE_3__* funcs; } ;
struct TYPE_13__ {scalar_t__ sink_signal; } ;
struct TYPE_12__ {struct dc_link* link; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* dp_blank ) (TYPE_7__*) ;} ;
struct TYPE_8__ {int /*<<< orphan*/  (* edp_backlight_control ) (struct dc_link*,int) ;} ;
struct TYPE_9__ {TYPE_1__ hwss; } ;

/* Variables and functions */
 scalar_t__ SIGNAL_TYPE_EDP ; 
 scalar_t__ dc_is_dp_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dc_link_set_abm_disable (struct dc_link*) ; 
 int /*<<< orphan*/  stub1 (struct dc_link*,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_7__*) ; 

void dce110_blank_stream(struct pipe_ctx *pipe_ctx)
{
	struct dc_stream_state *stream = pipe_ctx->stream;
	struct dc_link *link = stream->sink->link;

	if (link->local_sink && link->local_sink->sink_signal == SIGNAL_TYPE_EDP) {
		link->dc->hwss.edp_backlight_control(link, false);
		dc_link_set_abm_disable(link);
	}

	if (dc_is_dp_signal(pipe_ctx->stream->signal))
		pipe_ctx->stream_res.stream_enc->funcs->dp_blank(pipe_ctx->stream_res.stream_enc);
}