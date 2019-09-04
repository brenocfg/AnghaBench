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
struct rect {scalar_t__ x; int width; scalar_t__ y; int height; } ;
struct TYPE_14__ {int x; int width; scalar_t__ y; int height; } ;
struct TYPE_15__ {TYPE_6__ recout; } ;
struct TYPE_16__ {TYPE_7__ scl_data; } ;
struct pipe_ctx {TYPE_8__ plane_res; struct dc_plane_state* plane_state; TYPE_3__* top_pipe; TYPE_2__* bottom_pipe; struct dc_stream_state* stream; } ;
struct TYPE_12__ {scalar_t__ x; int width; scalar_t__ y; int height; } ;
struct TYPE_13__ {int x; int width; scalar_t__ y; int height; } ;
struct dc_stream_state {scalar_t__ view_format; TYPE_4__ src; TYPE_5__ dst; } ;
struct TYPE_9__ {int x; int width; int y; int height; } ;
struct dc_plane_state {scalar_t__ rotation; int horizontal_mirror; TYPE_1__ dst_rect; struct rect clip_rect; struct rect src_rect; } ;
struct TYPE_11__ {struct dc_plane_state* plane_state; } ;
struct TYPE_10__ {struct dc_plane_state* plane_state; } ;

/* Variables and functions */
 scalar_t__ ROTATION_ANGLE_180 ; 
 scalar_t__ ROTATION_ANGLE_270 ; 
 scalar_t__ ROTATION_ANGLE_90 ; 
 scalar_t__ VIEW_3D_FORMAT_TOP_AND_BOTTOM ; 
 int /*<<< orphan*/  rect_swap_helper (struct rect*) ; 

__attribute__((used)) static void calculate_recout(struct pipe_ctx *pipe_ctx, struct rect *recout_full)
{
	const struct dc_plane_state *plane_state = pipe_ctx->plane_state;
	const struct dc_stream_state *stream = pipe_ctx->stream;
	struct rect surf_src = plane_state->src_rect;
	struct rect surf_clip = plane_state->clip_rect;
	bool pri_split = pipe_ctx->bottom_pipe &&
			pipe_ctx->bottom_pipe->plane_state == pipe_ctx->plane_state;
	bool sec_split = pipe_ctx->top_pipe &&
			pipe_ctx->top_pipe->plane_state == pipe_ctx->plane_state;
	bool top_bottom_split = stream->view_format == VIEW_3D_FORMAT_TOP_AND_BOTTOM;

	if (pipe_ctx->plane_state->rotation == ROTATION_ANGLE_90 ||
			pipe_ctx->plane_state->rotation == ROTATION_ANGLE_270)
		rect_swap_helper(&surf_src);

	pipe_ctx->plane_res.scl_data.recout.x = stream->dst.x;
	if (stream->src.x < surf_clip.x)
		pipe_ctx->plane_res.scl_data.recout.x += (surf_clip.x
			- stream->src.x) * stream->dst.width
						/ stream->src.width;

	pipe_ctx->plane_res.scl_data.recout.width = surf_clip.width *
			stream->dst.width / stream->src.width;
	if (pipe_ctx->plane_res.scl_data.recout.width + pipe_ctx->plane_res.scl_data.recout.x >
			stream->dst.x + stream->dst.width)
		pipe_ctx->plane_res.scl_data.recout.width =
			stream->dst.x + stream->dst.width
						- pipe_ctx->plane_res.scl_data.recout.x;

	pipe_ctx->plane_res.scl_data.recout.y = stream->dst.y;
	if (stream->src.y < surf_clip.y)
		pipe_ctx->plane_res.scl_data.recout.y += (surf_clip.y
			- stream->src.y) * stream->dst.height
						/ stream->src.height;

	pipe_ctx->plane_res.scl_data.recout.height = surf_clip.height *
			stream->dst.height / stream->src.height;
	if (pipe_ctx->plane_res.scl_data.recout.height + pipe_ctx->plane_res.scl_data.recout.y >
			stream->dst.y + stream->dst.height)
		pipe_ctx->plane_res.scl_data.recout.height =
			stream->dst.y + stream->dst.height
						- pipe_ctx->plane_res.scl_data.recout.y;

	/* Handle h & vsplit */
	if (sec_split && top_bottom_split) {
		pipe_ctx->plane_res.scl_data.recout.y +=
				pipe_ctx->plane_res.scl_data.recout.height / 2;
		/* Floor primary pipe, ceil 2ndary pipe */
		pipe_ctx->plane_res.scl_data.recout.height =
				(pipe_ctx->plane_res.scl_data.recout.height + 1) / 2;
	} else if (pri_split && top_bottom_split)
		pipe_ctx->plane_res.scl_data.recout.height /= 2;
	else if (pri_split || sec_split) {
		/* HMirror XOR Secondary_pipe XOR Rotation_180 */
		bool right_view = (sec_split != plane_state->horizontal_mirror) !=
					(plane_state->rotation == ROTATION_ANGLE_180);

		if (plane_state->rotation == ROTATION_ANGLE_90
				|| plane_state->rotation == ROTATION_ANGLE_270)
			/* Secondary_pipe XOR Rotation_270 */
			right_view = (plane_state->rotation == ROTATION_ANGLE_270) != sec_split;

		if (right_view) {
			pipe_ctx->plane_res.scl_data.recout.x +=
					pipe_ctx->plane_res.scl_data.recout.width / 2;
			/* Ceil offset pipe */
			pipe_ctx->plane_res.scl_data.recout.width =
					(pipe_ctx->plane_res.scl_data.recout.width + 1) / 2;
		} else {
			pipe_ctx->plane_res.scl_data.recout.width /= 2;
		}
	}
	/* Unclipped recout offset = stream dst offset + ((surf dst offset - stream surf_src offset)
	 *			* 1/ stream scaling ratio) - (surf surf_src offset * 1/ full scl
	 *			ratio)
	 */
	recout_full->x = stream->dst.x + (plane_state->dst_rect.x - stream->src.x)
					* stream->dst.width / stream->src.width -
			surf_src.x * plane_state->dst_rect.width / surf_src.width
					* stream->dst.width / stream->src.width;
	recout_full->y = stream->dst.y + (plane_state->dst_rect.y - stream->src.y)
					* stream->dst.height / stream->src.height -
			surf_src.y * plane_state->dst_rect.height / surf_src.height
					* stream->dst.height / stream->src.height;

	recout_full->width = plane_state->dst_rect.width
					* stream->dst.width / stream->src.width;
	recout_full->height = plane_state->dst_rect.height
					* stream->dst.height / stream->src.height;
}