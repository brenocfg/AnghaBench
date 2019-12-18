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
typedef  size_t uint32_t ;
struct resource_context {struct pipe_ctx* pipe_ctx; } ;
struct pipe_ctx {unsigned int pipe_idx; TYPE_7__* plane_state; TYPE_4__* stream; } ;
struct dc_state {int stream_count; struct resource_context res_ctx; } ;
struct dc {TYPE_2__* res_pool; TYPE_1__* ctx; int /*<<< orphan*/  fbc_compressor; } ;
struct TYPE_12__ {scalar_t__ array_mode; } ;
struct TYPE_13__ {TYPE_5__ gfx8; } ;
struct TYPE_14__ {TYPE_6__ tiling_info; } ;
struct TYPE_11__ {TYPE_3__* link; } ;
struct TYPE_10__ {scalar_t__ connector_signal; scalar_t__ psr_enabled; } ;
struct TYPE_9__ {unsigned int underlay_pipe_index; size_t pipe_count; } ;
struct TYPE_8__ {int /*<<< orphan*/  fbc_gpu_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ DC_ARRAY_LINEAR_GENERAL ; 
 scalar_t__ SIGNAL_TYPE_EDP ; 

__attribute__((used)) static bool should_enable_fbc(struct dc *dc,
		struct dc_state *context,
		uint32_t *pipe_idx)
{
	uint32_t i;
	struct pipe_ctx *pipe_ctx = NULL;
	struct resource_context *res_ctx = &context->res_ctx;
	unsigned int underlay_idx = dc->res_pool->underlay_pipe_index;


	ASSERT(dc->fbc_compressor);

	/* FBC memory should be allocated */
	if (!dc->ctx->fbc_gpu_addr)
		return false;

	/* Only supports single display */
	if (context->stream_count != 1)
		return false;

	for (i = 0; i < dc->res_pool->pipe_count; i++) {
		if (res_ctx->pipe_ctx[i].stream) {

			pipe_ctx = &res_ctx->pipe_ctx[i];

			if (!pipe_ctx)
				continue;

			/* fbc not applicable on underlay pipe */
			if (pipe_ctx->pipe_idx != underlay_idx) {
				*pipe_idx = i;
				break;
			}
		}
	}

	if (i == dc->res_pool->pipe_count)
		return false;

	if (!pipe_ctx->stream->link)
		return false;

	/* Only supports eDP */
	if (pipe_ctx->stream->link->connector_signal != SIGNAL_TYPE_EDP)
		return false;

	/* PSR should not be enabled */
	if (pipe_ctx->stream->link->psr_enabled)
		return false;

	/* Nothing to compress */
	if (!pipe_ctx->plane_state)
		return false;

	/* Only for non-linear tiling */
	if (pipe_ctx->plane_state->tiling_info.gfx8.array_mode == DC_ARRAY_LINEAR_GENERAL)
		return false;

	return true;
}