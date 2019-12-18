#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct resource_pool {unsigned int pipe_count; unsigned int stream_enc_count; unsigned int timing_generator_count; TYPE_5__** dpps; int /*<<< orphan*/ * opps; int /*<<< orphan*/ * transforms; int /*<<< orphan*/ * ipps; int /*<<< orphan*/ * hubps; int /*<<< orphan*/ * mis; int /*<<< orphan*/ * timing_generators; TYPE_6__** stream_enc; } ;
struct resource_context {struct pipe_ctx* pipe_ctx; } ;
struct TYPE_12__ {int /*<<< orphan*/  mpcc_inst; TYPE_5__* dpp; int /*<<< orphan*/  xfm; int /*<<< orphan*/  ipp; int /*<<< orphan*/  hubp; int /*<<< orphan*/  mi; } ;
struct TYPE_11__ {int /*<<< orphan*/  opp; int /*<<< orphan*/  tg; } ;
struct pipe_ctx {unsigned int pipe_idx; struct dc_stream_state* stream; TYPE_4__ plane_res; TYPE_3__ stream_res; } ;
struct dc_stream_state {struct dc_link* link; } ;
struct dc_link {TYPE_7__* link_enc; } ;
struct TYPE_15__ {TYPE_1__* funcs; } ;
struct TYPE_14__ {TYPE_2__* funcs; } ;
struct TYPE_13__ {int /*<<< orphan*/  inst; } ;
struct TYPE_10__ {unsigned int (* dig_source_otg ) (TYPE_6__*) ;} ;
struct TYPE_9__ {unsigned int (* get_dig_frontend ) (TYPE_7__*) ;int /*<<< orphan*/  (* is_dig_enabled ) (TYPE_7__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_7__*) ; 
 unsigned int stub2 (TYPE_7__*) ; 
 unsigned int stub3 (TYPE_6__*) ; 

__attribute__((used)) static int acquire_resource_from_hw_enabled_state(
		struct resource_context *res_ctx,
		const struct resource_pool *pool,
		struct dc_stream_state *stream)
{
	struct dc_link *link = stream->link;
	unsigned int inst, tg_inst;

	/* Check for enabled DIG to identify enabled display */
	if (!link->link_enc->funcs->is_dig_enabled(link->link_enc))
		return -1;

	/* Check for which front end is used by this encoder.
	 * Note the inst is 1 indexed, where 0 is undefined.
	 * Note that DIG_FE can source from different OTG but our
	 * current implementation always map 1-to-1, so this code makes
	 * the same assumption and doesn't check OTG source.
	 */
	inst = link->link_enc->funcs->get_dig_frontend(link->link_enc);

	/* Instance should be within the range of the pool */
	if (inst >= pool->pipe_count)
		return -1;

	if (inst >= pool->stream_enc_count)
		return -1;

	tg_inst = pool->stream_enc[inst]->funcs->dig_source_otg(pool->stream_enc[inst]);

	if (tg_inst >= pool->timing_generator_count)
		return false;

	if (!res_ctx->pipe_ctx[tg_inst].stream) {
		struct pipe_ctx *pipe_ctx = &res_ctx->pipe_ctx[tg_inst];

		pipe_ctx->stream_res.tg = pool->timing_generators[tg_inst];
		pipe_ctx->plane_res.mi = pool->mis[tg_inst];
		pipe_ctx->plane_res.hubp = pool->hubps[tg_inst];
		pipe_ctx->plane_res.ipp = pool->ipps[tg_inst];
		pipe_ctx->plane_res.xfm = pool->transforms[tg_inst];
		pipe_ctx->plane_res.dpp = pool->dpps[tg_inst];
		pipe_ctx->stream_res.opp = pool->opps[tg_inst];

		if (pool->dpps[tg_inst])
			pipe_ctx->plane_res.mpcc_inst = pool->dpps[tg_inst]->inst;
		pipe_ctx->pipe_idx = tg_inst;

		pipe_ctx->stream = stream;
		return tg_inst;
	}

	return -1;
}