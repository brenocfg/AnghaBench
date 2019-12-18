#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_8__* hubp; } ;
struct TYPE_12__ {TYPE_7__* opp; } ;
struct pipe_ctx {TYPE_5__ plane_res; TYPE_3__ stream_res; } ;
struct dce_hwseq {int dummy; } ;
struct dc_state {int dummy; } ;
struct TYPE_15__ {scalar_t__ sanity_checks; } ;
struct TYPE_13__ {scalar_t__ gpu_vm_support; } ;
struct dc {TYPE_6__ debug; TYPE_4__ config; struct dce_hwseq* hwseq; } ;
struct TYPE_17__ {TYPE_1__* funcs; int /*<<< orphan*/  inst; } ;
struct TYPE_16__ {TYPE_2__* funcs; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* opp_pipe_clock_control ) (TYPE_7__*,int) ;} ;
struct TYPE_10__ {int /*<<< orphan*/  (* hubp_clk_cntl ) (TYPE_8__*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dcn10_program_pte_vm (struct dce_hwseq*,TYPE_8__*) ; 
 int /*<<< orphan*/  dcn10_verify_allow_pstate_change_high (struct dc*) ; 
 int /*<<< orphan*/  power_on_plane (struct dce_hwseq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_8__*,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_7__*,int) ; 
 int /*<<< orphan*/  undo_DEGVIDCN10_253_wa (struct dc*) ; 

__attribute__((used)) static void dcn10_enable_plane(
	struct dc *dc,
	struct pipe_ctx *pipe_ctx,
	struct dc_state *context)
{
	struct dce_hwseq *hws = dc->hwseq;

	if (dc->debug.sanity_checks) {
		dcn10_verify_allow_pstate_change_high(dc);
	}

	undo_DEGVIDCN10_253_wa(dc);

	power_on_plane(dc->hwseq,
		pipe_ctx->plane_res.hubp->inst);

	/* enable DCFCLK current DCHUB */
	pipe_ctx->plane_res.hubp->funcs->hubp_clk_cntl(pipe_ctx->plane_res.hubp, true);

	/* make sure OPP_PIPE_CLOCK_EN = 1 */
	pipe_ctx->stream_res.opp->funcs->opp_pipe_clock_control(
			pipe_ctx->stream_res.opp,
			true);

/* TODO: enable/disable in dm as per update type.
	if (plane_state) {
		DC_LOG_DC(dc->ctx->logger,
				"Pipe:%d 0x%x: addr hi:0x%x, "
				"addr low:0x%x, "
				"src: %d, %d, %d,"
				" %d; dst: %d, %d, %d, %d;\n",
				pipe_ctx->pipe_idx,
				plane_state,
				plane_state->address.grph.addr.high_part,
				plane_state->address.grph.addr.low_part,
				plane_state->src_rect.x,
				plane_state->src_rect.y,
				plane_state->src_rect.width,
				plane_state->src_rect.height,
				plane_state->dst_rect.x,
				plane_state->dst_rect.y,
				plane_state->dst_rect.width,
				plane_state->dst_rect.height);

		DC_LOG_DC(dc->ctx->logger,
				"Pipe %d: width, height, x, y         format:%d\n"
				"viewport:%d, %d, %d, %d\n"
				"recout:  %d, %d, %d, %d\n",
				pipe_ctx->pipe_idx,
				plane_state->format,
				pipe_ctx->plane_res.scl_data.viewport.width,
				pipe_ctx->plane_res.scl_data.viewport.height,
				pipe_ctx->plane_res.scl_data.viewport.x,
				pipe_ctx->plane_res.scl_data.viewport.y,
				pipe_ctx->plane_res.scl_data.recout.width,
				pipe_ctx->plane_res.scl_data.recout.height,
				pipe_ctx->plane_res.scl_data.recout.x,
				pipe_ctx->plane_res.scl_data.recout.y);
		print_rq_dlg_ttu(dc, pipe_ctx);
	}
*/
	if (dc->config.gpu_vm_support)
		dcn10_program_pte_vm(hws, pipe_ctx->plane_res.hubp);

	if (dc->debug.sanity_checks) {
		dcn10_verify_allow_pstate_change_high(dc);
	}
}