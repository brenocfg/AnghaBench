#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_19__ {TYPE_9__* mi; } ;
struct pipe_ctx {int pipe_idx; TYPE_8__ plane_res; } ;
struct TYPE_15__ {int /*<<< orphan*/  (* enable_display_power_gating ) (struct dc*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct dc {TYPE_7__* res_pool; TYPE_5__* ctx; TYPE_4__ hwss; TYPE_3__* current_state; } ;
struct TYPE_20__ {int inst; } ;
struct TYPE_18__ {TYPE_10__** transforms; } ;
struct TYPE_17__ {int /*<<< orphan*/  (* transform_reset ) (TYPE_10__*) ;} ;
struct TYPE_16__ {int /*<<< orphan*/  dc_bios; } ;
struct TYPE_13__ {TYPE_1__* pipe_ctx; } ;
struct TYPE_14__ {TYPE_2__ res_ctx; } ;
struct TYPE_12__ {scalar_t__ stream; } ;
struct TYPE_11__ {TYPE_6__* funcs; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIPE_GATING_CONTROL_ENABLE ; 
 int /*<<< orphan*/  stub1 (struct dc*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_10__*) ; 

__attribute__((used)) static void dce110_power_down_fe(struct dc *dc, struct pipe_ctx *pipe_ctx)
{
	int fe_idx = pipe_ctx->plane_res.mi ?
		pipe_ctx->plane_res.mi->inst : pipe_ctx->pipe_idx;

	/* Do not power down fe when stream is active on dce*/
	if (dc->current_state->res_ctx.pipe_ctx[fe_idx].stream)
		return;

	dc->hwss.enable_display_power_gating(
		dc, fe_idx, dc->ctx->dc_bios, PIPE_GATING_CONTROL_ENABLE);

	dc->res_pool->transforms[fe_idx]->funcs->transform_reset(
				dc->res_pool->transforms[fe_idx]);
}