#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_83__   TYPE_9__ ;
typedef  struct TYPE_82__   TYPE_8__ ;
typedef  struct TYPE_81__   TYPE_7__ ;
typedef  struct TYPE_80__   TYPE_6__ ;
typedef  struct TYPE_79__   TYPE_5__ ;
typedef  struct TYPE_78__   TYPE_4__ ;
typedef  struct TYPE_77__   TYPE_43__ ;
typedef  struct TYPE_76__   TYPE_40__ ;
typedef  struct TYPE_75__   TYPE_3__ ;
typedef  struct TYPE_74__   TYPE_38__ ;
typedef  struct TYPE_73__   TYPE_37__ ;
typedef  struct TYPE_72__   TYPE_36__ ;
typedef  struct TYPE_71__   TYPE_35__ ;
typedef  struct TYPE_70__   TYPE_34__ ;
typedef  struct TYPE_69__   TYPE_33__ ;
typedef  struct TYPE_68__   TYPE_32__ ;
typedef  struct TYPE_67__   TYPE_31__ ;
typedef  struct TYPE_66__   TYPE_30__ ;
typedef  struct TYPE_65__   TYPE_2__ ;
typedef  struct TYPE_64__   TYPE_29__ ;
typedef  struct TYPE_63__   TYPE_28__ ;
typedef  struct TYPE_62__   TYPE_27__ ;
typedef  struct TYPE_61__   TYPE_26__ ;
typedef  struct TYPE_60__   TYPE_25__ ;
typedef  struct TYPE_59__   TYPE_24__ ;
typedef  struct TYPE_58__   TYPE_23__ ;
typedef  struct TYPE_57__   TYPE_22__ ;
typedef  struct TYPE_56__   TYPE_21__ ;
typedef  struct TYPE_55__   TYPE_20__ ;
typedef  struct TYPE_54__   TYPE_1__ ;
typedef  struct TYPE_53__   TYPE_19__ ;
typedef  struct TYPE_52__   TYPE_18__ ;
typedef  struct TYPE_51__   TYPE_17__ ;
typedef  struct TYPE_50__   TYPE_16__ ;
typedef  struct TYPE_49__   TYPE_15__ ;
typedef  struct TYPE_48__   TYPE_14__ ;
typedef  struct TYPE_47__   TYPE_13__ ;
typedef  struct TYPE_46__   TYPE_12__ ;
typedef  struct TYPE_45__   TYPE_11__ ;
typedef  struct TYPE_44__   TYPE_10__ ;

/* Type definitions */
struct TYPE_67__ {int h_taps; int v_taps; int /*<<< orphan*/  v_taps_c; int /*<<< orphan*/  h_taps_c; } ;
struct TYPE_62__ {scalar_t__ value; } ;
struct TYPE_61__ {scalar_t__ value; } ;
struct TYPE_60__ {scalar_t__ value; } ;
struct TYPE_59__ {scalar_t__ value; } ;
struct TYPE_63__ {TYPE_27__ horz_c; TYPE_26__ vert_c; TYPE_25__ horz; TYPE_24__ vert; } ;
struct TYPE_46__ {int width; int height; } ;
struct TYPE_83__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y; } ;
struct TYPE_82__ {int width; int height; int /*<<< orphan*/  y; } ;
struct scaler_data {TYPE_31__ taps; TYPE_28__ ratios; TYPE_12__ recout; TYPE_9__ viewport_c; TYPE_8__ viewport; } ;
struct resource_context {TYPE_22__* pipe_ctx; } ;
struct pipe_ctx {int /*<<< orphan*/  pipe_idx; struct pipe_ctx* prev_odm_pipe; } ;
struct TYPE_68__ {int /*<<< orphan*/  swizzle; } ;
struct TYPE_69__ {TYPE_32__ gfx9; } ;
struct TYPE_45__ {int enable; int /*<<< orphan*/  meta_pitch; int /*<<< orphan*/  meta_pitch_c; } ;
struct TYPE_44__ {int surface_pitch; int /*<<< orphan*/  chroma_pitch; } ;
struct dc_plane_state {scalar_t__ rotation; int format; TYPE_33__ tiling_info; TYPE_11__ dcc; TYPE_10__ plane_size; int /*<<< orphan*/  flip_immediate; } ;
struct TYPE_65__ {int /*<<< orphan*/  INTERLACE; int /*<<< orphan*/  DSC; } ;
struct TYPE_54__ {int /*<<< orphan*/  num_slices_h; } ;
struct dc_crtc_timing {int v_total; int v_addressable; int v_border_top; int v_border_bottom; int h_total; int h_front_porch; int h_addressable; int h_border_left; int h_border_right; int v_front_porch; double pix_clk_100hz; scalar_t__ timing_3d_format; int display_color_depth; int pixel_encoding; TYPE_2__ flags; TYPE_1__ dsc_cfg; } ;
struct TYPE_64__ {scalar_t__ always_scale; } ;
struct dc {TYPE_37__* res_pool; TYPE_29__ debug; } ;
struct TYPE_70__ {int dynamic_metadata_enable; int dynamic_metadata_lines_before_active; int dynamic_metadata_xmit_bytes; int dcc; int dcc_rate; int num_cursors; int cur0_src_width; int cur1_src_width; int viewport_width; int viewport_height; int data_pitch; int is_hsplit; void* source_format; int /*<<< orphan*/  sw_mode; int /*<<< orphan*/  macro_tile_size; int /*<<< orphan*/  meta_pitch; int /*<<< orphan*/  meta_pitch_c; int /*<<< orphan*/  data_pitch_c; int /*<<< orphan*/  viewport_height_c; int /*<<< orphan*/  viewport_width_c; int /*<<< orphan*/  viewport_y_c; int /*<<< orphan*/  viewport_y_y; void* source_scan; int /*<<< orphan*/  immediate_flip; void* cur1_bpp; void* cur0_bpp; int /*<<< orphan*/  hsplit_grp; } ;
struct TYPE_66__ {int htaps; int vtaps; int /*<<< orphan*/  vtaps_c; int /*<<< orphan*/  htaps_c; } ;
struct TYPE_58__ {double hscl_ratio; double vscl_ratio; int scl_enable; double hscl_ratio_c; double vscl_ratio_c; void* lb_depth; } ;
struct TYPE_51__ {int synchronized_vblank_all_planes; int hblank_start; int hblank_end; int vblank_start; int vblank_end; int htotal; int vtotal; int hactive; int vactive; double pixel_rate_mhz; int vtotal_min; int vtotal_max; int odm_combine; int recout_width; int recout_height; int full_recout_width; int full_recout_height; int /*<<< orphan*/  otg_inst; int /*<<< orphan*/  interlaced; } ;
struct TYPE_71__ {TYPE_34__ src; TYPE_30__ scale_taps; TYPE_23__ scale_ratio_depth; TYPE_17__ dest; } ;
struct TYPE_80__ {int dp_lanes; int output_bpp; int output_bpc; void* output_format; void* output_type; int /*<<< orphan*/  dsc_slices; int /*<<< orphan*/  dsc_enable; } ;
struct TYPE_74__ {TYPE_35__ pipe; TYPE_6__ dout; } ;
typedef  TYPE_38__ display_e2e_pipe_params_st ;
struct TYPE_81__ {struct scaler_data scl_data; } ;
struct TYPE_79__ {int v_total_min; int v_total_max; } ;
struct TYPE_78__ {TYPE_3__* tg; } ;
struct TYPE_77__ {scalar_t__ value; } ;
struct TYPE_76__ {int signal; struct dc_crtc_timing timing; TYPE_5__ adjust; scalar_t__ use_dynamic_meta; } ;
struct TYPE_75__ {int /*<<< orphan*/  inst; } ;
struct TYPE_73__ {int pipe_count; TYPE_36__* funcs; } ;
struct TYPE_72__ {int /*<<< orphan*/  (* populate_dml_writeback_from_context ) (struct dc*,struct resource_context*,TYPE_38__*) ;} ;
struct TYPE_57__ {TYPE_21__* top_pipe; TYPE_16__* bottom_pipe; TYPE_7__ plane_res; struct dc_plane_state* plane_state; TYPE_40__* stream; struct pipe_ctx* prev_odm_pipe; int /*<<< orphan*/  pipe_idx; scalar_t__ next_odm_pipe; TYPE_4__ stream_res; } ;
struct TYPE_52__ {scalar_t__ height; scalar_t__ width; } ;
struct TYPE_53__ {TYPE_18__ recout; } ;
struct TYPE_55__ {TYPE_19__ scl_data; } ;
struct TYPE_56__ {TYPE_20__ plane_res; struct dc_plane_state* plane_state; int /*<<< orphan*/  pipe_idx; } ;
struct TYPE_47__ {scalar_t__ height; scalar_t__ width; } ;
struct TYPE_48__ {TYPE_13__ recout; } ;
struct TYPE_49__ {TYPE_14__ scl_data; } ;
struct TYPE_50__ {TYPE_15__ plane_res; struct dc_plane_state* plane_state; } ;

/* Variables and functions */
#define  COLOR_DEPTH_101010 155 
#define  COLOR_DEPTH_111111 154 
#define  COLOR_DEPTH_121212 153 
#define  COLOR_DEPTH_141414 152 
#define  COLOR_DEPTH_161616 151 
#define  COLOR_DEPTH_666 150 
#define  COLOR_DEPTH_888 149 
#define  COLOR_DEPTH_999 148 
#define  PIXEL_ENCODING_RGB 147 
#define  PIXEL_ENCODING_YCBCR420 146 
#define  PIXEL_ENCODING_YCBCR422 145 
#define  PIXEL_ENCODING_YCBCR444 144 
 scalar_t__ ROTATION_ANGLE_270 ; 
 scalar_t__ ROTATION_ANGLE_90 ; 
#define  SIGNAL_TYPE_DISPLAY_PORT 143 
#define  SIGNAL_TYPE_DISPLAY_PORT_MST 142 
#define  SIGNAL_TYPE_DVI_DUAL_LINK 141 
#define  SIGNAL_TYPE_DVI_SINGLE_LINK 140 
#define  SIGNAL_TYPE_EDP 139 
#define  SIGNAL_TYPE_HDMI_TYPE_A 138 
#define  SURFACE_PIXEL_FORMAT_GRPH_ABGR16161616F 137 
#define  SURFACE_PIXEL_FORMAT_GRPH_ARGB1555 136 
#define  SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616 135 
#define  SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616F 134 
#define  SURFACE_PIXEL_FORMAT_GRPH_PALETA_256_COLORS 133 
#define  SURFACE_PIXEL_FORMAT_GRPH_RGB565 132 
#define  SURFACE_PIXEL_FORMAT_VIDEO_420_10bpc_YCbCr 131 
#define  SURFACE_PIXEL_FORMAT_VIDEO_420_10bpc_YCrCb 130 
#define  SURFACE_PIXEL_FORMAT_VIDEO_420_YCbCr 129 
#define  SURFACE_PIXEL_FORMAT_VIDEO_420_YCrCb 128 
 int SURFACE_PIXEL_FORMAT_VIDEO_BEGIN ; 
 scalar_t__ TIMING_3D_FORMAT_HW_FRAME_PACKING ; 
 TYPE_43__ dc_fixpt_one ; 
 scalar_t__ dc_is_dp_signal (int) ; 
 void* dm_420 ; 
 void* dm_420_10 ; 
 void* dm_420_8 ; 
 void* dm_444 ; 
 void* dm_444_16 ; 
 void* dm_444_32 ; 
 void* dm_444_64 ; 
 void* dm_444_8 ; 
 int /*<<< orphan*/  dm_64k_tile ; 
 void* dm_cur_32bit ; 
 void* dm_dp ; 
 void* dm_edp ; 
 void* dm_hdmi ; 
 void* dm_horz ; 
 void* dm_lb_16 ; 
 void* dm_n422 ; 
 void* dm_s422 ; 
 int /*<<< orphan*/  dm_sw_linear ; 
 void* dm_vert ; 
 int /*<<< orphan*/  resource_are_streams_timing_synchronizable (TYPE_40__*,TYPE_40__*) ; 
 int /*<<< orphan*/  stub1 (struct dc*,struct resource_context*,TYPE_38__*) ; 
 int /*<<< orphan*/  swizzle_mode_to_macro_tile_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swizzle_to_dml_params (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int dcn20_populate_dml_pipes_from_context(
		struct dc *dc, struct resource_context *res_ctx, display_e2e_pipe_params_st *pipes)
{
	int pipe_cnt, i;
	bool synchronized_vblank = true;

	for (i = 0, pipe_cnt = -1; i < dc->res_pool->pipe_count; i++) {
		if (!res_ctx->pipe_ctx[i].stream)
			continue;

		if (pipe_cnt < 0) {
			pipe_cnt = i;
			continue;
		}
		if (!resource_are_streams_timing_synchronizable(
				res_ctx->pipe_ctx[pipe_cnt].stream,
				res_ctx->pipe_ctx[i].stream)) {
			synchronized_vblank = false;
			break;
		}
	}

	for (i = 0, pipe_cnt = 0; i < dc->res_pool->pipe_count; i++) {
		struct dc_crtc_timing *timing = &res_ctx->pipe_ctx[i].stream->timing;
		int output_bpc;

		if (!res_ctx->pipe_ctx[i].stream)
			continue;
		/* todo:
		pipes[pipe_cnt].pipe.src.dynamic_metadata_enable = 0;
		pipes[pipe_cnt].pipe.src.dcc = 0;
		pipes[pipe_cnt].pipe.src.vm = 0;*/

#ifdef CONFIG_DRM_AMD_DC_DSC_SUPPORT
		pipes[pipe_cnt].dout.dsc_enable = res_ctx->pipe_ctx[i].stream->timing.flags.DSC;
		/* todo: rotation?*/
		pipes[pipe_cnt].dout.dsc_slices = res_ctx->pipe_ctx[i].stream->timing.dsc_cfg.num_slices_h;
#endif
		if (res_ctx->pipe_ctx[i].stream->use_dynamic_meta) {
			pipes[pipe_cnt].pipe.src.dynamic_metadata_enable = true;
			/* 1/2 vblank */
			pipes[pipe_cnt].pipe.src.dynamic_metadata_lines_before_active =
				(timing->v_total - timing->v_addressable
					- timing->v_border_top - timing->v_border_bottom) / 2;
			/* 36 bytes dp, 32 hdmi */
			pipes[pipe_cnt].pipe.src.dynamic_metadata_xmit_bytes =
				dc_is_dp_signal(res_ctx->pipe_ctx[i].stream->signal) ? 36 : 32;
		}
		pipes[pipe_cnt].pipe.src.dcc = false;
		pipes[pipe_cnt].pipe.src.dcc_rate = 1;
		pipes[pipe_cnt].pipe.dest.synchronized_vblank_all_planes = synchronized_vblank;
		pipes[pipe_cnt].pipe.dest.hblank_start = timing->h_total - timing->h_front_porch;
		pipes[pipe_cnt].pipe.dest.hblank_end = pipes[pipe_cnt].pipe.dest.hblank_start
				- timing->h_addressable
				- timing->h_border_left
				- timing->h_border_right;
		pipes[pipe_cnt].pipe.dest.vblank_start = timing->v_total - timing->v_front_porch;
		pipes[pipe_cnt].pipe.dest.vblank_end = pipes[pipe_cnt].pipe.dest.vblank_start
				- timing->v_addressable
				- timing->v_border_top
				- timing->v_border_bottom;
		pipes[pipe_cnt].pipe.dest.htotal = timing->h_total;
		pipes[pipe_cnt].pipe.dest.vtotal = timing->v_total;
		pipes[pipe_cnt].pipe.dest.hactive = timing->h_addressable;
		pipes[pipe_cnt].pipe.dest.vactive = timing->v_addressable;
		pipes[pipe_cnt].pipe.dest.interlaced = timing->flags.INTERLACE;
		pipes[pipe_cnt].pipe.dest.pixel_rate_mhz = timing->pix_clk_100hz/10000.0;
		if (timing->timing_3d_format == TIMING_3D_FORMAT_HW_FRAME_PACKING)
			pipes[pipe_cnt].pipe.dest.pixel_rate_mhz *= 2;
		pipes[pipe_cnt].pipe.dest.otg_inst = res_ctx->pipe_ctx[i].stream_res.tg->inst;
		pipes[pipe_cnt].dout.dp_lanes = 4;
		pipes[pipe_cnt].pipe.dest.vtotal_min = res_ctx->pipe_ctx[i].stream->adjust.v_total_min;
		pipes[pipe_cnt].pipe.dest.vtotal_max = res_ctx->pipe_ctx[i].stream->adjust.v_total_max;
		pipes[pipe_cnt].pipe.dest.odm_combine = res_ctx->pipe_ctx[i].prev_odm_pipe
							|| res_ctx->pipe_ctx[i].next_odm_pipe;
		pipes[pipe_cnt].pipe.src.hsplit_grp = res_ctx->pipe_ctx[i].pipe_idx;
		if (res_ctx->pipe_ctx[i].top_pipe && res_ctx->pipe_ctx[i].top_pipe->plane_state
				== res_ctx->pipe_ctx[i].plane_state)
			pipes[pipe_cnt].pipe.src.hsplit_grp = res_ctx->pipe_ctx[i].top_pipe->pipe_idx;
		else if (res_ctx->pipe_ctx[i].prev_odm_pipe) {
			struct pipe_ctx *first_pipe = res_ctx->pipe_ctx[i].prev_odm_pipe;

			while (first_pipe->prev_odm_pipe)
				first_pipe = first_pipe->prev_odm_pipe;
			pipes[pipe_cnt].pipe.src.hsplit_grp = first_pipe->pipe_idx;
		}

		switch (res_ctx->pipe_ctx[i].stream->signal) {
		case SIGNAL_TYPE_DISPLAY_PORT_MST:
		case SIGNAL_TYPE_DISPLAY_PORT:
			pipes[pipe_cnt].dout.output_type = dm_dp;
			break;
		case SIGNAL_TYPE_EDP:
			pipes[pipe_cnt].dout.output_type = dm_edp;
			break;
		case SIGNAL_TYPE_HDMI_TYPE_A:
		case SIGNAL_TYPE_DVI_SINGLE_LINK:
		case SIGNAL_TYPE_DVI_DUAL_LINK:
			pipes[pipe_cnt].dout.output_type = dm_hdmi;
			break;
		default:
			/* In case there is no signal, set dp with 4 lanes to allow max config */
			pipes[pipe_cnt].dout.output_type = dm_dp;
			pipes[pipe_cnt].dout.dp_lanes = 4;
		}

		switch (res_ctx->pipe_ctx[i].stream->timing.display_color_depth) {
		case COLOR_DEPTH_666:
			output_bpc = 6;
			break;
		case COLOR_DEPTH_888:
			output_bpc = 8;
			break;
		case COLOR_DEPTH_101010:
			output_bpc = 10;
			break;
		case COLOR_DEPTH_121212:
			output_bpc = 12;
			break;
		case COLOR_DEPTH_141414:
			output_bpc = 14;
			break;
		case COLOR_DEPTH_161616:
			output_bpc = 16;
			break;
#ifdef CONFIG_DRM_AMD_DC_DCN2_0
		case COLOR_DEPTH_999:
			output_bpc = 9;
			break;
		case COLOR_DEPTH_111111:
			output_bpc = 11;
			break;
#endif
		default:
			output_bpc = 8;
			break;
		}

		switch (res_ctx->pipe_ctx[i].stream->timing.pixel_encoding) {
		case PIXEL_ENCODING_RGB:
		case PIXEL_ENCODING_YCBCR444:
			pipes[pipe_cnt].dout.output_format = dm_444;
			pipes[pipe_cnt].dout.output_bpp = output_bpc * 3;
			break;
		case PIXEL_ENCODING_YCBCR420:
			pipes[pipe_cnt].dout.output_format = dm_420;
			pipes[pipe_cnt].dout.output_bpp = (output_bpc * 3) / 2;
			break;
		case PIXEL_ENCODING_YCBCR422:
			if (true) /* todo */
				pipes[pipe_cnt].dout.output_format = dm_s422;
			else
				pipes[pipe_cnt].dout.output_format = dm_n422;
			pipes[pipe_cnt].dout.output_bpp = output_bpc * 2;
			break;
		default:
			pipes[pipe_cnt].dout.output_format = dm_444;
			pipes[pipe_cnt].dout.output_bpp = output_bpc * 3;
		}

		/* todo: default max for now, until there is logic reflecting this in dc*/
		pipes[pipe_cnt].dout.output_bpc = 12;
		/*
		 * Use max cursor settings for calculations to minimize
		 * bw calculations due to cursor on/off
		 */
		pipes[pipe_cnt].pipe.src.num_cursors = 2;
		pipes[pipe_cnt].pipe.src.cur0_src_width = 256;
		pipes[pipe_cnt].pipe.src.cur0_bpp = dm_cur_32bit;
		pipes[pipe_cnt].pipe.src.cur1_src_width = 256;
		pipes[pipe_cnt].pipe.src.cur1_bpp = dm_cur_32bit;

		if (!res_ctx->pipe_ctx[i].plane_state) {
			pipes[pipe_cnt].pipe.src.source_scan = dm_horz;
			pipes[pipe_cnt].pipe.src.sw_mode = dm_sw_linear;
			pipes[pipe_cnt].pipe.src.macro_tile_size = dm_64k_tile;
			pipes[pipe_cnt].pipe.src.viewport_width = timing->h_addressable;
			if (pipes[pipe_cnt].pipe.src.viewport_width > 1920)
				pipes[pipe_cnt].pipe.src.viewport_width = 1920;
			pipes[pipe_cnt].pipe.src.viewport_height = timing->v_addressable;
			if (pipes[pipe_cnt].pipe.src.viewport_height > 1080)
				pipes[pipe_cnt].pipe.src.viewport_height = 1080;
			pipes[pipe_cnt].pipe.src.data_pitch = ((pipes[pipe_cnt].pipe.src.viewport_width + 63) / 64) * 64; /* linear sw only */
			pipes[pipe_cnt].pipe.src.source_format = dm_444_32;
			pipes[pipe_cnt].pipe.dest.recout_width = pipes[pipe_cnt].pipe.src.viewport_width; /*vp_width/hratio*/
			pipes[pipe_cnt].pipe.dest.recout_height = pipes[pipe_cnt].pipe.src.viewport_height; /*vp_height/vratio*/
			pipes[pipe_cnt].pipe.dest.full_recout_width = pipes[pipe_cnt].pipe.dest.recout_width;  /*when is_hsplit != 1*/
			pipes[pipe_cnt].pipe.dest.full_recout_height = pipes[pipe_cnt].pipe.dest.recout_height; /*when is_hsplit != 1*/
			pipes[pipe_cnt].pipe.scale_ratio_depth.lb_depth = dm_lb_16;
			pipes[pipe_cnt].pipe.scale_ratio_depth.hscl_ratio = 1.0;
			pipes[pipe_cnt].pipe.scale_ratio_depth.vscl_ratio = 1.0;
			pipes[pipe_cnt].pipe.scale_ratio_depth.scl_enable = 0; /*Lb only or Full scl*/
			pipes[pipe_cnt].pipe.scale_taps.htaps = 1;
			pipes[pipe_cnt].pipe.scale_taps.vtaps = 1;
			pipes[pipe_cnt].pipe.src.is_hsplit = 0;
			pipes[pipe_cnt].pipe.dest.odm_combine = 0;
			pipes[pipe_cnt].pipe.dest.vtotal_min = timing->v_total;
			pipes[pipe_cnt].pipe.dest.vtotal_max = timing->v_total;
		} else {
			struct dc_plane_state *pln = res_ctx->pipe_ctx[i].plane_state;
			struct scaler_data *scl = &res_ctx->pipe_ctx[i].plane_res.scl_data;

			pipes[pipe_cnt].pipe.src.immediate_flip = pln->flip_immediate;
			pipes[pipe_cnt].pipe.src.is_hsplit = (res_ctx->pipe_ctx[i].bottom_pipe
					&& res_ctx->pipe_ctx[i].bottom_pipe->plane_state == pln)
					|| (res_ctx->pipe_ctx[i].top_pipe
					&& res_ctx->pipe_ctx[i].top_pipe->plane_state == pln);
			pipes[pipe_cnt].pipe.src.source_scan = pln->rotation == ROTATION_ANGLE_90
					|| pln->rotation == ROTATION_ANGLE_270 ? dm_vert : dm_horz;
			pipes[pipe_cnt].pipe.src.viewport_y_y = scl->viewport.y;
			pipes[pipe_cnt].pipe.src.viewport_y_c = scl->viewport_c.y;
			pipes[pipe_cnt].pipe.src.viewport_width = scl->viewport.width;
			pipes[pipe_cnt].pipe.src.viewport_width_c = scl->viewport_c.width;
			pipes[pipe_cnt].pipe.src.viewport_height = scl->viewport.height;
			pipes[pipe_cnt].pipe.src.viewport_height_c = scl->viewport_c.height;
			if (pln->format >= SURFACE_PIXEL_FORMAT_VIDEO_BEGIN) {
				pipes[pipe_cnt].pipe.src.data_pitch = pln->plane_size.surface_pitch;
				pipes[pipe_cnt].pipe.src.data_pitch_c = pln->plane_size.chroma_pitch;
				pipes[pipe_cnt].pipe.src.meta_pitch = pln->dcc.meta_pitch;
				pipes[pipe_cnt].pipe.src.meta_pitch_c = pln->dcc.meta_pitch_c;
			} else {
				pipes[pipe_cnt].pipe.src.data_pitch = pln->plane_size.surface_pitch;
				pipes[pipe_cnt].pipe.src.meta_pitch = pln->dcc.meta_pitch;
			}
			pipes[pipe_cnt].pipe.src.dcc = pln->dcc.enable;
			pipes[pipe_cnt].pipe.dest.recout_width = scl->recout.width;
			pipes[pipe_cnt].pipe.dest.recout_height = scl->recout.height;
			pipes[pipe_cnt].pipe.dest.full_recout_width = scl->recout.width;
			pipes[pipe_cnt].pipe.dest.full_recout_height = scl->recout.height;
			if (res_ctx->pipe_ctx[i].bottom_pipe && res_ctx->pipe_ctx[i].bottom_pipe->plane_state == pln) {
				pipes[pipe_cnt].pipe.dest.full_recout_width +=
						res_ctx->pipe_ctx[i].bottom_pipe->plane_res.scl_data.recout.width;
				pipes[pipe_cnt].pipe.dest.full_recout_height +=
						res_ctx->pipe_ctx[i].bottom_pipe->plane_res.scl_data.recout.height;
			} else if (res_ctx->pipe_ctx[i].top_pipe && res_ctx->pipe_ctx[i].top_pipe->plane_state == pln) {
				pipes[pipe_cnt].pipe.dest.full_recout_width +=
						res_ctx->pipe_ctx[i].top_pipe->plane_res.scl_data.recout.width;
				pipes[pipe_cnt].pipe.dest.full_recout_height +=
						res_ctx->pipe_ctx[i].top_pipe->plane_res.scl_data.recout.height;
			}

			pipes[pipe_cnt].pipe.scale_ratio_depth.lb_depth = dm_lb_16;
			pipes[pipe_cnt].pipe.scale_ratio_depth.hscl_ratio = (double) scl->ratios.horz.value / (1ULL<<32);
			pipes[pipe_cnt].pipe.scale_ratio_depth.hscl_ratio_c = (double) scl->ratios.horz_c.value / (1ULL<<32);
			pipes[pipe_cnt].pipe.scale_ratio_depth.vscl_ratio = (double) scl->ratios.vert.value / (1ULL<<32);
			pipes[pipe_cnt].pipe.scale_ratio_depth.vscl_ratio_c = (double) scl->ratios.vert_c.value / (1ULL<<32);
			pipes[pipe_cnt].pipe.scale_ratio_depth.scl_enable =
					scl->ratios.vert.value != dc_fixpt_one.value
					|| scl->ratios.horz.value != dc_fixpt_one.value
					|| scl->ratios.vert_c.value != dc_fixpt_one.value
					|| scl->ratios.horz_c.value != dc_fixpt_one.value /*Lb only or Full scl*/
					|| dc->debug.always_scale; /*support always scale*/
			pipes[pipe_cnt].pipe.scale_taps.htaps = scl->taps.h_taps;
			pipes[pipe_cnt].pipe.scale_taps.htaps_c = scl->taps.h_taps_c;
			pipes[pipe_cnt].pipe.scale_taps.vtaps = scl->taps.v_taps;
			pipes[pipe_cnt].pipe.scale_taps.vtaps_c = scl->taps.v_taps_c;

			pipes[pipe_cnt].pipe.src.macro_tile_size =
					swizzle_mode_to_macro_tile_size(pln->tiling_info.gfx9.swizzle);
			swizzle_to_dml_params(pln->tiling_info.gfx9.swizzle,
					&pipes[pipe_cnt].pipe.src.sw_mode);

			switch (pln->format) {
			case SURFACE_PIXEL_FORMAT_VIDEO_420_YCbCr:
			case SURFACE_PIXEL_FORMAT_VIDEO_420_YCrCb:
				pipes[pipe_cnt].pipe.src.source_format = dm_420_8;
				break;
			case SURFACE_PIXEL_FORMAT_VIDEO_420_10bpc_YCbCr:
			case SURFACE_PIXEL_FORMAT_VIDEO_420_10bpc_YCrCb:
				pipes[pipe_cnt].pipe.src.source_format = dm_420_10;
				break;
			case SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616:
			case SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616F:
			case SURFACE_PIXEL_FORMAT_GRPH_ABGR16161616F:
				pipes[pipe_cnt].pipe.src.source_format = dm_444_64;
				break;
			case SURFACE_PIXEL_FORMAT_GRPH_ARGB1555:
			case SURFACE_PIXEL_FORMAT_GRPH_RGB565:
				pipes[pipe_cnt].pipe.src.source_format = dm_444_16;
				break;
			case SURFACE_PIXEL_FORMAT_GRPH_PALETA_256_COLORS:
				pipes[pipe_cnt].pipe.src.source_format = dm_444_8;
				break;
			default:
				pipes[pipe_cnt].pipe.src.source_format = dm_444_32;
				break;
			}
		}

		pipe_cnt++;
	}

	/* populate writeback information */
	dc->res_pool->funcs->populate_dml_writeback_from_context(dc, res_ctx, pipes);

	return pipe_cnt;
}