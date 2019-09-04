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
struct TYPE_10__ {TYPE_2__* tg; TYPE_1__* stream_enc; } ;
struct pipe_ctx {TYPE_5__* stream; TYPE_3__ stream_res; } ;
struct dc_sink {TYPE_6__* ctx; } ;
struct dc_bios {TYPE_7__* funcs; } ;
struct bp_crtc_source_select {int enable_dp_audio; void* display_output_bit_depth; int /*<<< orphan*/  sink_signal; int /*<<< orphan*/  signal; scalar_t__ controller_id; int /*<<< orphan*/  engine_id; int /*<<< orphan*/  member_0; } ;
typedef  enum dc_status { ____Placeholder_dc_status } dc_status ;
struct TYPE_14__ {scalar_t__ (* crtc_source_select ) (struct dc_bios*,struct bp_crtc_source_select*) ;} ;
struct TYPE_13__ {struct dc_bios* dc_bios; } ;
struct TYPE_11__ {int display_color_depth; } ;
struct TYPE_12__ {TYPE_4__ timing; int /*<<< orphan*/  signal; struct dc_sink* sink; } ;
struct TYPE_9__ {scalar_t__ inst; } ;
struct TYPE_8__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 scalar_t__ BP_RESULT_OK ; 
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
#define  COLOR_DEPTH_101010 131 
#define  COLOR_DEPTH_121212 130 
#define  COLOR_DEPTH_666 129 
#define  COLOR_DEPTH_888 128 
 int DC_ERROR_UNEXPECTED ; 
 int DC_OK ; 
 void* PANEL_10BIT_COLOR ; 
 void* PANEL_12BIT_COLOR ; 
 void* PANEL_6BIT_COLOR ; 
 void* PANEL_8BIT_COLOR ; 
 scalar_t__ stub1 (struct dc_bios*,struct bp_crtc_source_select*) ; 

__attribute__((used)) static enum dc_status bios_parser_crtc_source_select(
		struct pipe_ctx *pipe_ctx)
{
	struct dc_bios *dcb;
	/* call VBIOS table to set CRTC source for the HW
	 * encoder block
	 * note: video bios clears all FMT setting here. */
	struct bp_crtc_source_select crtc_source_select = {0};
	const struct dc_sink *sink = pipe_ctx->stream->sink;

	crtc_source_select.engine_id = pipe_ctx->stream_res.stream_enc->id;
	crtc_source_select.controller_id = pipe_ctx->stream_res.tg->inst + 1;
	/*TODO: Need to un-hardcode color depth, dp_audio and account for
	 * the case where signal and sink signal is different (translator
	 * encoder)*/
	crtc_source_select.signal = pipe_ctx->stream->signal;
	crtc_source_select.enable_dp_audio = false;
	crtc_source_select.sink_signal = pipe_ctx->stream->signal;

	switch (pipe_ctx->stream->timing.display_color_depth) {
	case COLOR_DEPTH_666:
		crtc_source_select.display_output_bit_depth = PANEL_6BIT_COLOR;
		break;
	case COLOR_DEPTH_888:
		crtc_source_select.display_output_bit_depth = PANEL_8BIT_COLOR;
		break;
	case COLOR_DEPTH_101010:
		crtc_source_select.display_output_bit_depth = PANEL_10BIT_COLOR;
		break;
	case COLOR_DEPTH_121212:
		crtc_source_select.display_output_bit_depth = PANEL_12BIT_COLOR;
		break;
	default:
		BREAK_TO_DEBUGGER();
		crtc_source_select.display_output_bit_depth = PANEL_8BIT_COLOR;
		break;
	}

	dcb = sink->ctx->dc_bios;

	if (BP_RESULT_OK != dcb->funcs->crtc_source_select(
		dcb,
		&crtc_source_select)) {
		return DC_ERROR_UNEXPECTED;
	}

	return DC_OK;
}