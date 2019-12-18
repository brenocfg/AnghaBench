#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_14__ ;
typedef  struct TYPE_18__   TYPE_13__ ;
typedef  struct TYPE_17__   TYPE_12__ ;
typedef  struct TYPE_16__   TYPE_11__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
struct TYPE_26__ {int /*<<< orphan*/  vert; int /*<<< orphan*/  horz; } ;
struct TYPE_27__ {TYPE_7__ ratios; int /*<<< orphan*/  viewport; } ;
struct TYPE_28__ {TYPE_8__ scl_data; struct mem_input* mi; struct input_pixel_processor* ipp; } ;
struct pipe_ctx {TYPE_12__* top_pipe; TYPE_11__* plane_state; TYPE_9__ plane_res; TYPE_6__* stream; } ;
struct mem_input {TYPE_14__* funcs; } ;
struct input_pixel_processor {TYPE_13__* funcs; } ;
struct dc_cursor_position {int enable; } ;
struct dc_cursor_mi_param {int pixel_clk_khz; int /*<<< orphan*/  mirror; int /*<<< orphan*/  rotation; int /*<<< orphan*/  v_scale_ratio; int /*<<< orphan*/  h_scale_ratio; int /*<<< orphan*/  viewport; int /*<<< orphan*/  ref_clk_khz; } ;
struct TYPE_20__ {int pix_clk_100hz; } ;
struct TYPE_25__ {TYPE_5__* ctx; TYPE_1__ timing; struct dc_cursor_position cursor_position; } ;
struct TYPE_24__ {TYPE_4__* dc; } ;
struct TYPE_23__ {TYPE_3__* res_pool; } ;
struct TYPE_21__ {int /*<<< orphan*/  xtalin_clock_inKhz; } ;
struct TYPE_22__ {TYPE_2__ ref_clocks; } ;
struct TYPE_19__ {int /*<<< orphan*/  (* set_cursor_position ) (struct mem_input*,struct dc_cursor_position*,struct dc_cursor_mi_param*) ;} ;
struct TYPE_18__ {int /*<<< orphan*/  (* ipp_cursor_set_position ) (struct input_pixel_processor*,struct dc_cursor_position*,struct dc_cursor_mi_param*) ;} ;
struct TYPE_17__ {TYPE_11__* plane_state; } ;
struct TYPE_15__ {scalar_t__ type; } ;
struct TYPE_16__ {TYPE_10__ address; int /*<<< orphan*/  horizontal_mirror; int /*<<< orphan*/  rotation; } ;

/* Variables and functions */
 scalar_t__ PLN_ADDR_TYPE_VIDEO_PROGRESSIVE ; 
 int /*<<< orphan*/  stub1 (struct input_pixel_processor*,struct dc_cursor_position*,struct dc_cursor_mi_param*) ; 
 int /*<<< orphan*/  stub2 (struct mem_input*,struct dc_cursor_position*,struct dc_cursor_mi_param*) ; 

void dce110_set_cursor_position(struct pipe_ctx *pipe_ctx)
{
	struct dc_cursor_position pos_cpy = pipe_ctx->stream->cursor_position;
	struct input_pixel_processor *ipp = pipe_ctx->plane_res.ipp;
	struct mem_input *mi = pipe_ctx->plane_res.mi;
	struct dc_cursor_mi_param param = {
		.pixel_clk_khz = pipe_ctx->stream->timing.pix_clk_100hz / 10,
		.ref_clk_khz = pipe_ctx->stream->ctx->dc->res_pool->ref_clocks.xtalin_clock_inKhz,
		.viewport = pipe_ctx->plane_res.scl_data.viewport,
		.h_scale_ratio = pipe_ctx->plane_res.scl_data.ratios.horz,
		.v_scale_ratio = pipe_ctx->plane_res.scl_data.ratios.vert,
		.rotation = pipe_ctx->plane_state->rotation,
		.mirror = pipe_ctx->plane_state->horizontal_mirror
	};

	if (pipe_ctx->plane_state->address.type
			== PLN_ADDR_TYPE_VIDEO_PROGRESSIVE)
		pos_cpy.enable = false;

	if (pipe_ctx->top_pipe && pipe_ctx->plane_state != pipe_ctx->top_pipe->plane_state)
		pos_cpy.enable = false;

	if (ipp->funcs->ipp_cursor_set_position)
		ipp->funcs->ipp_cursor_set_position(ipp, &pos_cpy, &param);
	if (mi->funcs->set_cursor_position)
		mi->funcs->set_cursor_position(mi, &pos_cpy, &param);
}