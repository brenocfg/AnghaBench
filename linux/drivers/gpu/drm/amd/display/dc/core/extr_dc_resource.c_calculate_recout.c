#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct rect {scalar_t__ x; int width; scalar_t__ y; int height; } ;
struct TYPE_13__ {scalar_t__ x; int width; scalar_t__ y; int height; } ;
struct TYPE_14__ {TYPE_6__ recout; } ;
struct TYPE_12__ {TYPE_7__ scl_data; } ;
struct pipe_ctx {TYPE_5__ plane_res; struct dc_plane_state* plane_state; TYPE_2__* top_pipe; TYPE_1__* bottom_pipe; struct dc_stream_state* stream; } ;
struct TYPE_11__ {scalar_t__ x; int width; scalar_t__ y; int height; } ;
struct TYPE_10__ {scalar_t__ x; int width; scalar_t__ y; int height; } ;
struct dc_stream_state {scalar_t__ view_format; TYPE_4__ dst; TYPE_3__ src; } ;
struct dc_plane_state {struct rect clip_rect; } ;
struct TYPE_9__ {struct dc_plane_state* plane_state; } ;
struct TYPE_8__ {struct dc_plane_state* plane_state; } ;

/* Variables and functions */
 scalar_t__ VIEW_3D_FORMAT_TOP_AND_BOTTOM ; 

__attribute__((used)) static void calculate_recout(struct pipe_ctx *pipe_ctx)
{
	const struct dc_plane_state *plane_state = pipe_ctx->plane_state;
	const struct dc_stream_state *stream = pipe_ctx->stream;
	struct rect surf_clip = plane_state->clip_rect;
	bool pri_split = pipe_ctx->bottom_pipe &&
			pipe_ctx->bottom_pipe->plane_state == pipe_ctx->plane_state;
	bool sec_split = pipe_ctx->top_pipe &&
			pipe_ctx->top_pipe->plane_state == pipe_ctx->plane_state;
	bool top_bottom_split = stream->view_format == VIEW_3D_FORMAT_TOP_AND_BOTTOM;

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

	/* Handle h & v split, handle rotation using viewport */
	if (sec_split && top_bottom_split) {
		pipe_ctx->plane_res.scl_data.recout.y +=
				pipe_ctx->plane_res.scl_data.recout.height / 2;
		/* Floor primary pipe, ceil 2ndary pipe */
		pipe_ctx->plane_res.scl_data.recout.height =
				(pipe_ctx->plane_res.scl_data.recout.height + 1) / 2;
	} else if (pri_split && top_bottom_split)
		pipe_ctx->plane_res.scl_data.recout.height /= 2;
	else if (sec_split) {
		pipe_ctx->plane_res.scl_data.recout.x +=
				pipe_ctx->plane_res.scl_data.recout.width / 2;
		/* Ceil offset pipe */
		pipe_ctx->plane_res.scl_data.recout.width =
				(pipe_ctx->plane_res.scl_data.recout.width + 1) / 2;
	} else if (pri_split)
		pipe_ctx->plane_res.scl_data.recout.width /= 2;
}