#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_7__* stream_enc; } ;
struct pipe_ctx {TYPE_5__ stream_res; struct dc_stream_state* stream; } ;
struct dc_stream_state {int /*<<< orphan*/  signal; TYPE_1__* ctx; struct dc_link* link; } ;
struct dc_link {TYPE_6__* link_enc; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* disable_audio_stream ) (struct pipe_ctx*) ;} ;
struct dc {TYPE_3__ hwss; } ;
struct TYPE_16__ {int /*<<< orphan*/  id; TYPE_2__* funcs; } ;
struct TYPE_15__ {TYPE_4__* funcs; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* connect_dig_be_to_fe ) (TYPE_6__*,int /*<<< orphan*/ ,int) ;} ;
struct TYPE_11__ {int /*<<< orphan*/  (* stop_dp_info_packets ) (TYPE_7__*) ;int /*<<< orphan*/  (* hdmi_reset_stream_attribute ) (TYPE_7__*) ;int /*<<< orphan*/  (* stop_hdmi_info_packets ) (TYPE_7__*) ;} ;
struct TYPE_10__ {struct dc* dc; } ;

/* Variables and functions */
 scalar_t__ dc_is_dp_signal (int /*<<< orphan*/ ) ; 
 scalar_t__ dc_is_hdmi_tmds_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_7__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_7__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_7__*) ; 
 int /*<<< orphan*/  stub4 (struct pipe_ctx*) ; 
 int /*<<< orphan*/  stub5 (TYPE_6__*,int /*<<< orphan*/ ,int) ; 

void dce110_disable_stream(struct pipe_ctx *pipe_ctx)
{
	struct dc_stream_state *stream = pipe_ctx->stream;
	struct dc_link *link = stream->link;
	struct dc *dc = pipe_ctx->stream->ctx->dc;

	if (dc_is_hdmi_tmds_signal(pipe_ctx->stream->signal)) {
		pipe_ctx->stream_res.stream_enc->funcs->stop_hdmi_info_packets(
			pipe_ctx->stream_res.stream_enc);
		pipe_ctx->stream_res.stream_enc->funcs->hdmi_reset_stream_attribute(
			pipe_ctx->stream_res.stream_enc);
	}

	if (dc_is_dp_signal(pipe_ctx->stream->signal))
		pipe_ctx->stream_res.stream_enc->funcs->stop_dp_info_packets(
			pipe_ctx->stream_res.stream_enc);

	dc->hwss.disable_audio_stream(pipe_ctx);

	link->link_enc->funcs->connect_dig_be_to_fe(
			link->link_enc,
			pipe_ctx->stream_res.stream_enc->id,
			false);

}