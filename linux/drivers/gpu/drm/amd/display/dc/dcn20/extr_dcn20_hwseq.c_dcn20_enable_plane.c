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
typedef  struct TYPE_15__   TYPE_11__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct TYPE_20__ {int /*<<< orphan*/  quad_part; } ;
struct TYPE_19__ {int /*<<< orphan*/  quad_part; } ;
struct TYPE_18__ {scalar_t__ quad_part; } ;
struct vm_system_aperture_param {TYPE_5__ sys_high; TYPE_4__ sys_low; TYPE_3__ sys_default; } ;
struct TYPE_24__ {TYPE_10__* hubp; } ;
struct TYPE_17__ {TYPE_11__* opp; } ;
struct pipe_ctx {TYPE_9__ plane_res; TYPE_2__ stream_res; } ;
struct dc_state {int dummy; } ;
struct TYPE_21__ {int /*<<< orphan*/  end_addr; int /*<<< orphan*/  start_addr; } ;
struct TYPE_22__ {TYPE_6__ system_aperture; scalar_t__ valid; } ;
struct dc {TYPE_7__ vm_pa_config; int /*<<< orphan*/  hwseq; } ;
struct TYPE_23__ {int /*<<< orphan*/  (* hubp_set_vm_system_aperture_settings ) (TYPE_10__*,struct vm_system_aperture_param*) ;int /*<<< orphan*/  (* hubp_init ) (TYPE_10__*) ;int /*<<< orphan*/  (* hubp_clk_cntl ) (TYPE_10__*,int) ;} ;
struct TYPE_16__ {int /*<<< orphan*/  (* opp_pipe_clock_control ) (TYPE_11__*,int) ;} ;
struct TYPE_15__ {TYPE_1__* funcs; } ;
struct TYPE_14__ {TYPE_8__* funcs; } ;

/* Variables and functions */
 int /*<<< orphan*/  dcn20_power_on_plane (int /*<<< orphan*/ ,struct pipe_ctx*) ; 
 int /*<<< orphan*/  stub1 (TYPE_10__*,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_10__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_11__*,int) ; 
 int /*<<< orphan*/  stub4 (TYPE_10__*,struct vm_system_aperture_param*) ; 

void dcn20_enable_plane(
	struct dc *dc,
	struct pipe_ctx *pipe_ctx,
	struct dc_state *context)
{
	//if (dc->debug.sanity_checks) {
	//	dcn10_verify_allow_pstate_change_high(dc);
	//}
	dcn20_power_on_plane(dc->hwseq, pipe_ctx);

	/* enable DCFCLK current DCHUB */
	pipe_ctx->plane_res.hubp->funcs->hubp_clk_cntl(pipe_ctx->plane_res.hubp, true);

	/* initialize HUBP on power up */
	pipe_ctx->plane_res.hubp->funcs->hubp_init(pipe_ctx->plane_res.hubp);

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
	if (dc->vm_pa_config.valid) {
		struct vm_system_aperture_param apt;

		apt.sys_default.quad_part = 0;

		apt.sys_low.quad_part = dc->vm_pa_config.system_aperture.start_addr;
		apt.sys_high.quad_part = dc->vm_pa_config.system_aperture.end_addr;

		// Program system aperture settings
		pipe_ctx->plane_res.hubp->funcs->hubp_set_vm_system_aperture_settings(pipe_ctx->plane_res.hubp, &apt);
	}

//	if (dc->debug.sanity_checks) {
//		dcn10_verify_allow_pstate_change_high(dc);
//	}
}