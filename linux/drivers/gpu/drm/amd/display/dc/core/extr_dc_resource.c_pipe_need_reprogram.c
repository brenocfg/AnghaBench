#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ audio; scalar_t__ stream_enc; } ;
struct pipe_ctx {scalar_t__ clock_source; TYPE_3__* stream; TYPE_1__ stream_res; } ;
struct TYPE_11__ {scalar_t__ sink; scalar_t__ signal; int dpms_off; TYPE_2__* link; } ;
struct TYPE_10__ {int link_state_valid; } ;

/* Variables and functions */
 scalar_t__ is_hdr_static_meta_changed (TYPE_3__*,TYPE_3__*) ; 
 scalar_t__ is_timing_changed (TYPE_3__*,TYPE_3__*) ; 
 scalar_t__ is_vsc_info_packet_changed (TYPE_3__*,TYPE_3__*) ; 

bool pipe_need_reprogram(
		struct pipe_ctx *pipe_ctx_old,
		struct pipe_ctx *pipe_ctx)
{
	if (!pipe_ctx_old->stream)
		return false;

	if (pipe_ctx_old->stream->sink != pipe_ctx->stream->sink)
		return true;

	if (pipe_ctx_old->stream->signal != pipe_ctx->stream->signal)
		return true;

	if (pipe_ctx_old->stream_res.audio != pipe_ctx->stream_res.audio)
		return true;

	if (pipe_ctx_old->clock_source != pipe_ctx->clock_source
			&& pipe_ctx_old->stream != pipe_ctx->stream)
		return true;

	if (pipe_ctx_old->stream_res.stream_enc != pipe_ctx->stream_res.stream_enc)
		return true;

	if (is_timing_changed(pipe_ctx_old->stream, pipe_ctx->stream))
		return true;

	if (is_hdr_static_meta_changed(pipe_ctx_old->stream, pipe_ctx->stream))
		return true;

	if (pipe_ctx_old->stream->dpms_off != pipe_ctx->stream->dpms_off)
		return true;

	if (is_vsc_info_packet_changed(pipe_ctx_old->stream, pipe_ctx->stream))
		return true;

	if (false == pipe_ctx_old->stream->link->link_state_valid &&
		false == pipe_ctx_old->stream->dpms_off)
		return true;

	return false;
}