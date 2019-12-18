#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  depth; } ;
struct TYPE_13__ {TYPE_4__ lb_params; int /*<<< orphan*/  format; } ;
struct TYPE_15__ {TYPE_8__* xfm; TYPE_5__ scl_data; } ;
struct pipe_ctx {TYPE_7__ plane_res; TYPE_3__* stream; TYPE_1__* plane_state; } ;
struct default_adjustment {int force_hw_default; int /*<<< orphan*/  lb_color_depth; int /*<<< orphan*/  color_depth; int /*<<< orphan*/  surface_pixel_format; int /*<<< orphan*/  csc_adjust_type; int /*<<< orphan*/  out_color_space; int /*<<< orphan*/  in_color_space; int /*<<< orphan*/  member_0; } ;
struct TYPE_16__ {TYPE_6__* funcs; } ;
struct TYPE_14__ {int /*<<< orphan*/  (* opp_set_csc_default ) (TYPE_8__*,struct default_adjustment*) ;} ;
struct TYPE_10__ {int /*<<< orphan*/  display_color_depth; } ;
struct TYPE_11__ {TYPE_2__ timing; int /*<<< orphan*/  output_color_space; } ;
struct TYPE_9__ {int /*<<< orphan*/  color_space; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRAPHICS_CSC_ADJUST_TYPE_SW ; 
 int /*<<< orphan*/  stub1 (TYPE_8__*,struct default_adjustment*) ; 

__attribute__((used)) static void set_default_colors(struct pipe_ctx *pipe_ctx)
{
	struct default_adjustment default_adjust = { 0 };

	default_adjust.force_hw_default = false;
	default_adjust.in_color_space = pipe_ctx->plane_state->color_space;
	default_adjust.out_color_space = pipe_ctx->stream->output_color_space;
	default_adjust.csc_adjust_type = GRAPHICS_CSC_ADJUST_TYPE_SW;
	default_adjust.surface_pixel_format = pipe_ctx->plane_res.scl_data.format;

	/* display color depth */
	default_adjust.color_depth =
		pipe_ctx->stream->timing.display_color_depth;

	/* Lb color depth */
	default_adjust.lb_color_depth = pipe_ctx->plane_res.scl_data.lb_params.depth;

	pipe_ctx->plane_res.xfm->funcs->opp_set_csc_default(
					pipe_ctx->plane_res.xfm, &default_adjust);
}