#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_40__   TYPE_9__ ;
typedef  struct TYPE_39__   TYPE_8__ ;
typedef  struct TYPE_38__   TYPE_7__ ;
typedef  struct TYPE_37__   TYPE_6__ ;
typedef  struct TYPE_36__   TYPE_5__ ;
typedef  struct TYPE_35__   TYPE_4__ ;
typedef  struct TYPE_34__   TYPE_3__ ;
typedef  struct TYPE_33__   TYPE_2__ ;
typedef  struct TYPE_32__   TYPE_20__ ;
typedef  struct TYPE_31__   TYPE_1__ ;
typedef  struct TYPE_30__   TYPE_19__ ;
typedef  struct TYPE_29__   TYPE_18__ ;
typedef  struct TYPE_28__   TYPE_17__ ;
typedef  struct TYPE_27__   TYPE_16__ ;
typedef  struct TYPE_26__   TYPE_15__ ;
typedef  struct TYPE_25__   TYPE_14__ ;
typedef  struct TYPE_24__   TYPE_13__ ;
typedef  struct TYPE_23__   TYPE_12__ ;
typedef  struct TYPE_22__   TYPE_11__ ;
typedef  struct TYPE_21__   TYPE_10__ ;

/* Type definitions */
struct TYPE_21__ {int /*<<< orphan*/  surface_size; } ;
union plane_size {TYPE_10__ grph; } ;
struct TYPE_22__ {int /*<<< orphan*/  viewport_c; int /*<<< orphan*/  viewport; } ;
struct TYPE_23__ {TYPE_11__ scl_data; struct dpp* dpp; struct hubp* hubp; } ;
struct TYPE_40__ {TYPE_8__* tg; } ;
struct pipe_ctx {TYPE_17__* stream; TYPE_12__ plane_res; int /*<<< orphan*/  pipe_dlg_param; int /*<<< orphan*/  rq_regs; int /*<<< orphan*/  ttu_regs; int /*<<< orphan*/  dlg_regs; TYPE_9__ stream_res; struct dc_plane_state* plane_state; } ;
struct hubp {int power_gated; TYPE_20__* funcs; int /*<<< orphan*/  opp_id; } ;
struct dpp {TYPE_4__* funcs; } ;
struct TYPE_31__ {int dppclk_khz; } ;
struct TYPE_33__ {TYPE_1__ clk; } ;
struct TYPE_34__ {TYPE_2__ dcn; } ;
struct dc_state {TYPE_3__ bw; } ;
struct TYPE_29__ {scalar_t__ scaling_change; scalar_t__ bpp_change; scalar_t__ dcc_change; scalar_t__ swizzle_change; scalar_t__ rotation_change; scalar_t__ horizontal_mirror_change; scalar_t__ pixel_format_change; scalar_t__ full_update; scalar_t__ position_change; scalar_t__ per_pixel_alpha_change; } ;
struct TYPE_30__ {TYPE_18__ bits; } ;
struct dc_plane_state {int /*<<< orphan*/  horizontal_mirror; int /*<<< orphan*/  dcc; int /*<<< orphan*/  rotation; int /*<<< orphan*/  tiling_info; int /*<<< orphan*/  format; TYPE_19__ update_flags; union plane_size plane_size; } ;
struct TYPE_26__ {int /*<<< orphan*/  (* update_plane_addr ) (struct dc*,struct pipe_ctx*) ;int /*<<< orphan*/  (* program_output_csc ) (struct dc*,struct pipe_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* set_cursor_attribute ) (struct pipe_ctx*) ;int /*<<< orphan*/  (* set_cursor_position ) (struct pipe_ctx*) ;int /*<<< orphan*/  (* update_mpcc ) (struct dc*,struct pipe_ctx*) ;} ;
struct dc {TYPE_15__ hwss; TYPE_7__* res_pool; } ;
struct TYPE_39__ {int /*<<< orphan*/  inst; } ;
struct TYPE_38__ {TYPE_6__* dccg; } ;
struct TYPE_36__ {int dispclk_khz; int dppclk_khz; } ;
struct TYPE_37__ {TYPE_5__ clks; } ;
struct TYPE_35__ {int /*<<< orphan*/  (* dpp_dppclk_control ) (struct dpp*,int,int) ;} ;
struct TYPE_32__ {int /*<<< orphan*/  (* set_blank ) (struct hubp*,int) ;int /*<<< orphan*/  (* hubp_program_surface_config ) (struct hubp*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,union plane_size*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* mem_program_viewport ) (struct hubp*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* hubp_setup ) (struct hubp*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* hubp_vtg_sel ) (struct hubp*,int /*<<< orphan*/ ) ;} ;
struct TYPE_27__ {int /*<<< orphan*/  matrix; } ;
struct TYPE_24__ {scalar_t__ quad_part; } ;
struct TYPE_25__ {TYPE_13__ address; } ;
struct TYPE_28__ {TYPE_16__ csc_color_matrix; int /*<<< orphan*/  output_color_space; TYPE_14__ cursor_attributes; } ;

/* Variables and functions */
 scalar_t__ is_pipe_tree_visible (struct pipe_ctx*) ; 
 int /*<<< orphan*/  program_gamut_remap (struct pipe_ctx*) ; 
 int /*<<< orphan*/  stub1 (struct dpp*,int,int) ; 
 int /*<<< orphan*/  stub10 (struct dc*,struct pipe_ctx*) ; 
 int /*<<< orphan*/  stub11 (struct hubp*,int) ; 
 int /*<<< orphan*/  stub2 (struct hubp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct hubp*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (struct dc*,struct pipe_ctx*) ; 
 int /*<<< orphan*/  stub5 (struct hubp*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub6 (struct pipe_ctx*) ; 
 int /*<<< orphan*/  stub7 (struct pipe_ctx*) ; 
 int /*<<< orphan*/  stub8 (struct dc*,struct pipe_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub9 (struct hubp*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,union plane_size*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_dpp (struct dpp*,struct dc_plane_state*) ; 
 int /*<<< orphan*/  update_scaler (struct pipe_ctx*) ; 

__attribute__((used)) static void update_dchubp_dpp(
	struct dc *dc,
	struct pipe_ctx *pipe_ctx,
	struct dc_state *context)
{
	struct hubp *hubp = pipe_ctx->plane_res.hubp;
	struct dpp *dpp = pipe_ctx->plane_res.dpp;
	struct dc_plane_state *plane_state = pipe_ctx->plane_state;
	union plane_size size = plane_state->plane_size;

	/* depends on DML calculation, DPP clock value may change dynamically */
	/* If request max dpp clk is lower than current dispclk, no need to
	 * divided by 2
	 */
	if (plane_state->update_flags.bits.full_update) {
		bool should_divided_by_2 = context->bw.dcn.clk.dppclk_khz <=
				dc->res_pool->dccg->clks.dispclk_khz / 2;

		dpp->funcs->dpp_dppclk_control(
				dpp,
				should_divided_by_2,
				true);

		dc->res_pool->dccg->clks.dppclk_khz = should_divided_by_2 ?
						dc->res_pool->dccg->clks.dispclk_khz / 2 :
							dc->res_pool->dccg->clks.dispclk_khz;
	}

	/* TODO: Need input parameter to tell current DCHUB pipe tie to which OTG
	 * VTG is within DCHUBBUB which is commond block share by each pipe HUBP.
	 * VTG is 1:1 mapping with OTG. Each pipe HUBP will select which VTG
	 */
	if (plane_state->update_flags.bits.full_update) {
		hubp->funcs->hubp_vtg_sel(hubp, pipe_ctx->stream_res.tg->inst);

		hubp->funcs->hubp_setup(
			hubp,
			&pipe_ctx->dlg_regs,
			&pipe_ctx->ttu_regs,
			&pipe_ctx->rq_regs,
			&pipe_ctx->pipe_dlg_param);
	}

	size.grph.surface_size = pipe_ctx->plane_res.scl_data.viewport;

	if (plane_state->update_flags.bits.full_update ||
		plane_state->update_flags.bits.bpp_change)
		update_dpp(dpp, plane_state);

	if (plane_state->update_flags.bits.full_update ||
		plane_state->update_flags.bits.per_pixel_alpha_change)
		dc->hwss.update_mpcc(dc, pipe_ctx);

	if (plane_state->update_flags.bits.full_update ||
		plane_state->update_flags.bits.per_pixel_alpha_change ||
		plane_state->update_flags.bits.scaling_change ||
		plane_state->update_flags.bits.position_change) {
		update_scaler(pipe_ctx);
	}

	if (plane_state->update_flags.bits.full_update ||
		plane_state->update_flags.bits.scaling_change ||
		plane_state->update_flags.bits.position_change) {
		hubp->funcs->mem_program_viewport(
			hubp,
			&pipe_ctx->plane_res.scl_data.viewport,
			&pipe_ctx->plane_res.scl_data.viewport_c);
	}

	if (pipe_ctx->stream->cursor_attributes.address.quad_part != 0) {
		dc->hwss.set_cursor_position(pipe_ctx);
		dc->hwss.set_cursor_attribute(pipe_ctx);
	}

	if (plane_state->update_flags.bits.full_update) {
		/*gamut remap*/
		program_gamut_remap(pipe_ctx);

		dc->hwss.program_output_csc(dc,
				pipe_ctx,
				pipe_ctx->stream->output_color_space,
				pipe_ctx->stream->csc_color_matrix.matrix,
				hubp->opp_id);
	}

	if (plane_state->update_flags.bits.full_update ||
		plane_state->update_flags.bits.pixel_format_change ||
		plane_state->update_flags.bits.horizontal_mirror_change ||
		plane_state->update_flags.bits.rotation_change ||
		plane_state->update_flags.bits.swizzle_change ||
		plane_state->update_flags.bits.dcc_change ||
		plane_state->update_flags.bits.bpp_change ||
		plane_state->update_flags.bits.scaling_change) {
		hubp->funcs->hubp_program_surface_config(
			hubp,
			plane_state->format,
			&plane_state->tiling_info,
			&size,
			plane_state->rotation,
			&plane_state->dcc,
			plane_state->horizontal_mirror);
	}

	hubp->power_gated = false;

	dc->hwss.update_plane_addr(dc, pipe_ctx);

	if (is_pipe_tree_visible(pipe_ctx))
		hubp->funcs->set_blank(hubp, false);
}