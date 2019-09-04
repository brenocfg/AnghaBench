#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct pp_smu_funcs_rv {int /*<<< orphan*/  pp_smu; int /*<<< orphan*/  (* set_pme_wa_enable ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_13__ {TYPE_11__* stream_enc; TYPE_12__* audio; } ;
struct pipe_ctx {TYPE_10__ stream_res; TYPE_2__* stream; } ;
struct dc {TYPE_7__* current_state; TYPE_3__* res_pool; } ;
struct TYPE_24__ {int /*<<< orphan*/  (* audio_mute_control ) (TYPE_11__*,int) ;} ;
struct TYPE_23__ {int /*<<< orphan*/  (* az_enable ) (TYPE_12__*) ;} ;
struct TYPE_21__ {TYPE_5__* pipe_ctx; } ;
struct TYPE_22__ {TYPE_6__ res_ctx; } ;
struct TYPE_19__ {int /*<<< orphan*/ * audio; } ;
struct TYPE_20__ {TYPE_4__ stream_res; } ;
struct TYPE_18__ {struct pp_smu_funcs_rv* pp_smu; } ;
struct TYPE_17__ {TYPE_1__* ctx; } ;
struct TYPE_16__ {struct dc* dc; } ;
struct TYPE_15__ {TYPE_8__* funcs; } ;
struct TYPE_14__ {TYPE_9__* funcs; } ;

/* Variables and functions */
 unsigned int MAX_PIPES ; 
 int /*<<< orphan*/  stub1 (TYPE_12__*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (TYPE_11__*,int) ; 

void dce110_enable_audio_stream(struct pipe_ctx *pipe_ctx)
{
	struct dc *core_dc = pipe_ctx->stream->ctx->dc;
	/* notify audio driver for audio modes of monitor */
	struct pp_smu_funcs_rv *pp_smu = core_dc->res_pool->pp_smu;
	unsigned int i, num_audio = 1;

	if (pipe_ctx->stream_res.audio) {
		for (i = 0; i < MAX_PIPES; i++) {
			/*current_state not updated yet*/
			if (core_dc->current_state->res_ctx.pipe_ctx[i].stream_res.audio != NULL)
				num_audio++;
		}

		pipe_ctx->stream_res.audio->funcs->az_enable(pipe_ctx->stream_res.audio);

		if (num_audio >= 1 && pp_smu != NULL && pp_smu->set_pme_wa_enable != NULL)
			/*this is the first audio. apply the PME w/a in order to wake AZ from D3*/
			pp_smu->set_pme_wa_enable(&pp_smu->pp_smu);
		/* un-mute audio */
		/* TODO: audio should be per stream rather than per link */
		pipe_ctx->stream_res.stream_enc->funcs->audio_mute_control(
			pipe_ctx->stream_res.stream_enc, false);
	}
}