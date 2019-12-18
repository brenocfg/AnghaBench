#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_9__ ;
typedef  struct TYPE_33__   TYPE_8__ ;
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_17__ ;
typedef  struct TYPE_24__   TYPE_16__ ;
typedef  struct TYPE_23__   TYPE_15__ ;
typedef  struct TYPE_22__   TYPE_14__ ;
typedef  struct TYPE_21__   TYPE_13__ ;
typedef  struct TYPE_20__   TYPE_12__ ;
typedef  struct TYPE_19__   TYPE_11__ ;
typedef  struct TYPE_18__   TYPE_10__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_24__ {int width; int x; int height; } ;
struct TYPE_34__ {int /*<<< orphan*/  vert; int /*<<< orphan*/  horz; } ;
struct TYPE_23__ {TYPE_16__ viewport; TYPE_9__ ratios; } ;
struct TYPE_25__ {TYPE_15__ scl_data; struct dpp* dpp; struct hubp* hubp; } ;
struct pipe_ctx {TYPE_17__ plane_res; TYPE_14__* plane_state; TYPE_8__* stream; } ;
struct TYPE_20__ {int /*<<< orphan*/  height; scalar_t__ width; } ;
struct hubp {TYPE_12__ curs_attr; TYPE_1__* funcs; } ;
struct dpp {TYPE_2__* funcs; } ;
struct dc_cursor_position {int x; int y; int enable; int /*<<< orphan*/  y_hotspot; int /*<<< orphan*/  x_hotspot; } ;
struct dc_cursor_mi_param {int pixel_clk_khz; scalar_t__ rotation; int /*<<< orphan*/  mirror; int /*<<< orphan*/  v_scale_ratio; int /*<<< orphan*/  h_scale_ratio; TYPE_16__ viewport; int /*<<< orphan*/  ref_clk_khz; } ;
struct TYPE_28__ {int pix_clk_100hz; } ;
struct TYPE_33__ {TYPE_7__* ctx; TYPE_3__ timing; struct dc_cursor_position cursor_position; } ;
struct TYPE_32__ {TYPE_6__* dc; } ;
struct TYPE_31__ {TYPE_5__* res_pool; } ;
struct TYPE_29__ {int /*<<< orphan*/  dchub_ref_clock_inKhz; } ;
struct TYPE_30__ {TYPE_4__ ref_clocks; } ;
struct TYPE_27__ {int /*<<< orphan*/  (* set_cursor_position ) (struct dpp*,struct dc_cursor_position*,struct dc_cursor_mi_param*,scalar_t__,int /*<<< orphan*/ ) ;} ;
struct TYPE_26__ {int /*<<< orphan*/  (* set_cursor_position ) (struct hubp*,struct dc_cursor_position*,struct dc_cursor_mi_param*) ;} ;
struct TYPE_21__ {scalar_t__ x; } ;
struct TYPE_19__ {scalar_t__ type; } ;
struct TYPE_18__ {int x; int y; } ;
struct TYPE_22__ {scalar_t__ rotation; TYPE_13__ src_rect; TYPE_11__ address; TYPE_10__ dst_rect; int /*<<< orphan*/  horizontal_mirror; } ;

/* Variables and functions */
 scalar_t__ PLN_ADDR_TYPE_VIDEO_PROGRESSIVE ; 
 scalar_t__ ROTATION_ANGLE_180 ; 
 scalar_t__ ROTATION_ANGLE_270 ; 
 scalar_t__ ROTATION_ANGLE_90 ; 
 int min (int,int) ; 
 int /*<<< orphan*/  stub1 (struct hubp*,struct dc_cursor_position*,struct dc_cursor_mi_param*) ; 
 int /*<<< orphan*/  stub2 (struct dpp*,struct dc_cursor_position*,struct dc_cursor_mi_param*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dcn10_set_cursor_position(struct pipe_ctx *pipe_ctx)
{
	struct dc_cursor_position pos_cpy = pipe_ctx->stream->cursor_position;
	struct hubp *hubp = pipe_ctx->plane_res.hubp;
	struct dpp *dpp = pipe_ctx->plane_res.dpp;
	struct dc_cursor_mi_param param = {
		.pixel_clk_khz = pipe_ctx->stream->timing.pix_clk_100hz / 10,
		.ref_clk_khz = pipe_ctx->stream->ctx->dc->res_pool->ref_clocks.dchub_ref_clock_inKhz,
		.viewport = pipe_ctx->plane_res.scl_data.viewport,
		.h_scale_ratio = pipe_ctx->plane_res.scl_data.ratios.horz,
		.v_scale_ratio = pipe_ctx->plane_res.scl_data.ratios.vert,
		.rotation = pipe_ctx->plane_state->rotation,
		.mirror = pipe_ctx->plane_state->horizontal_mirror
	};
	uint32_t x_plane = pipe_ctx->plane_state->dst_rect.x;
	uint32_t y_plane = pipe_ctx->plane_state->dst_rect.y;
	uint32_t x_offset = min(x_plane, pos_cpy.x);
	uint32_t y_offset = min(y_plane, pos_cpy.y);

	pos_cpy.x -= x_offset;
	pos_cpy.y -= y_offset;
	pos_cpy.x_hotspot += (x_plane - x_offset);
	pos_cpy.y_hotspot += (y_plane - y_offset);

	if (pipe_ctx->plane_state->address.type
			== PLN_ADDR_TYPE_VIDEO_PROGRESSIVE)
		pos_cpy.enable = false;

	// Swap axis and mirror horizontally
	if (param.rotation == ROTATION_ANGLE_90) {
		uint32_t temp_x = pos_cpy.x;
		pos_cpy.x = pipe_ctx->plane_res.scl_data.viewport.width -
				(pos_cpy.y - pipe_ctx->plane_res.scl_data.viewport.x) + pipe_ctx->plane_res.scl_data.viewport.x;
		pos_cpy.y = temp_x;
	}
	// Swap axis and mirror vertically
	else if (param.rotation == ROTATION_ANGLE_270) {
		uint32_t temp_y = pos_cpy.y;
		if (pos_cpy.x >  pipe_ctx->plane_res.scl_data.viewport.height) {
			pos_cpy.x = pos_cpy.x - pipe_ctx->plane_res.scl_data.viewport.height;
			pos_cpy.y = pipe_ctx->plane_res.scl_data.viewport.height - pos_cpy.x;
		} else {
			pos_cpy.y = 2 * pipe_ctx->plane_res.scl_data.viewport.height - pos_cpy.x;
		}
		pos_cpy.x = temp_y;
	}
	// Mirror horizontally and vertically
	else if (param.rotation == ROTATION_ANGLE_180) {
		if (pos_cpy.x >= pipe_ctx->plane_res.scl_data.viewport.width + pipe_ctx->plane_res.scl_data.viewport.x) {
			pos_cpy.x = 2 * pipe_ctx->plane_res.scl_data.viewport.width
					- pos_cpy.x + 2 * pipe_ctx->plane_res.scl_data.viewport.x;
		} else {
			uint32_t temp_x = pos_cpy.x;
			pos_cpy.x = 2 * pipe_ctx->plane_res.scl_data.viewport.x - pos_cpy.x;
			if (temp_x >= pipe_ctx->plane_res.scl_data.viewport.x + (int)hubp->curs_attr.width
					|| pos_cpy.x <= (int)hubp->curs_attr.width + pipe_ctx->plane_state->src_rect.x) {
				pos_cpy.x = temp_x + pipe_ctx->plane_res.scl_data.viewport.width;
			}
		}
		pos_cpy.y = pipe_ctx->plane_res.scl_data.viewport.height - pos_cpy.y;
	}

	hubp->funcs->set_cursor_position(hubp, &pos_cpy, &param);
	dpp->funcs->set_cursor_position(dpp, &pos_cpy, &param, hubp->curs_attr.width, hubp->curs_attr.height);
}