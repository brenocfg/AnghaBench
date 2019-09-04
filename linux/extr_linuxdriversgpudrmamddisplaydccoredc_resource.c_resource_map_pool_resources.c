#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct resource_pool {int /*<<< orphan*/  abm; } ;
struct TYPE_19__ {TYPE_8__* stream_enc; TYPE_4__* tg; int /*<<< orphan*/  abm; scalar_t__ audio; } ;
struct pipe_ctx {TYPE_6__ stream_res; TYPE_3__* stream; } ;
struct TYPE_15__ {scalar_t__ mode_count; } ;
struct dc_stream_state {TYPE_2__ audio_info; TYPE_1__* sink; } ;
struct TYPE_20__ {struct pipe_ctx* pipe_ctx; } ;
struct dc_state {int stream_count; TYPE_5__* stream_status; struct dc_stream_state** streams; TYPE_7__ res_ctx; } ;
struct dc_context {int dummy; } ;
struct dc {struct dc_context* ctx; struct resource_pool* res_pool; } ;
typedef  enum dc_status { ____Placeholder_dc_status } dc_status ;
struct TYPE_21__ {int /*<<< orphan*/  id; } ;
struct TYPE_18__ {int /*<<< orphan*/  stream_enc_inst; int /*<<< orphan*/  primary_otg_inst; } ;
struct TYPE_17__ {int /*<<< orphan*/  inst; } ;
struct TYPE_16__ {int /*<<< orphan*/  signal; } ;
struct TYPE_14__ {int /*<<< orphan*/  converter_disable_audio; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_ERROR (char*,struct dc_stream_state*) ; 
 int DC_ERROR_UNEXPECTED ; 
 int DC_NO_CONTROLLER_RESOURCE ; 
 int DC_NO_STREAM_ENG_RESOURCE ; 
 int DC_OK ; 
 int acquire_first_free_pipe (TYPE_7__*,struct resource_pool const*,struct dc_stream_state*) ; 
 int /*<<< orphan*/  calculate_phy_pix_clks (struct dc_stream_state*) ; 
 scalar_t__ dc_is_audio_capable_signal (int /*<<< orphan*/ ) ; 
 scalar_t__ dc_is_embedded_signal (int /*<<< orphan*/ ) ; 
 scalar_t__ find_first_free_audio (TYPE_7__*,struct resource_pool const*,int /*<<< orphan*/ ) ; 
 TYPE_8__* find_first_free_match_stream_enc_for_link (TYPE_7__*,struct resource_pool const*,struct dc_stream_state*) ; 
 int /*<<< orphan*/  update_audio_usage (TYPE_7__*,struct resource_pool const*,scalar_t__,int) ; 
 int /*<<< orphan*/  update_stream_engine_usage (TYPE_7__*,struct resource_pool const*,TYPE_8__*,int) ; 

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
		find_first_free_match_stream_enc_for_link(
			&context->res_ctx, pool, stream);

	if (!pipe_ctx->stream_res.stream_enc)
		return DC_NO_STREAM_ENG_RESOURCE;

	update_stream_engine_usage(
		&context->res_ctx, pool,
		pipe_ctx->stream_res.stream_enc,
		true);

	/* TODO: Add check if ASIC support and EDID audio */
	if (!stream->sink->converter_disable_audio &&
	    dc_is_audio_capable_signal(pipe_ctx->stream->signal) &&
	    stream->audio_info.mode_count) {
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
			return DC_OK;
		}

	DC_ERROR("Stream %p not found in new ctx!\n", stream);
	return DC_ERROR_UNEXPECTED;
}