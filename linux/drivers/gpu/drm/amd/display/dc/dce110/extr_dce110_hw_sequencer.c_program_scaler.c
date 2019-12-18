#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct tg_color {int /*<<< orphan*/  color_g_y; int /*<<< orphan*/  color_r_cr; int /*<<< orphan*/  member_0; } ;
struct TYPE_16__ {int /*<<< orphan*/  depth; } ;
struct TYPE_13__ {TYPE_2__ lb_params; } ;
struct TYPE_22__ {TYPE_10__ scl_data; TYPE_9__* xfm; } ;
struct TYPE_20__ {TYPE_11__* tg; } ;
struct pipe_ctx {TYPE_8__ plane_res; TYPE_6__ stream_res; TYPE_4__* stream; } ;
struct TYPE_15__ {scalar_t__ visual_confirm; } ;
struct dc {TYPE_1__ debug; } ;
struct TYPE_23__ {TYPE_7__* funcs; } ;
struct TYPE_21__ {int /*<<< orphan*/  (* transform_set_scaler ) (TYPE_9__*,TYPE_10__*) ;int /*<<< orphan*/  (* transform_set_pixel_storage_depth ) (TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_19__ {int /*<<< orphan*/  (* set_overscan_blank_color ) (TYPE_11__*,struct tg_color*) ;} ;
struct TYPE_17__ {scalar_t__ pixel_encoding; } ;
struct TYPE_18__ {TYPE_3__ timing; int /*<<< orphan*/  bit_depth_params; int /*<<< orphan*/  output_color_space; } ;
struct TYPE_14__ {TYPE_5__* funcs; } ;

/* Variables and functions */
 scalar_t__ PIXEL_ENCODING_YCBCR420 ; 
 scalar_t__ VISUAL_CONFIRM_SURFACE ; 
 int /*<<< orphan*/  color_space_to_black_color (struct dc const*,int /*<<< orphan*/ ,struct tg_color*) ; 
 int /*<<< orphan*/  get_surface_visual_confirm_color (struct pipe_ctx const*,struct tg_color*) ; 
 int /*<<< orphan*/  stub1 (TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_11__*,struct tg_color*) ; 
 int /*<<< orphan*/  stub3 (TYPE_9__*,TYPE_10__*) ; 

__attribute__((used)) static void program_scaler(const struct dc *dc,
		const struct pipe_ctx *pipe_ctx)
{
	struct tg_color color = {0};

#if defined(CONFIG_DRM_AMD_DC_DCN1_0)
	/* TOFPGA */
	if (pipe_ctx->plane_res.xfm->funcs->transform_set_pixel_storage_depth == NULL)
		return;
#endif

	if (dc->debug.visual_confirm == VISUAL_CONFIRM_SURFACE)
		get_surface_visual_confirm_color(pipe_ctx, &color);
	else
		color_space_to_black_color(dc,
				pipe_ctx->stream->output_color_space,
				&color);

	pipe_ctx->plane_res.xfm->funcs->transform_set_pixel_storage_depth(
		pipe_ctx->plane_res.xfm,
		pipe_ctx->plane_res.scl_data.lb_params.depth,
		&pipe_ctx->stream->bit_depth_params);

	if (pipe_ctx->stream_res.tg->funcs->set_overscan_blank_color) {
		/*
		 * The way 420 is packed, 2 channels carry Y component, 1 channel
		 * alternate between Cb and Cr, so both channels need the pixel
		 * value for Y
		 */
		if (pipe_ctx->stream->timing.pixel_encoding == PIXEL_ENCODING_YCBCR420)
			color.color_r_cr = color.color_g_y;

		pipe_ctx->stream_res.tg->funcs->set_overscan_blank_color(
				pipe_ctx->stream_res.tg,
				&color);
	}

	pipe_ctx->plane_res.xfm->funcs->transform_set_scaler(pipe_ctx->plane_res.xfm,
		&pipe_ctx->plane_res.scl_data);
}