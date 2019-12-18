#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_9__ ;
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_13__ ;
typedef  struct TYPE_22__   TYPE_11__ ;
typedef  struct TYPE_21__   TYPE_10__ ;

/* Type definitions */
struct resource_pool {int /*<<< orphan*/  abm; TYPE_3__* funcs; } ;
struct TYPE_32__ {TYPE_13__* audio; TYPE_11__* stream_enc; TYPE_7__* tg; int /*<<< orphan*/  abm; } ;
struct pipe_ctx {TYPE_9__ stream_res; TYPE_6__* stream; } ;
struct TYPE_27__ {scalar_t__ all; } ;
struct TYPE_28__ {TYPE_4__ flags; scalar_t__ mode_count; } ;
struct dc_stream_state {int apply_seamless_boot_optimization; TYPE_5__ audio_info; int /*<<< orphan*/  converter_disable_audio; int /*<<< orphan*/  timing; int /*<<< orphan*/  sink; } ;
struct TYPE_21__ {struct pipe_ctx* pipe_ctx; } ;
struct dc_state {int stream_count; TYPE_8__* stream_status; struct dc_stream_state** streams; TYPE_10__ res_ctx; } ;
struct dc_context {struct dc_bios* dc_bios; } ;
struct dc_bios {TYPE_2__* funcs; } ;
struct TYPE_24__ {scalar_t__ allow_seamless_boot_optimization; } ;
struct dc {struct resource_pool* res_pool; TYPE_1__ config; struct dc_context* ctx; } ;
typedef  enum dc_status { ____Placeholder_dc_status } dc_status ;
struct TYPE_31__ {int audio_inst; int /*<<< orphan*/  stream_enc_inst; int /*<<< orphan*/  primary_otg_inst; } ;
struct TYPE_30__ {int /*<<< orphan*/  inst; } ;
struct TYPE_29__ {int /*<<< orphan*/  signal; } ;
struct TYPE_26__ {TYPE_11__* (* find_first_free_match_stream_enc_for_link ) (TYPE_10__*,struct resource_pool const*,struct dc_stream_state*) ;} ;
struct TYPE_25__ {int /*<<< orphan*/  (* is_accelerated_mode ) (struct dc_bios*) ;} ;
struct TYPE_23__ {int inst; } ;
struct TYPE_22__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_ERROR (char*,struct dc_stream_state*) ; 
 int DC_ERROR_UNEXPECTED ; 
 int DC_NO_CONTROLLER_RESOURCE ; 
 int DC_NO_STREAM_ENC_RESOURCE ; 
 int DC_OK ; 
 int acquire_first_free_pipe (TYPE_10__*,struct resource_pool const*,struct dc_stream_state*) ; 
 int acquire_first_split_pipe (TYPE_10__*,struct resource_pool const*,struct dc_stream_state*) ; 
 int acquire_resource_from_hw_enabled_state (TYPE_10__*,struct resource_pool const*,struct dc_stream_state*) ; 
 int /*<<< orphan*/  calculate_phy_pix_clks (struct dc_stream_state*) ; 
 scalar_t__ dc_is_audio_capable_signal (int /*<<< orphan*/ ) ; 
 scalar_t__ dc_is_embedded_signal (int /*<<< orphan*/ ) ; 
 scalar_t__ dc_validate_seamless_boot_timing (struct dc const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_13__* find_first_free_audio (TYPE_10__*,struct resource_pool const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct dc_bios*) ; 
 TYPE_11__* stub2 (TYPE_10__*,struct resource_pool const*,struct dc_stream_state*) ; 
 int /*<<< orphan*/  update_audio_usage (TYPE_10__*,struct resource_pool const*,TYPE_13__*,int) ; 
 int /*<<< orphan*/  update_stream_engine_usage (TYPE_10__*,struct resource_pool const*,TYPE_11__*,int) ; 

enum dc_status resource_map_pool_resources(
		const struct dc  *dc,
		struct dc_state *context,
		struct dc_stream_state *stream)
{
	const struct resource_pool *pool = dc->res_pool;
	int i;
	struct dc_context *dc_ctx = dc->ctx;
	struct pipe_ctx *pipe_ctx = NULL;
	int pipe_idx = -1;
	struct dc_bios *dcb = dc->ctx->dc_bios;

	/* TODO Check if this is needed */
	/*if (!resource_is_stream_unchanged(old_context, stream)) {
			if (stream != NULL && old_context->streams[i] != NULL) {
				stream->bit_depth_params =
						old_context->streams[i]->bit_depth_params;
				stream->clamping = old_context->streams[i]->clamping;
				continue;
			}
		}
	*/

	calculate_phy_pix_clks(stream);

	/* TODO: Check Linux */
	if (dc->config.allow_seamless_boot_optimization &&
			!dcb->funcs->is_accelerated_mode(dcb)) {
		if (dc_validate_seamless_boot_timing(dc, stream->sink, &stream->timing))
			stream->apply_seamless_boot_optimization = true;
	}

	if (stream->apply_seamless_boot_optimization)
		pipe_idx = acquire_resource_from_hw_enabled_state(
				&context->res_ctx,
				pool,
				stream);

	if (pipe_idx < 0)
		/* acquire new resources */
		pipe_idx = acquire_first_free_pipe(&context->res_ctx, pool, stream);

#ifdef CONFIG_DRM_AMD_DC_DCN1_0
	if (pipe_idx < 0)
		pipe_idx = acquire_first_split_pipe(&context->res_ctx, pool, stream);
#endif

	if (pipe_idx < 0 || context->res_ctx.pipe_ctx[pipe_idx].stream_res.tg == NULL)
		return DC_NO_CONTROLLER_RESOURCE;

	pipe_ctx = &context->res_ctx.pipe_ctx[pipe_idx];

	pipe_ctx->stream_res.stream_enc =
		dc->res_pool->funcs->find_first_free_match_stream_enc_for_link(
			&context->res_ctx, pool, stream);

	if (!pipe_ctx->stream_res.stream_enc)
		return DC_NO_STREAM_ENC_RESOURCE;

	update_stream_engine_usage(
		&context->res_ctx, pool,
		pipe_ctx->stream_res.stream_enc,
		true);

	/* TODO: Add check if ASIC support and EDID audio */
	if (!stream->converter_disable_audio &&
	    dc_is_audio_capable_signal(pipe_ctx->stream->signal) &&
	    stream->audio_info.mode_count && stream->audio_info.flags.all) {
		pipe_ctx->stream_res.audio = find_first_free_audio(
		&context->res_ctx, pool, pipe_ctx->stream_res.stream_enc->id);

		/*
		 * Audio assigned in order first come first get.
		 * There are asics which has number of audio
		 * resources less then number of pipes
		 */
		if (pipe_ctx->stream_res.audio)
			update_audio_usage(&context->res_ctx, pool,
					   pipe_ctx->stream_res.audio, true);
	}

	/* Add ABM to the resource if on EDP */
	if (pipe_ctx->stream && dc_is_embedded_signal(pipe_ctx->stream->signal))
		pipe_ctx->stream_res.abm = pool->abm;

	for (i = 0; i < context->stream_count; i++)
		if (context->streams[i] == stream) {
			context->stream_status[i].primary_otg_inst = pipe_ctx->stream_res.tg->inst;
			context->stream_status[i].stream_enc_inst = pipe_ctx->stream_res.stream_enc->id;
			context->stream_status[i].audio_inst =
				pipe_ctx->stream_res.audio ? pipe_ctx->stream_res.audio->inst : -1;

			return DC_OK;
		}

	DC_ERROR("Stream %p not found in new ctx!\n", stream);
	return DC_ERROR_UNEXPECTED;
}