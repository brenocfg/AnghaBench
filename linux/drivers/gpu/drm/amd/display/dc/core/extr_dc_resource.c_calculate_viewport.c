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
struct TYPE_11__ {int x; int width; int y; int height; } ;
struct TYPE_10__ {int x; int y; int width; int height; } ;
struct TYPE_9__ {void* v_c; void* h_c; } ;
struct scaler_data {scalar_t__ format; TYPE_3__ viewport; TYPE_2__ viewport_c; TYPE_1__ inits; } ;
struct rect {int x; int width; int y; int height; } ;
struct TYPE_12__ {struct scaler_data scl_data; } ;
struct pipe_ctx {struct dc_plane_state* plane_state; TYPE_6__* top_pipe; TYPE_5__* bottom_pipe; TYPE_4__ plane_res; struct dc_stream_state* stream; } ;
struct TYPE_15__ {scalar_t__ x; scalar_t__ width; scalar_t__ y; scalar_t__ height; } ;
struct dc_stream_state {scalar_t__ view_format; TYPE_7__ src; } ;
struct TYPE_16__ {scalar_t__ x; scalar_t__ width; scalar_t__ y; scalar_t__ height; } ;
struct dc_plane_state {int /*<<< orphan*/  horizontal_mirror; int /*<<< orphan*/  rotation; TYPE_8__ clip_rect; struct rect dst_rect; struct rect src_rect; } ;
struct TYPE_14__ {struct dc_plane_state* plane_state; } ;
struct TYPE_13__ {struct dc_plane_state* plane_state; } ;

/* Variables and functions */
 scalar_t__ PIXEL_FORMAT_420BPP10 ; 
 scalar_t__ PIXEL_FORMAT_420BPP8 ; 
 scalar_t__ VIEW_3D_FORMAT_SIDE_BY_SIDE ; 
 scalar_t__ VIEW_3D_FORMAT_TOP_AND_BOTTOM ; 
 void* dc_fixpt_half ; 
 void* dc_fixpt_zero ; 
 int /*<<< orphan*/  get_vp_scan_direction (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*,int*) ; 
 int /*<<< orphan*/  swap (int,int) ; 

__attribute__((used)) static void calculate_viewport(struct pipe_ctx *pipe_ctx)
{
	const struct dc_plane_state *plane_state = pipe_ctx->plane_state;
	const struct dc_stream_state *stream = pipe_ctx->stream;
	struct scaler_data *data = &pipe_ctx->plane_res.scl_data;
	struct rect surf_src = plane_state->src_rect;
	struct rect clip, dest;
	int vpc_div = (data->format == PIXEL_FORMAT_420BPP8
			|| data->format == PIXEL_FORMAT_420BPP10) ? 2 : 1;
	bool pri_split = pipe_ctx->bottom_pipe &&
			pipe_ctx->bottom_pipe->plane_state == pipe_ctx->plane_state;
	bool sec_split = pipe_ctx->top_pipe &&
			pipe_ctx->top_pipe->plane_state == pipe_ctx->plane_state;
	bool orthogonal_rotation, flip_y_start, flip_x_start;

	if (stream->view_format == VIEW_3D_FORMAT_SIDE_BY_SIDE ||
		stream->view_format == VIEW_3D_FORMAT_TOP_AND_BOTTOM) {
		pri_split = false;
		sec_split = false;
	}

	/* The actual clip is an intersection between stream
	 * source and surface clip
	 */
	dest = plane_state->dst_rect;
	clip.x = stream->src.x > plane_state->clip_rect.x ?
			stream->src.x : plane_state->clip_rect.x;

	clip.width = stream->src.x + stream->src.width <
			plane_state->clip_rect.x + plane_state->clip_rect.width ?
			stream->src.x + stream->src.width - clip.x :
			plane_state->clip_rect.x + plane_state->clip_rect.width - clip.x ;

	clip.y = stream->src.y > plane_state->clip_rect.y ?
			stream->src.y : plane_state->clip_rect.y;

	clip.height = stream->src.y + stream->src.height <
			plane_state->clip_rect.y + plane_state->clip_rect.height ?
			stream->src.y + stream->src.height - clip.y :
			plane_state->clip_rect.y + plane_state->clip_rect.height - clip.y ;

	/*
	 * Need to calculate how scan origin is shifted in vp space
	 * to correctly rotate clip and dst
	 */
	get_vp_scan_direction(
			plane_state->rotation,
			plane_state->horizontal_mirror,
			&orthogonal_rotation,
			&flip_y_start,
			&flip_x_start);

	if (orthogonal_rotation) {
		swap(clip.x, clip.y);
		swap(clip.width, clip.height);
		swap(dest.x, dest.y);
		swap(dest.width, dest.height);
	}
	if (flip_x_start) {
		clip.x = dest.x + dest.width - clip.x - clip.width;
		dest.x = 0;
	}
	if (flip_y_start) {
		clip.y = dest.y + dest.height - clip.y - clip.height;
		dest.y = 0;
	}

	/* offset = surf_src.ofs + (clip.ofs - surface->dst_rect.ofs) * scl_ratio
	 * num_pixels = clip.num_pix * scl_ratio
	 */
	data->viewport.x = surf_src.x + (clip.x - dest.x) * surf_src.width / dest.width;
	data->viewport.width = clip.width * surf_src.width / dest.width;

	data->viewport.y = surf_src.y + (clip.y - dest.y) * surf_src.height / dest.height;
	data->viewport.height = clip.height * surf_src.height / dest.height;

	/* Handle split */
	if (pri_split || sec_split) {
		if (orthogonal_rotation) {
			if (flip_y_start != pri_split)
				data->viewport.height /= 2;
			else {
				data->viewport.y +=  data->viewport.height / 2;
				/* Ceil offset pipe */
				data->viewport.height = (data->viewport.height + 1) / 2;
			}
		} else {
			if (flip_x_start != pri_split)
				data->viewport.width /= 2;
			else {
				data->viewport.x +=  data->viewport.width / 2;
				/* Ceil offset pipe */
				data->viewport.width = (data->viewport.width + 1) / 2;
			}
		}
	}

	/* Round down, compensate in init */
	data->viewport_c.x = data->viewport.x / vpc_div;
	data->viewport_c.y = data->viewport.y / vpc_div;
	data->inits.h_c = (data->viewport.x % vpc_div) != 0 ? dc_fixpt_half : dc_fixpt_zero;
	data->inits.v_c = (data->viewport.y % vpc_div) != 0 ? dc_fixpt_half : dc_fixpt_zero;

	/* Round up, assume original video size always even dimensions */
	data->viewport_c.width = (data->viewport.width + vpc_div - 1) / vpc_div;
	data->viewport_c.height = (data->viewport.height + vpc_div - 1) / vpc_div;
}