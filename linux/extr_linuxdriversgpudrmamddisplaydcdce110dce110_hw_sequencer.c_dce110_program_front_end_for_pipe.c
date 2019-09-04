#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_58__   TYPE_9__ ;
typedef  struct TYPE_57__   TYPE_8__ ;
typedef  struct TYPE_56__   TYPE_7__ ;
typedef  struct TYPE_55__   TYPE_6__ ;
typedef  struct TYPE_54__   TYPE_5__ ;
typedef  struct TYPE_53__   TYPE_4__ ;
typedef  struct TYPE_52__   TYPE_3__ ;
typedef  struct TYPE_51__   TYPE_30__ ;
typedef  struct TYPE_50__   TYPE_2__ ;
typedef  struct TYPE_49__   TYPE_28__ ;
typedef  struct TYPE_48__   TYPE_27__ ;
typedef  struct TYPE_47__   TYPE_25__ ;
typedef  struct TYPE_46__   TYPE_24__ ;
typedef  struct TYPE_45__   TYPE_23__ ;
typedef  struct TYPE_44__   TYPE_22__ ;
typedef  struct TYPE_43__   TYPE_21__ ;
typedef  struct TYPE_42__   TYPE_20__ ;
typedef  struct TYPE_41__   TYPE_1__ ;
typedef  struct TYPE_40__   TYPE_19__ ;
typedef  struct TYPE_39__   TYPE_18__ ;
typedef  struct TYPE_38__   TYPE_17__ ;
typedef  struct TYPE_37__   TYPE_16__ ;
typedef  struct TYPE_36__   TYPE_15__ ;
typedef  struct TYPE_35__   TYPE_14__ ;
typedef  struct TYPE_34__   TYPE_13__ ;
typedef  struct TYPE_33__   TYPE_12__ ;
typedef  struct TYPE_32__   TYPE_11__ ;
typedef  struct TYPE_31__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tbl_entry ;
struct xfm_grph_csc_adjustment {int /*<<< orphan*/ * temperature_matrix; int /*<<< orphan*/  gamut_adjust_type; int /*<<< orphan*/ * regval; int /*<<< orphan*/  color_space; } ;
struct TYPE_33__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_32__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_39__ {int alpha_en; } ;
struct TYPE_40__ {TYPE_12__ recout; TYPE_11__ viewport; TYPE_18__ lb_params; } ;
struct TYPE_42__ {TYPE_19__ scl_data; struct mem_input* mi; TYPE_28__* xfm; } ;
struct pipe_ctx {size_t pipe_idx; scalar_t__ bottom_pipe; TYPE_20__ plane_res; struct dc_plane_state* plane_state; TYPE_24__* stream; } ;
struct out_csc_color_matrix {int /*<<< orphan*/ * temperature_matrix; int /*<<< orphan*/  gamut_adjust_type; int /*<<< orphan*/ * regval; int /*<<< orphan*/  color_space; } ;
struct mem_input {TYPE_23__* funcs; int /*<<< orphan*/  inst; } ;
struct TYPE_31__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_58__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_57__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_54__ {int /*<<< orphan*/  low_part; int /*<<< orphan*/  high_part; } ;
struct TYPE_55__ {TYPE_5__ addr; } ;
struct TYPE_56__ {TYPE_6__ grph; } ;
struct TYPE_50__ {scalar_t__ full_update; scalar_t__ gamma_change; scalar_t__ in_transfer_func_change; } ;
struct TYPE_52__ {TYPE_2__ bits; } ;
struct TYPE_43__ {scalar_t__ array_mode; } ;
struct TYPE_47__ {TYPE_21__ gfx8; } ;
struct dc_plane_state {TYPE_10__ clip_rect; TYPE_9__ dst_rect; TYPE_8__ src_rect; TYPE_7__ address; TYPE_3__ update_flags; int /*<<< orphan*/  rotation; TYPE_25__ tiling_info; int /*<<< orphan*/  format; int /*<<< orphan*/  visible; int /*<<< orphan*/  plane_size; } ;
struct TYPE_53__ {int /*<<< orphan*/  (* set_output_transfer_func ) (struct pipe_ctx*,TYPE_24__*) ;int /*<<< orphan*/  (* set_input_transfer_func ) (struct pipe_ctx*,struct dc_plane_state*) ;} ;
struct TYPE_41__ {scalar_t__ gpu_vm_support; } ;
struct dc {TYPE_4__ hwss; TYPE_1__ config; TYPE_30__* current_state; TYPE_27__* fbc_compressor; int /*<<< orphan*/  hwseq; TYPE_13__* res_pool; } ;
typedef  int /*<<< orphan*/  adjust ;
struct TYPE_35__ {struct pipe_ctx* pipe_ctx; } ;
struct TYPE_51__ {TYPE_14__ res_ctx; } ;
struct TYPE_49__ {TYPE_17__* funcs; } ;
struct TYPE_48__ {TYPE_22__* funcs; } ;
struct TYPE_37__ {int enable_remap; int /*<<< orphan*/ * matrix; } ;
struct TYPE_36__ {int enable_adjustment; int /*<<< orphan*/ * matrix; } ;
struct TYPE_46__ {TYPE_16__ gamut_remap_matrix; TYPE_15__ csc_color_matrix; int /*<<< orphan*/  output_color_space; } ;
struct TYPE_45__ {int /*<<< orphan*/  (* mem_input_program_pte_vm ) (struct mem_input*,int /*<<< orphan*/ ,TYPE_25__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* set_blank ) (struct mem_input*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* mem_input_program_surface_config ) (struct mem_input*,int /*<<< orphan*/ ,TYPE_25__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ;} ;
struct TYPE_44__ {int /*<<< orphan*/  (* disable_fbc ) (TYPE_27__*) ;} ;
struct TYPE_38__ {int /*<<< orphan*/  (* transform_set_gamut_remap ) (TYPE_28__*,struct xfm_grph_csc_adjustment*) ;int /*<<< orphan*/  (* opp_set_csc_adjustment ) (TYPE_28__*,struct xfm_grph_csc_adjustment*) ;} ;
struct TYPE_34__ {unsigned int underlay_pipe_index; } ;

/* Variables and functions */
 unsigned int CSC_TEMPERATURE_MATRIX_SIZE ; 
 scalar_t__ DC_ARRAY_LINEAR_GENERAL ; 
 int /*<<< orphan*/  DC_LOGGER_INIT () ; 
 int /*<<< orphan*/  DC_LOG_SURFACE (char*,unsigned int,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  GRAPHICS_GAMUT_ADJUST_TYPE_BYPASS ; 
 int /*<<< orphan*/  GRAPHICS_GAMUT_ADJUST_TYPE_SW ; 
 int /*<<< orphan*/  dce_enable_fe_clock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  enable_fbc (struct dc*,TYPE_30__*) ; 
 int /*<<< orphan*/  memset (struct xfm_grph_csc_adjustment*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  program_scaler (struct dc*,struct pipe_ctx*) ; 
 int /*<<< orphan*/  set_default_colors (struct pipe_ctx*) ; 
 int /*<<< orphan*/  stub1 (TYPE_28__*,struct xfm_grph_csc_adjustment*) ; 
 int /*<<< orphan*/  stub2 (TYPE_28__*,struct xfm_grph_csc_adjustment*) ; 
 int /*<<< orphan*/  stub3 (TYPE_27__*) ; 
 int /*<<< orphan*/  stub4 (struct mem_input*,int /*<<< orphan*/ ,TYPE_25__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub5 (struct mem_input*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (struct mem_input*,int /*<<< orphan*/ ,TYPE_25__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (struct pipe_ctx*,struct dc_plane_state*) ; 
 int /*<<< orphan*/  stub8 (struct pipe_ctx*,TYPE_24__*) ; 

__attribute__((used)) static void dce110_program_front_end_for_pipe(
		struct dc *dc, struct pipe_ctx *pipe_ctx)
{
	struct mem_input *mi = pipe_ctx->plane_res.mi;
	struct pipe_ctx *old_pipe = NULL;
	struct dc_plane_state *plane_state = pipe_ctx->plane_state;
	struct xfm_grph_csc_adjustment adjust;
	struct out_csc_color_matrix tbl_entry;
	unsigned int underlay_idx = dc->res_pool->underlay_pipe_index;
	unsigned int i;
	DC_LOGGER_INIT();
	memset(&tbl_entry, 0, sizeof(tbl_entry));

	if (dc->current_state)
		old_pipe = &dc->current_state->res_ctx.pipe_ctx[pipe_ctx->pipe_idx];

	memset(&adjust, 0, sizeof(adjust));
	adjust.gamut_adjust_type = GRAPHICS_GAMUT_ADJUST_TYPE_BYPASS;

	dce_enable_fe_clock(dc->hwseq, mi->inst, true);

	set_default_colors(pipe_ctx);
	if (pipe_ctx->stream->csc_color_matrix.enable_adjustment
			== true) {
		tbl_entry.color_space =
			pipe_ctx->stream->output_color_space;

		for (i = 0; i < 12; i++)
			tbl_entry.regval[i] =
			pipe_ctx->stream->csc_color_matrix.matrix[i];

		pipe_ctx->plane_res.xfm->funcs->opp_set_csc_adjustment
				(pipe_ctx->plane_res.xfm, &tbl_entry);
	}

	if (pipe_ctx->stream->gamut_remap_matrix.enable_remap == true) {
		adjust.gamut_adjust_type = GRAPHICS_GAMUT_ADJUST_TYPE_SW;

		for (i = 0; i < CSC_TEMPERATURE_MATRIX_SIZE; i++)
			adjust.temperature_matrix[i] =
				pipe_ctx->stream->gamut_remap_matrix.matrix[i];
	}

	pipe_ctx->plane_res.xfm->funcs->transform_set_gamut_remap(pipe_ctx->plane_res.xfm, &adjust);

	pipe_ctx->plane_res.scl_data.lb_params.alpha_en = pipe_ctx->bottom_pipe != 0;

	program_scaler(dc, pipe_ctx);

	/* fbc not applicable on Underlay pipe */
	if (dc->fbc_compressor && old_pipe->stream &&
	    pipe_ctx->pipe_idx != underlay_idx) {
		if (plane_state->tiling_info.gfx8.array_mode == DC_ARRAY_LINEAR_GENERAL)
			dc->fbc_compressor->funcs->disable_fbc(dc->fbc_compressor);
		else
			enable_fbc(dc, dc->current_state);
	}

	mi->funcs->mem_input_program_surface_config(
			mi,
			plane_state->format,
			&plane_state->tiling_info,
			&plane_state->plane_size,
			plane_state->rotation,
			NULL,
			false);
	if (mi->funcs->set_blank)
		mi->funcs->set_blank(mi, pipe_ctx->plane_state->visible);

	if (dc->config.gpu_vm_support)
		mi->funcs->mem_input_program_pte_vm(
				pipe_ctx->plane_res.mi,
				plane_state->format,
				&plane_state->tiling_info,
				plane_state->rotation);

	/* Moved programming gamma from dc to hwss */
	if (pipe_ctx->plane_state->update_flags.bits.full_update ||
			pipe_ctx->plane_state->update_flags.bits.in_transfer_func_change ||
			pipe_ctx->plane_state->update_flags.bits.gamma_change)
		dc->hwss.set_input_transfer_func(pipe_ctx, pipe_ctx->plane_state);

	if (pipe_ctx->plane_state->update_flags.bits.full_update)
		dc->hwss.set_output_transfer_func(pipe_ctx, pipe_ctx->stream);

	DC_LOG_SURFACE(
			"Pipe:%d %p: addr hi:0x%x, "
			"addr low:0x%x, "
			"src: %d, %d, %d,"
			" %d; dst: %d, %d, %d, %d;"
			"clip: %d, %d, %d, %d\n",
			pipe_ctx->pipe_idx,
			(void *) pipe_ctx->plane_state,
			pipe_ctx->plane_state->address.grph.addr.high_part,
			pipe_ctx->plane_state->address.grph.addr.low_part,
			pipe_ctx->plane_state->src_rect.x,
			pipe_ctx->plane_state->src_rect.y,
			pipe_ctx->plane_state->src_rect.width,
			pipe_ctx->plane_state->src_rect.height,
			pipe_ctx->plane_state->dst_rect.x,
			pipe_ctx->plane_state->dst_rect.y,
			pipe_ctx->plane_state->dst_rect.width,
			pipe_ctx->plane_state->dst_rect.height,
			pipe_ctx->plane_state->clip_rect.x,
			pipe_ctx->plane_state->clip_rect.y,
			pipe_ctx->plane_state->clip_rect.width,
			pipe_ctx->plane_state->clip_rect.height);

	DC_LOG_SURFACE(
			"Pipe %d: width, height, x, y\n"
			"viewport:%d, %d, %d, %d\n"
			"recout:  %d, %d, %d, %d\n",
			pipe_ctx->pipe_idx,
			pipe_ctx->plane_res.scl_data.viewport.width,
			pipe_ctx->plane_res.scl_data.viewport.height,
			pipe_ctx->plane_res.scl_data.viewport.x,
			pipe_ctx->plane_res.scl_data.viewport.y,
			pipe_ctx->plane_res.scl_data.recout.width,
			pipe_ctx->plane_res.scl_data.recout.height,
			pipe_ctx->plane_res.scl_data.recout.x,
			pipe_ctx->plane_res.scl_data.recout.y);
}