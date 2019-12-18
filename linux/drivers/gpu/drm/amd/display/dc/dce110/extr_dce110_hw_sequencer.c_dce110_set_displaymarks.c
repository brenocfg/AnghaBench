#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_15__ {TYPE_9__* mi; } ;
struct pipe_ctx {TYPE_5__ plane_res; int /*<<< orphan*/ * stream; } ;
struct TYPE_16__ {int /*<<< orphan*/ * urgent_wm_ns; int /*<<< orphan*/ * stutter_exit_wm_ns; int /*<<< orphan*/ * nbp_state_change_wm_ns; int /*<<< orphan*/ * stutter_entry_wm_ns; } ;
struct TYPE_17__ {TYPE_6__ dce; } ;
struct TYPE_18__ {TYPE_7__ bw; } ;
struct TYPE_12__ {struct pipe_ctx* pipe_ctx; } ;
struct dc_state {TYPE_8__ bw_ctx; TYPE_2__ res_ctx; } ;
struct dc {TYPE_3__* bw_vbios; TYPE_1__* res_pool; } ;
struct TYPE_19__ {TYPE_4__* funcs; } ;
struct TYPE_14__ {int /*<<< orphan*/  (* mem_input_program_chroma_display_marks ) (TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* mem_input_program_display_marks ) (TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_13__ {int /*<<< orphan*/  blackout_duration; } ;
struct TYPE_11__ {unsigned int underlay_pipe_index; } ;

/* Variables and functions */
 size_t MAX_PIPES ; 
 int /*<<< orphan*/  compute_pstate_blackout_duration (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dce110_set_displaymarks(
	const struct dc *dc,
	struct dc_state *context)
{
	uint8_t i, num_pipes;
	unsigned int underlay_idx = dc->res_pool->underlay_pipe_index;

	for (i = 0, num_pipes = 0; i < MAX_PIPES; i++) {
		struct pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[i];
		uint32_t total_dest_line_time_ns;

		if (pipe_ctx->stream == NULL)
			continue;

		total_dest_line_time_ns = compute_pstate_blackout_duration(
			dc->bw_vbios->blackout_duration, pipe_ctx->stream);
		pipe_ctx->plane_res.mi->funcs->mem_input_program_display_marks(
			pipe_ctx->plane_res.mi,
			context->bw_ctx.bw.dce.nbp_state_change_wm_ns[num_pipes],
			context->bw_ctx.bw.dce.stutter_exit_wm_ns[num_pipes],
			context->bw_ctx.bw.dce.stutter_entry_wm_ns[num_pipes],
			context->bw_ctx.bw.dce.urgent_wm_ns[num_pipes],
			total_dest_line_time_ns);
		if (i == underlay_idx) {
			num_pipes++;
			pipe_ctx->plane_res.mi->funcs->mem_input_program_chroma_display_marks(
				pipe_ctx->plane_res.mi,
				context->bw_ctx.bw.dce.nbp_state_change_wm_ns[num_pipes],
				context->bw_ctx.bw.dce.stutter_exit_wm_ns[num_pipes],
				context->bw_ctx.bw.dce.urgent_wm_ns[num_pipes],
				total_dest_line_time_ns);
		}
		num_pipes++;
	}
}