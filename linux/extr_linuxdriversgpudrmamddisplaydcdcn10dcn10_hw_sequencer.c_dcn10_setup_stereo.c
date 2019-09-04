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
struct TYPE_8__ {TYPE_4__* tg; TYPE_5__* opp; } ;
struct pipe_ctx {TYPE_3__ stream_res; struct dc_stream_state* stream; } ;
struct dc_stream_state {int /*<<< orphan*/  timing; } ;
struct dc {int dummy; } ;
struct crtc_stereo_flags {int PROGRAM_STEREO; int /*<<< orphan*/  member_0; } ;
struct TYPE_10__ {TYPE_1__* funcs; } ;
struct TYPE_9__ {TYPE_2__* funcs; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* program_stereo ) (TYPE_4__*,int /*<<< orphan*/ *,struct crtc_stereo_flags*) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  (* opp_program_stereo ) (TYPE_5__*,int,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dcn10_config_stereo_parameters (struct dc_stream_state*,struct crtc_stereo_flags*) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*,int /*<<< orphan*/ *,struct crtc_stereo_flags*) ; 

__attribute__((used)) static void dcn10_setup_stereo(struct pipe_ctx *pipe_ctx, struct dc *dc)
{
	struct crtc_stereo_flags flags = { 0 };
	struct dc_stream_state *stream = pipe_ctx->stream;

	dcn10_config_stereo_parameters(stream, &flags);

	pipe_ctx->stream_res.opp->funcs->opp_program_stereo(
		pipe_ctx->stream_res.opp,
		flags.PROGRAM_STEREO == 1 ? true:false,
		&stream->timing);

	pipe_ctx->stream_res.tg->funcs->program_stereo(
		pipe_ctx->stream_res.tg,
		&stream->timing,
		&flags);

	return;
}