#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_46__   TYPE_9__ ;
typedef  struct TYPE_45__   TYPE_8__ ;
typedef  struct TYPE_44__   TYPE_7__ ;
typedef  struct TYPE_43__   TYPE_6__ ;
typedef  struct TYPE_42__   TYPE_5__ ;
typedef  struct TYPE_41__   TYPE_4__ ;
typedef  struct TYPE_40__   TYPE_3__ ;
typedef  struct TYPE_39__   TYPE_2__ ;
typedef  struct TYPE_38__   TYPE_23__ ;
typedef  struct TYPE_37__   TYPE_22__ ;
typedef  struct TYPE_36__   TYPE_21__ ;
typedef  struct TYPE_35__   TYPE_20__ ;
typedef  struct TYPE_34__   TYPE_1__ ;
typedef  struct TYPE_33__   TYPE_19__ ;
typedef  struct TYPE_32__   TYPE_18__ ;
typedef  struct TYPE_31__   TYPE_17__ ;
typedef  struct TYPE_30__   TYPE_16__ ;
typedef  struct TYPE_29__   TYPE_15__ ;
typedef  struct TYPE_28__   TYPE_14__ ;
typedef  struct TYPE_27__   TYPE_13__ ;
typedef  struct TYPE_26__   TYPE_12__ ;
typedef  struct TYPE_25__   TYPE_11__ ;
typedef  struct TYPE_24__   TYPE_10__ ;

/* Type definitions */
struct TYPE_29__ {int /*<<< orphan*/  value; } ;
struct TYPE_28__ {int /*<<< orphan*/  value; } ;
struct TYPE_30__ {TYPE_15__ vert; TYPE_14__ horz; } ;
struct TYPE_27__ {int h_taps; int v_taps; } ;
struct TYPE_26__ {int width; int height; } ;
struct TYPE_31__ {TYPE_16__ ratios; TYPE_13__ taps; TYPE_12__ viewport; } ;
struct TYPE_32__ {TYPE_17__ scl_data; } ;
struct pipe_ctx {TYPE_22__* stream; TYPE_23__* plane_state; TYPE_18__ plane_res; TYPE_11__* bottom_pipe; } ;
struct bw_calcs_data {int graphics_lb_bpc; int underlay_lb_bpc; int increase_voltage_to_support_mclk_switch; int* fbc_en; int* lpt_en; int* bytes_per_pixel; int* interlace_mode; int number_of_displays; void** stereo_mode; void** rotation_angle; void** v_scale_ratio; void** h_scale_ratio; void** v_taps; void** h_taps; void** src_height; void** src_width; void** pitch_in_pixels; void** pixel_rate; void** v_total; void** h_total; void* d1_underlay_mode; void* d0_underlay_mode; void* graphics_micro_tile_mode; void* underlay_micro_tile_mode; void* graphics_tiling_mode; void* underlay_tiling_mode; int /*<<< orphan*/  panning_and_bezel_adjustment; int /*<<< orphan*/  underlay_surface_type; } ;
struct TYPE_43__ {int /*<<< orphan*/  value; } ;
struct TYPE_42__ {int /*<<< orphan*/  value; } ;
struct TYPE_44__ {TYPE_6__ vert; TYPE_5__ horz; } ;
struct TYPE_41__ {int h_taps; int v_taps; } ;
struct TYPE_34__ {int height; int width; } ;
struct TYPE_45__ {TYPE_7__ ratios; TYPE_4__ taps; TYPE_1__ viewport; } ;
struct TYPE_46__ {TYPE_8__ scl_data; } ;
struct TYPE_39__ {int surface_pitch; } ;
struct TYPE_40__ {TYPE_2__ grph; } ;
struct TYPE_38__ {int rotation; int format; int /*<<< orphan*/  visible; } ;
struct TYPE_36__ {int h_total; int v_total; int pix_clk_khz; int h_addressable; int v_addressable; } ;
struct TYPE_35__ {int width; int height; } ;
struct TYPE_33__ {scalar_t__ width; scalar_t__ height; } ;
struct TYPE_37__ {TYPE_21__ timing; TYPE_20__ dst; TYPE_19__ src; } ;
struct TYPE_25__ {TYPE_10__* plane_state; TYPE_9__ plane_res; } ;
struct TYPE_24__ {int rotation; TYPE_3__ plane_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (TYPE_23__*) ; 
#define  ROTATION_ANGLE_0 144 
#define  ROTATION_ANGLE_180 143 
#define  ROTATION_ANGLE_270 142 
#define  ROTATION_ANGLE_90 141 
#define  SURFACE_PIXEL_FORMAT_GRPH_ABGR16161616F 140 
#define  SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010 139 
#define  SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010_XR_BIAS 138 
#define  SURFACE_PIXEL_FORMAT_GRPH_ABGR8888 137 
#define  SURFACE_PIXEL_FORMAT_GRPH_ARGB1555 136 
#define  SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616 135 
#define  SURFACE_PIXEL_FORMAT_GRPH_ARGB2101010 134 
#define  SURFACE_PIXEL_FORMAT_GRPH_ARGB8888 133 
#define  SURFACE_PIXEL_FORMAT_GRPH_RGB565 132 
#define  SURFACE_PIXEL_FORMAT_VIDEO_420_10bpc_YCbCr 131 
#define  SURFACE_PIXEL_FORMAT_VIDEO_420_10bpc_YCrCb 130 
#define  SURFACE_PIXEL_FORMAT_VIDEO_420_YCbCr 129 
#define  SURFACE_PIXEL_FORMAT_VIDEO_420_YCrCb 128 
 int /*<<< orphan*/  bw_def_420 ; 
 void* bw_def_blend ; 
 void* bw_def_display_micro_tiling ; 
 void* bw_def_mono ; 
 int /*<<< orphan*/  bw_def_none ; 
 void* bw_def_tiled ; 
 void* bw_def_underlay_only ; 
 void* bw_frc_to_fixed (int,int) ; 
 void* bw_int_to_fixed (int) ; 
 void* fixed31_32_to_bw_fixed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void populate_initial_data(
	const struct pipe_ctx pipe[], int pipe_count, struct bw_calcs_data *data)
{
	int i, j;
	int num_displays = 0;

	data->underlay_surface_type = bw_def_420;
	data->panning_and_bezel_adjustment = bw_def_none;
	data->graphics_lb_bpc = 10;
	data->underlay_lb_bpc = 8;
	data->underlay_tiling_mode = bw_def_tiled;
	data->graphics_tiling_mode = bw_def_tiled;
	data->underlay_micro_tile_mode = bw_def_display_micro_tiling;
	data->graphics_micro_tile_mode = bw_def_display_micro_tiling;
	data->increase_voltage_to_support_mclk_switch = true;

	/* Pipes with underlay first */
	for (i = 0; i < pipe_count; i++) {
		if (!pipe[i].stream || !pipe[i].bottom_pipe)
			continue;

		ASSERT(pipe[i].plane_state);

		if (num_displays == 0) {
			if (!pipe[i].plane_state->visible)
				data->d0_underlay_mode = bw_def_underlay_only;
			else
				data->d0_underlay_mode = bw_def_blend;
		} else {
			if (!pipe[i].plane_state->visible)
				data->d1_underlay_mode = bw_def_underlay_only;
			else
				data->d1_underlay_mode = bw_def_blend;
		}

		data->fbc_en[num_displays + 4] = false;
		data->lpt_en[num_displays + 4] = false;
		data->h_total[num_displays + 4] = bw_int_to_fixed(pipe[i].stream->timing.h_total);
		data->v_total[num_displays + 4] = bw_int_to_fixed(pipe[i].stream->timing.v_total);
		data->pixel_rate[num_displays + 4] = bw_frc_to_fixed(pipe[i].stream->timing.pix_clk_khz, 1000);
		data->src_width[num_displays + 4] = bw_int_to_fixed(pipe[i].plane_res.scl_data.viewport.width);
		data->pitch_in_pixels[num_displays + 4] = data->src_width[num_displays + 4];
		data->src_height[num_displays + 4] = bw_int_to_fixed(pipe[i].plane_res.scl_data.viewport.height);
		data->h_taps[num_displays + 4] = bw_int_to_fixed(pipe[i].plane_res.scl_data.taps.h_taps);
		data->v_taps[num_displays + 4] = bw_int_to_fixed(pipe[i].plane_res.scl_data.taps.v_taps);
		data->h_scale_ratio[num_displays + 4] = fixed31_32_to_bw_fixed(pipe[i].plane_res.scl_data.ratios.horz.value);
		data->v_scale_ratio[num_displays + 4] = fixed31_32_to_bw_fixed(pipe[i].plane_res.scl_data.ratios.vert.value);
		switch (pipe[i].plane_state->rotation) {
		case ROTATION_ANGLE_0:
			data->rotation_angle[num_displays + 4] = bw_int_to_fixed(0);
			break;
		case ROTATION_ANGLE_90:
			data->rotation_angle[num_displays + 4] = bw_int_to_fixed(90);
			break;
		case ROTATION_ANGLE_180:
			data->rotation_angle[num_displays + 4] = bw_int_to_fixed(180);
			break;
		case ROTATION_ANGLE_270:
			data->rotation_angle[num_displays + 4] = bw_int_to_fixed(270);
			break;
		default:
			break;
		}
		switch (pipe[i].plane_state->format) {
		case SURFACE_PIXEL_FORMAT_VIDEO_420_YCbCr:
		case SURFACE_PIXEL_FORMAT_GRPH_ARGB1555:
		case SURFACE_PIXEL_FORMAT_GRPH_RGB565:
			data->bytes_per_pixel[num_displays + 4] = 2;
			break;
		case SURFACE_PIXEL_FORMAT_GRPH_ARGB8888:
		case SURFACE_PIXEL_FORMAT_GRPH_ABGR8888:
		case SURFACE_PIXEL_FORMAT_GRPH_ARGB2101010:
		case SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010:
		case SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010_XR_BIAS:
		case SURFACE_PIXEL_FORMAT_VIDEO_420_10bpc_YCbCr:
		case SURFACE_PIXEL_FORMAT_VIDEO_420_10bpc_YCrCb:
			data->bytes_per_pixel[num_displays + 4] = 4;
			break;
		case SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616:
		case SURFACE_PIXEL_FORMAT_GRPH_ABGR16161616F:
			data->bytes_per_pixel[num_displays + 4] = 8;
			break;
		default:
			data->bytes_per_pixel[num_displays + 4] = 4;
			break;
		}
		data->interlace_mode[num_displays + 4] = false;
		data->stereo_mode[num_displays + 4] = bw_def_mono;


		for (j = 0; j < 2; j++) {
			data->fbc_en[num_displays * 2 + j] = false;
			data->lpt_en[num_displays * 2 + j] = false;

			data->src_height[num_displays * 2 + j] = bw_int_to_fixed(pipe[i].bottom_pipe->plane_res.scl_data.viewport.height);
			data->src_width[num_displays * 2 + j] = bw_int_to_fixed(pipe[i].bottom_pipe->plane_res.scl_data.viewport.width);
			data->pitch_in_pixels[num_displays * 2 + j] = bw_int_to_fixed(
					pipe[i].bottom_pipe->plane_state->plane_size.grph.surface_pitch);
			data->h_taps[num_displays * 2 + j] = bw_int_to_fixed(pipe[i].bottom_pipe->plane_res.scl_data.taps.h_taps);
			data->v_taps[num_displays * 2 + j] = bw_int_to_fixed(pipe[i].bottom_pipe->plane_res.scl_data.taps.v_taps);
			data->h_scale_ratio[num_displays * 2 + j] = fixed31_32_to_bw_fixed(
					pipe[i].bottom_pipe->plane_res.scl_data.ratios.horz.value);
			data->v_scale_ratio[num_displays * 2 + j] = fixed31_32_to_bw_fixed(
					pipe[i].bottom_pipe->plane_res.scl_data.ratios.vert.value);
			switch (pipe[i].bottom_pipe->plane_state->rotation) {
			case ROTATION_ANGLE_0:
				data->rotation_angle[num_displays * 2 + j] = bw_int_to_fixed(0);
				break;
			case ROTATION_ANGLE_90:
				data->rotation_angle[num_displays * 2 + j] = bw_int_to_fixed(90);
				break;
			case ROTATION_ANGLE_180:
				data->rotation_angle[num_displays * 2 + j] = bw_int_to_fixed(180);
				break;
			case ROTATION_ANGLE_270:
				data->rotation_angle[num_displays * 2 + j] = bw_int_to_fixed(270);
				break;
			default:
				break;
			}
			data->stereo_mode[num_displays * 2 + j] = bw_def_mono;
		}

		num_displays++;
	}

	/* Pipes without underlay after */
	for (i = 0; i < pipe_count; i++) {
		if (!pipe[i].stream || pipe[i].bottom_pipe)
			continue;


		data->fbc_en[num_displays + 4] = false;
		data->lpt_en[num_displays + 4] = false;
		data->h_total[num_displays + 4] = bw_int_to_fixed(pipe[i].stream->timing.h_total);
		data->v_total[num_displays + 4] = bw_int_to_fixed(pipe[i].stream->timing.v_total);
		data->pixel_rate[num_displays + 4] = bw_frc_to_fixed(pipe[i].stream->timing.pix_clk_khz, 1000);
		if (pipe[i].plane_state) {
			data->src_width[num_displays + 4] = bw_int_to_fixed(pipe[i].plane_res.scl_data.viewport.width);
			data->pitch_in_pixels[num_displays + 4] = data->src_width[num_displays + 4];
			data->src_height[num_displays + 4] = bw_int_to_fixed(pipe[i].plane_res.scl_data.viewport.height);
			data->h_taps[num_displays + 4] = bw_int_to_fixed(pipe[i].plane_res.scl_data.taps.h_taps);
			data->v_taps[num_displays + 4] = bw_int_to_fixed(pipe[i].plane_res.scl_data.taps.v_taps);
			data->h_scale_ratio[num_displays + 4] = fixed31_32_to_bw_fixed(pipe[i].plane_res.scl_data.ratios.horz.value);
			data->v_scale_ratio[num_displays + 4] = fixed31_32_to_bw_fixed(pipe[i].plane_res.scl_data.ratios.vert.value);
			switch (pipe[i].plane_state->rotation) {
			case ROTATION_ANGLE_0:
				data->rotation_angle[num_displays + 4] = bw_int_to_fixed(0);
				break;
			case ROTATION_ANGLE_90:
				data->rotation_angle[num_displays + 4] = bw_int_to_fixed(90);
				break;
			case ROTATION_ANGLE_180:
				data->rotation_angle[num_displays + 4] = bw_int_to_fixed(180);
				break;
			case ROTATION_ANGLE_270:
				data->rotation_angle[num_displays + 4] = bw_int_to_fixed(270);
				break;
			default:
				break;
			}
			switch (pipe[i].plane_state->format) {
			case SURFACE_PIXEL_FORMAT_VIDEO_420_YCbCr:
			case SURFACE_PIXEL_FORMAT_VIDEO_420_YCrCb:
			case SURFACE_PIXEL_FORMAT_GRPH_ARGB1555:
			case SURFACE_PIXEL_FORMAT_GRPH_RGB565:
				data->bytes_per_pixel[num_displays + 4] = 2;
				break;
			case SURFACE_PIXEL_FORMAT_GRPH_ARGB8888:
			case SURFACE_PIXEL_FORMAT_GRPH_ABGR8888:
			case SURFACE_PIXEL_FORMAT_GRPH_ARGB2101010:
			case SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010:
			case SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010_XR_BIAS:
			case SURFACE_PIXEL_FORMAT_VIDEO_420_10bpc_YCbCr:
			case SURFACE_PIXEL_FORMAT_VIDEO_420_10bpc_YCrCb:
				data->bytes_per_pixel[num_displays + 4] = 4;
				break;
			case SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616:
			case SURFACE_PIXEL_FORMAT_GRPH_ABGR16161616F:
				data->bytes_per_pixel[num_displays + 4] = 8;
				break;
			default:
				data->bytes_per_pixel[num_displays + 4] = 4;
				break;
			}
		} else if (pipe[i].stream->dst.width != 0 &&
					pipe[i].stream->dst.height != 0 &&
					pipe[i].stream->src.width != 0 &&
					pipe[i].stream->src.height != 0) {
			data->src_width[num_displays + 4] = bw_int_to_fixed(pipe[i].stream->src.width);
			data->pitch_in_pixels[num_displays + 4] = data->src_width[num_displays + 4];
			data->src_height[num_displays + 4] = bw_int_to_fixed(pipe[i].stream->src.height);
			data->h_taps[num_displays + 4] = pipe[i].stream->src.width == pipe[i].stream->dst.width ? bw_int_to_fixed(1) : bw_int_to_fixed(2);
			data->v_taps[num_displays + 4] = pipe[i].stream->src.height == pipe[i].stream->dst.height ? bw_int_to_fixed(1) : bw_int_to_fixed(2);
			data->h_scale_ratio[num_displays + 4] = bw_frc_to_fixed(pipe[i].stream->src.width, pipe[i].stream->dst.width);
			data->v_scale_ratio[num_displays + 4] = bw_frc_to_fixed(pipe[i].stream->src.height, pipe[i].stream->dst.height);
			data->rotation_angle[num_displays + 4] = bw_int_to_fixed(0);
			data->bytes_per_pixel[num_displays + 4] = 4;
		} else {
			data->src_width[num_displays + 4] = bw_int_to_fixed(pipe[i].stream->timing.h_addressable);
			data->pitch_in_pixels[num_displays + 4] = data->src_width[num_displays + 4];
			data->src_height[num_displays + 4] = bw_int_to_fixed(pipe[i].stream->timing.v_addressable);
			data->h_taps[num_displays + 4] = bw_int_to_fixed(1);
			data->v_taps[num_displays + 4] = bw_int_to_fixed(1);
			data->h_scale_ratio[num_displays + 4] = bw_int_to_fixed(1);
			data->v_scale_ratio[num_displays + 4] = bw_int_to_fixed(1);
			data->rotation_angle[num_displays + 4] = bw_int_to_fixed(0);
			data->bytes_per_pixel[num_displays + 4] = 4;
		}

		data->interlace_mode[num_displays + 4] = false;
		data->stereo_mode[num_displays + 4] = bw_def_mono;
		num_displays++;
	}

	data->number_of_displays = num_displays;
}