#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct omap_video_timings {int interlace; } ;
typedef  int s32 ;
typedef  enum omap_plane { ____Placeholder_omap_plane } omap_plane ;
typedef  enum omap_overlay_caps { ____Placeholder_omap_overlay_caps } omap_overlay_caps ;
typedef  enum omap_dss_rotation_type { ____Placeholder_omap_dss_rotation_type } omap_dss_rotation_type ;
typedef  enum omap_color_mode { ____Placeholder_omap_color_mode } omap_color_mode ;
struct TYPE_4__ {TYPE_1__* feat; } ;
struct TYPE_3__ {scalar_t__ last_pixel_inc_missing; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSDBG (char*,...) ; 
 int /*<<< orphan*/  DSSERR (char*,int) ; 
 int EINVAL ; 
#define  OMAP_DSS_COLOR_NV12 130 
#define  OMAP_DSS_COLOR_UYVY 129 
#define  OMAP_DSS_COLOR_YUV2 128 
 int OMAP_DSS_OVL_CAP_SCALE ; 
 int OMAP_DSS_ROT_DMA ; 
 int OMAP_DSS_ROT_TILER ; 
 int OMAP_DSS_WB ; 
 int /*<<< orphan*/  calc_dma_rotation_offset (int /*<<< orphan*/ ,int,int,int,int,int,int,unsigned int,unsigned int*,unsigned int*,int*,int*,int,int) ; 
 int /*<<< orphan*/  calc_tiler_rotation_offset (int,int,int,int,unsigned int,unsigned int*,unsigned int*,int*,int*,int,int) ; 
 int /*<<< orphan*/  calc_vrfb_rotation_offset (int /*<<< orphan*/ ,int,int,int,int,int,int,unsigned int,unsigned int*,unsigned int*,int*,int*,int,int) ; 
 TYPE_2__ dispc ; 
 int dispc_ovl_calc_scaling (unsigned long,unsigned long,int,struct omap_video_timings const*,int,int,int,int,int,int*,int*,int*,int,int,int) ; 
 int /*<<< orphan*/  dispc_ovl_configure_burst_type (int,int) ; 
 int /*<<< orphan*/  dispc_ovl_enable_replication (int,int,int) ; 
 int /*<<< orphan*/  dispc_ovl_set_ba0 (int,scalar_t__) ; 
 int /*<<< orphan*/  dispc_ovl_set_ba0_uv (int,scalar_t__) ; 
 int /*<<< orphan*/  dispc_ovl_set_ba1 (int,scalar_t__) ; 
 int /*<<< orphan*/  dispc_ovl_set_ba1_uv (int,scalar_t__) ; 
 int /*<<< orphan*/  dispc_ovl_set_color_mode (int,int) ; 
 int /*<<< orphan*/  dispc_ovl_set_input_size (int,int,int) ; 
 int /*<<< orphan*/  dispc_ovl_set_output_size (int,int,int) ; 
 int /*<<< orphan*/  dispc_ovl_set_pix_inc (int,int) ; 
 int /*<<< orphan*/  dispc_ovl_set_pos (int,int,int,int) ; 
 int /*<<< orphan*/  dispc_ovl_set_pre_mult_alpha (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dispc_ovl_set_rotation_attrs (int,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  dispc_ovl_set_row_inc (int,int) ; 
 int /*<<< orphan*/  dispc_ovl_set_scaling (int,int,int,int,int,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dispc_ovl_set_vid_color_conv (int,int) ; 
 int /*<<< orphan*/  dispc_ovl_set_zorder (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dispc_ovl_setup_global_alpha (int,int,int /*<<< orphan*/ ) ; 
 unsigned long dispc_plane_lclk_rate (int) ; 
 unsigned long dispc_plane_pclk_rate (int) ; 
 int /*<<< orphan*/  dss_feat_color_mode_supported (int,int) ; 

__attribute__((used)) static int dispc_ovl_setup_common(enum omap_plane plane,
		enum omap_overlay_caps caps, u32 paddr, u32 p_uv_addr,
		u16 screen_width, int pos_x, int pos_y, u16 width, u16 height,
		u16 out_width, u16 out_height, enum omap_color_mode color_mode,
		u8 rotation, bool mirror, u8 zorder, u8 pre_mult_alpha,
		u8 global_alpha, enum omap_dss_rotation_type rotation_type,
		bool replication, const struct omap_video_timings *mgr_timings,
		bool mem_to_mem)
{
	bool five_taps = true;
	bool fieldmode = false;
	int r, cconv = 0;
	unsigned offset0, offset1;
	s32 row_inc;
	s32 pix_inc;
	u16 frame_width, frame_height;
	unsigned int field_offset = 0;
	u16 in_height = height;
	u16 in_width = width;
	int x_predecim = 1, y_predecim = 1;
	bool ilace = mgr_timings->interlace;
	unsigned long pclk = dispc_plane_pclk_rate(plane);
	unsigned long lclk = dispc_plane_lclk_rate(plane);

	if (paddr == 0 && rotation_type != OMAP_DSS_ROT_TILER)
		return -EINVAL;

	switch (color_mode) {
	case OMAP_DSS_COLOR_YUV2:
	case OMAP_DSS_COLOR_UYVY:
	case OMAP_DSS_COLOR_NV12:
		if (in_width & 1) {
			DSSERR("input width %d is not even for YUV format\n",
				in_width);
			return -EINVAL;
		}
		break;

	default:
		break;
	}

	out_width = out_width == 0 ? width : out_width;
	out_height = out_height == 0 ? height : out_height;

	if (ilace && height == out_height)
		fieldmode = true;

	if (ilace) {
		if (fieldmode)
			in_height /= 2;
		pos_y /= 2;
		out_height /= 2;

		DSSDBG("adjusting for ilace: height %d, pos_y %d, "
			"out_height %d\n", in_height, pos_y,
			out_height);
	}

	if (!dss_feat_color_mode_supported(plane, color_mode))
		return -EINVAL;

	r = dispc_ovl_calc_scaling(pclk, lclk, caps, mgr_timings, in_width,
			in_height, out_width, out_height, color_mode,
			&five_taps, &x_predecim, &y_predecim, pos_x,
			rotation_type, mem_to_mem);
	if (r)
		return r;

	in_width = in_width / x_predecim;
	in_height = in_height / y_predecim;

	if (x_predecim > 1 || y_predecim > 1)
		DSSDBG("predecimation %d x %x, new input size %d x %d\n",
			x_predecim, y_predecim, in_width, in_height);

	switch (color_mode) {
	case OMAP_DSS_COLOR_YUV2:
	case OMAP_DSS_COLOR_UYVY:
	case OMAP_DSS_COLOR_NV12:
		if (in_width & 1) {
			DSSDBG("predecimated input width is not even for YUV format\n");
			DSSDBG("adjusting input width %d -> %d\n",
				in_width, in_width & ~1);

			in_width &= ~1;
		}
		break;

	default:
		break;
	}

	if (color_mode == OMAP_DSS_COLOR_YUV2 ||
			color_mode == OMAP_DSS_COLOR_UYVY ||
			color_mode == OMAP_DSS_COLOR_NV12)
		cconv = 1;

	if (ilace && !fieldmode) {
		/*
		 * when downscaling the bottom field may have to start several
		 * source lines below the top field. Unfortunately ACCUI
		 * registers will only hold the fractional part of the offset
		 * so the integer part must be added to the base address of the
		 * bottom field.
		 */
		if (!in_height || in_height == out_height)
			field_offset = 0;
		else
			field_offset = in_height / out_height / 2;
	}

	/* Fields are independent but interleaved in memory. */
	if (fieldmode)
		field_offset = 1;

	offset0 = 0;
	offset1 = 0;
	row_inc = 0;
	pix_inc = 0;

	if (plane == OMAP_DSS_WB) {
		frame_width = out_width;
		frame_height = out_height;
	} else {
		frame_width = in_width;
		frame_height = height;
	}

	if (rotation_type == OMAP_DSS_ROT_TILER)
		calc_tiler_rotation_offset(screen_width, frame_width,
				color_mode, fieldmode, field_offset,
				&offset0, &offset1, &row_inc, &pix_inc,
				x_predecim, y_predecim);
	else if (rotation_type == OMAP_DSS_ROT_DMA)
		calc_dma_rotation_offset(rotation, mirror, screen_width,
				frame_width, frame_height,
				color_mode, fieldmode, field_offset,
				&offset0, &offset1, &row_inc, &pix_inc,
				x_predecim, y_predecim);
	else
		calc_vrfb_rotation_offset(rotation, mirror,
				screen_width, frame_width, frame_height,
				color_mode, fieldmode, field_offset,
				&offset0, &offset1, &row_inc, &pix_inc,
				x_predecim, y_predecim);

	DSSDBG("offset0 %u, offset1 %u, row_inc %d, pix_inc %d\n",
			offset0, offset1, row_inc, pix_inc);

	dispc_ovl_set_color_mode(plane, color_mode);

	dispc_ovl_configure_burst_type(plane, rotation_type);

	dispc_ovl_set_ba0(plane, paddr + offset0);
	dispc_ovl_set_ba1(plane, paddr + offset1);

	if (OMAP_DSS_COLOR_NV12 == color_mode) {
		dispc_ovl_set_ba0_uv(plane, p_uv_addr + offset0);
		dispc_ovl_set_ba1_uv(plane, p_uv_addr + offset1);
	}

	if (dispc.feat->last_pixel_inc_missing)
		row_inc += pix_inc - 1;

	dispc_ovl_set_row_inc(plane, row_inc);
	dispc_ovl_set_pix_inc(plane, pix_inc);

	DSSDBG("%d,%d %dx%d -> %dx%d\n", pos_x, pos_y, in_width,
			in_height, out_width, out_height);

	dispc_ovl_set_pos(plane, caps, pos_x, pos_y);

	dispc_ovl_set_input_size(plane, in_width, in_height);

	if (caps & OMAP_DSS_OVL_CAP_SCALE) {
		dispc_ovl_set_scaling(plane, in_width, in_height, out_width,
				   out_height, ilace, five_taps, fieldmode,
				   color_mode, rotation);
		dispc_ovl_set_output_size(plane, out_width, out_height);
		dispc_ovl_set_vid_color_conv(plane, cconv);
	}

	dispc_ovl_set_rotation_attrs(plane, rotation, rotation_type, mirror,
			color_mode);

	dispc_ovl_set_zorder(plane, caps, zorder);
	dispc_ovl_set_pre_mult_alpha(plane, caps, pre_mult_alpha);
	dispc_ovl_setup_global_alpha(plane, caps, global_alpha);

	dispc_ovl_enable_replication(plane, caps, replication);

	return 0;
}