#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct resource_pool {int underlay_pipe_index; } ;
struct resource_context {TYPE_3__* pipe_ctx; } ;
struct dce_watermarks {int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_9__ {TYPE_1__* funcs; } ;
struct TYPE_7__ {TYPE_4__* mi; } ;
struct TYPE_8__ {TYPE_2__ plane_res; int /*<<< orphan*/ * stream; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* mem_input_program_chroma_display_marks ) (TYPE_4__*,struct dce_watermarks,struct dce_watermarks,struct dce_watermarks,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* mem_input_program_display_marks ) (TYPE_4__*,struct dce_watermarks,struct dce_watermarks,struct dce_watermarks,struct dce_watermarks,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int MAX_PIPES ; 
 int /*<<< orphan*/  MAX_WATERMARK ; 
 int /*<<< orphan*/  SAFE_NBP_MARK ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,struct dce_watermarks,struct dce_watermarks,struct dce_watermarks,struct dce_watermarks,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*,struct dce_watermarks,struct dce_watermarks,struct dce_watermarks,int /*<<< orphan*/ ) ; 

void dce110_set_safe_displaymarks(
		struct resource_context *res_ctx,
		const struct resource_pool *pool)
{
	int i;
	int underlay_idx = pool->underlay_pipe_index;
	struct dce_watermarks max_marks = {
		MAX_WATERMARK, MAX_WATERMARK, MAX_WATERMARK, MAX_WATERMARK };
	struct dce_watermarks nbp_marks = {
		SAFE_NBP_MARK, SAFE_NBP_MARK, SAFE_NBP_MARK, SAFE_NBP_MARK };
	struct dce_watermarks min_marks = { 0, 0, 0, 0};

	for (i = 0; i < MAX_PIPES; i++) {
		if (res_ctx->pipe_ctx[i].stream == NULL || res_ctx->pipe_ctx[i].plane_res.mi == NULL)
			continue;

		res_ctx->pipe_ctx[i].plane_res.mi->funcs->mem_input_program_display_marks(
				res_ctx->pipe_ctx[i].plane_res.mi,
				nbp_marks,
				max_marks,
				min_marks,
				max_marks,
				MAX_WATERMARK);

		if (i == underlay_idx)
			res_ctx->pipe_ctx[i].plane_res.mi->funcs->mem_input_program_chroma_display_marks(
				res_ctx->pipe_ctx[i].plane_res.mi,
				nbp_marks,
				max_marks,
				max_marks,
				MAX_WATERMARK);

	}
}