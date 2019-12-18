#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_11__ {void* horz; void* horz_c; void* vert; void* vert_c; } ;
struct TYPE_20__ {void* v_c; void* v_c_bot; void* v; void* v_bot; void* h_c; void* h; } ;
struct TYPE_13__ {int /*<<< orphan*/  height; int /*<<< orphan*/  y; int /*<<< orphan*/  width; int /*<<< orphan*/  x; } ;
struct TYPE_19__ {scalar_t__ v_taps_c; scalar_t__ h_taps_c; scalar_t__ v_taps; scalar_t__ h_taps; } ;
struct TYPE_12__ {int /*<<< orphan*/  height; int /*<<< orphan*/  y; int /*<<< orphan*/  width; int /*<<< orphan*/  x; } ;
struct TYPE_15__ {int x; int y; } ;
struct scaler_data {scalar_t__ format; TYPE_10__ ratios; TYPE_9__ inits; TYPE_2__ viewport_c; TYPE_8__ taps; TYPE_1__ viewport; TYPE_4__ recout; } ;
struct rect {int x; int width; int y; int height; } ;
struct TYPE_14__ {struct scaler_data scl_data; } ;
struct pipe_ctx {struct dc_plane_state* plane_state; TYPE_3__ plane_res; struct dc_stream_state* stream; } ;
struct TYPE_18__ {int x; int width; int y; int height; } ;
struct TYPE_17__ {int x; int width; int y; int height; } ;
struct dc_stream_state {TYPE_7__ src; TYPE_6__ dst; } ;
struct TYPE_16__ {int x; int width; int y; int height; } ;
struct dc_plane_state {TYPE_5__ dst_rect; int /*<<< orphan*/  horizontal_mirror; int /*<<< orphan*/  rotation; struct rect src_rect; } ;

/* Variables and functions */
 scalar_t__ PIXEL_FORMAT_420BPP10 ; 
 scalar_t__ PIXEL_FORMAT_420BPP8 ; 
 int /*<<< orphan*/  adjust_vp_and_init_for_seamless_clip (int,int,int,scalar_t__,void*,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* dc_fixpt_add (void*,void*) ; 
 int /*<<< orphan*/  dc_fixpt_add_int (void*,scalar_t__) ; 
 void* dc_fixpt_div_int (int /*<<< orphan*/ ,int) ; 
 void* dc_fixpt_truncate (void*,int) ; 
 int /*<<< orphan*/  get_vp_scan_direction (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*,int*) ; 
 int /*<<< orphan*/  swap (int,int) ; 

__attribute__((used)) static void calculate_inits_and_adj_vp(struct pipe_ctx *pipe_ctx)
{
	const struct dc_plane_state *plane_state = pipe_ctx->plane_state;
	const struct dc_stream_state *stream = pipe_ctx->stream;
	struct scaler_data *data = &pipe_ctx->plane_res.scl_data;
	struct rect src = pipe_ctx->plane_state->src_rect;
	int recout_skip_h, recout_skip_v, surf_size_h, surf_size_v;
	int vpc_div = (data->format == PIXEL_FORMAT_420BPP8
			|| data->format == PIXEL_FORMAT_420BPP10) ? 2 : 1;
	bool orthogonal_rotation, flip_vert_scan_dir, flip_horz_scan_dir;

	/*
	 * Need to calculate the scan direction for viewport to make adjustments
	 */
	get_vp_scan_direction(
			plane_state->rotation,
			plane_state->horizontal_mirror,
			&orthogonal_rotation,
			&flip_vert_scan_dir,
			&flip_horz_scan_dir);

	/* Calculate src rect rotation adjusted to recout space */
	surf_size_h = src.x + src.width;
	surf_size_v = src.y + src.height;
	if (flip_horz_scan_dir)
		src.x = 0;
	if (flip_vert_scan_dir)
		src.y = 0;
	if (orthogonal_rotation) {
		swap(src.x, src.y);
		swap(src.width, src.height);
	}

	/* Recout matching initial vp offset = recout_offset - (stream dst offset +
	 *			((surf dst offset - stream src offset) * 1/ stream scaling ratio)
	 *			- (surf surf_src offset * 1/ full scl ratio))
	 */
	recout_skip_h = data->recout.x - (stream->dst.x + (plane_state->dst_rect.x - stream->src.x)
					* stream->dst.width / stream->src.width -
					src.x * plane_state->dst_rect.width / src.width
					* stream->dst.width / stream->src.width);
	recout_skip_v = data->recout.y - (stream->dst.y + (plane_state->dst_rect.y - stream->src.y)
					* stream->dst.height / stream->src.height -
					src.y * plane_state->dst_rect.height / src.height
					* stream->dst.height / stream->src.height);
	if (orthogonal_rotation)
		swap(recout_skip_h, recout_skip_v);
	/*
	 * Init calculated according to formula:
	 * 	init = (scaling_ratio + number_of_taps + 1) / 2
	 * 	init_bot = init + scaling_ratio
	 * 	init_c = init + truncated_vp_c_offset(from calculate viewport)
	 */
	data->inits.h = dc_fixpt_truncate(dc_fixpt_div_int(
			dc_fixpt_add_int(data->ratios.horz, data->taps.h_taps + 1), 2), 19);

	data->inits.h_c = dc_fixpt_truncate(dc_fixpt_add(data->inits.h_c, dc_fixpt_div_int(
			dc_fixpt_add_int(data->ratios.horz_c, data->taps.h_taps_c + 1), 2)), 19);

	data->inits.v = dc_fixpt_truncate(dc_fixpt_div_int(
			dc_fixpt_add_int(data->ratios.vert, data->taps.v_taps + 1), 2), 19);

	data->inits.v_c = dc_fixpt_truncate(dc_fixpt_add(data->inits.v_c, dc_fixpt_div_int(
			dc_fixpt_add_int(data->ratios.vert_c, data->taps.v_taps_c + 1), 2)), 19);

	/*
	 * Taps, inits and scaling ratios are in recout space need to rotate
	 * to viewport rotation before adjustment
	 */
	adjust_vp_and_init_for_seamless_clip(
			flip_horz_scan_dir,
			recout_skip_h,
			surf_size_h,
			orthogonal_rotation ? data->taps.v_taps : data->taps.h_taps,
			orthogonal_rotation ? data->ratios.vert : data->ratios.horz,
			orthogonal_rotation ? &data->inits.v : &data->inits.h,
			&data->viewport.x,
			&data->viewport.width);
	adjust_vp_and_init_for_seamless_clip(
			flip_horz_scan_dir,
			recout_skip_h,
			surf_size_h / vpc_div,
			orthogonal_rotation ? data->taps.v_taps_c : data->taps.h_taps_c,
			orthogonal_rotation ? data->ratios.vert_c : data->ratios.horz_c,
			orthogonal_rotation ? &data->inits.v_c : &data->inits.h_c,
			&data->viewport_c.x,
			&data->viewport_c.width);
	adjust_vp_and_init_for_seamless_clip(
			flip_vert_scan_dir,
			recout_skip_v,
			surf_size_v,
			orthogonal_rotation ? data->taps.h_taps : data->taps.v_taps,
			orthogonal_rotation ? data->ratios.horz : data->ratios.vert,
			orthogonal_rotation ? &data->inits.h : &data->inits.v,
			&data->viewport.y,
			&data->viewport.height);
	adjust_vp_and_init_for_seamless_clip(
			flip_vert_scan_dir,
			recout_skip_v,
			surf_size_v / vpc_div,
			orthogonal_rotation ? data->taps.h_taps_c : data->taps.v_taps_c,
			orthogonal_rotation ? data->ratios.horz_c : data->ratios.vert_c,
			orthogonal_rotation ? &data->inits.h_c : &data->inits.v_c,
			&data->viewport_c.y,
			&data->viewport_c.height);

	/* Interlaced inits based on final vert inits */
	data->inits.v_bot = dc_fixpt_add(data->inits.v, data->ratios.vert);
	data->inits.v_c_bot = dc_fixpt_add(data->inits.v_c, data->ratios.vert_c);

}