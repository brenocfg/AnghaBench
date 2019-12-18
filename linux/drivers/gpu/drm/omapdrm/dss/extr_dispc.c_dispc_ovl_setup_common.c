#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct videomode {int flags; unsigned long pixelclock; } ;
struct drm_format_info {scalar_t__ is_yuv; } ;
struct dispc_device {TYPE_1__* feat; } ;
typedef  int s32 ;
typedef  enum omap_plane_id { ____Placeholder_omap_plane_id } omap_plane_id ;
typedef  enum omap_overlay_caps { ____Placeholder_omap_overlay_caps } omap_overlay_caps ;
typedef  enum omap_dss_rotation_type { ____Placeholder_omap_dss_rotation_type } omap_dss_rotation_type ;
struct TYPE_2__ {scalar_t__ last_pixel_inc_missing; scalar_t__ reverse_ilace_field_order; } ;

/* Variables and functions */
 int DISPLAY_FLAGS_INTERLACED ; 
 scalar_t__ DRM_FORMAT_NV12 ; 
 int /*<<< orphan*/  DSSDBG (char*,...) ; 
 int /*<<< orphan*/  DSSERR (char*,int) ; 
 int EINVAL ; 
 int OMAP_DSS_OVL_CAP_SCALE ; 
 int OMAP_DSS_ROT_TILER ; 
 int OMAP_DSS_WB ; 
 int /*<<< orphan*/  calc_offset (int,int,scalar_t__,int,unsigned int,unsigned int*,unsigned int*,int*,int*,int,int,int,int /*<<< orphan*/ ) ; 
 int dispc_ovl_calc_scaling (struct dispc_device*,int,unsigned long,unsigned long,int,struct videomode const*,int,int,int,int,scalar_t__,int*,int*,int*,int,int,int) ; 
 int /*<<< orphan*/  dispc_ovl_color_mode_supported (struct dispc_device*,int,scalar_t__) ; 
 int /*<<< orphan*/  dispc_ovl_configure_burst_type (struct dispc_device*,int,int) ; 
 int /*<<< orphan*/  dispc_ovl_enable_replication (struct dispc_device*,int,int,int) ; 
 int /*<<< orphan*/  dispc_ovl_set_ba0 (struct dispc_device*,int,scalar_t__) ; 
 int /*<<< orphan*/  dispc_ovl_set_ba0_uv (struct dispc_device*,int,scalar_t__) ; 
 int /*<<< orphan*/  dispc_ovl_set_ba1 (struct dispc_device*,int,scalar_t__) ; 
 int /*<<< orphan*/  dispc_ovl_set_ba1_uv (struct dispc_device*,int,scalar_t__) ; 
 int /*<<< orphan*/  dispc_ovl_set_color_mode (struct dispc_device*,int,scalar_t__) ; 
 int /*<<< orphan*/  dispc_ovl_set_input_size (struct dispc_device*,int,int,int) ; 
 int /*<<< orphan*/  dispc_ovl_set_output_size (struct dispc_device*,int,int,int) ; 
 int /*<<< orphan*/  dispc_ovl_set_pix_inc (struct dispc_device*,int,int) ; 
 int /*<<< orphan*/  dispc_ovl_set_pos (struct dispc_device*,int,int,int,int) ; 
 int /*<<< orphan*/  dispc_ovl_set_pre_mult_alpha (struct dispc_device*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dispc_ovl_set_rotation_attrs (struct dispc_device*,int,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  dispc_ovl_set_row_inc (struct dispc_device*,int,int) ; 
 int /*<<< orphan*/  dispc_ovl_set_scaling (struct dispc_device*,int,int,int,int,int,int,int,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dispc_ovl_set_vid_color_conv (struct dispc_device*,int,int) ; 
 int /*<<< orphan*/  dispc_ovl_set_zorder (struct dispc_device*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dispc_ovl_setup_global_alpha (struct dispc_device*,int,int,int /*<<< orphan*/ ) ; 
 unsigned long dispc_plane_lclk_rate (struct dispc_device*,int) ; 
 unsigned long dispc_plane_pclk_rate (struct dispc_device*,int) ; 
 struct drm_format_info* drm_format_info (scalar_t__) ; 
 int /*<<< orphan*/  swap (unsigned int,unsigned int) ; 

__attribute__((used)) static int dispc_ovl_setup_common(struct dispc_device *dispc,
				  enum omap_plane_id plane,
				  enum omap_overlay_caps caps,
				  u32 paddr, u32 p_uv_addr,
				  u16 screen_width, int pos_x, int pos_y,
				  u16 width, u16 height,
				  u16 out_width, u16 out_height,
				  u32 fourcc, u8 rotation, u8 zorder,
				  u8 pre_mult_alpha, u8 global_alpha,
				  enum omap_dss_rotation_type rotation_type,
				  bool replication, const struct videomode *vm,
				  bool mem_to_mem)
{
	bool five_taps = true;
	bool fieldmode = false;
	int r, cconv = 0;
	unsigned int offset0, offset1;
	s32 row_inc;
	s32 pix_inc;
	u16 frame_width;
	unsigned int field_offset = 0;
	u16 in_height = height;
	u16 in_width = width;
	int x_predecim = 1, y_predecim = 1;
	bool ilace = !!(vm->flags & DISPLAY_FLAGS_INTERLACED);
	unsigned long pclk = dispc_plane_pclk_rate(dispc, plane);
	unsigned long lclk = dispc_plane_lclk_rate(dispc, plane);
	const struct drm_format_info *info;

	info = drm_format_info(fourcc);

	/* when setting up WB, dispc_plane_pclk_rate() returns 0 */
	if (plane == OMAP_DSS_WB)
		pclk = vm->pixelclock;

	if (paddr == 0 && rotation_type != OMAP_DSS_ROT_TILER)
		return -EINVAL;

	if (info->is_yuv && (in_width & 1)) {
		DSSERR("input width %d is not even for YUV format\n", in_width);
		return -EINVAL;
	}

	out_width = out_width == 0 ? width : out_width;
	out_height = out_height == 0 ? height : out_height;

	if (plane != OMAP_DSS_WB) {
		if (ilace && height == out_height)
			fieldmode = true;

		if (ilace) {
			if (fieldmode)
				in_height /= 2;
			pos_y /= 2;
			out_height /= 2;

			DSSDBG("adjusting for ilace: height %d, pos_y %d, out_height %d\n",
				in_height, pos_y, out_height);
		}
	}

	if (!dispc_ovl_color_mode_supported(dispc, plane, fourcc))
		return -EINVAL;

	r = dispc_ovl_calc_scaling(dispc, plane, pclk, lclk, caps, vm, in_width,
				   in_height, out_width, out_height, fourcc,
				   &five_taps, &x_predecim, &y_predecim, pos_x,
				   rotation_type, mem_to_mem);
	if (r)
		return r;

	in_width = in_width / x_predecim;
	in_height = in_height / y_predecim;

	if (x_predecim > 1 || y_predecim > 1)
		DSSDBG("predecimation %d x %x, new input size %d x %d\n",
			x_predecim, y_predecim, in_width, in_height);

	if (info->is_yuv && (in_width & 1)) {
		DSSDBG("predecimated input width is not even for YUV format\n");
		DSSDBG("adjusting input width %d -> %d\n",
			in_width, in_width & ~1);

		in_width &= ~1;
	}

	if (info->is_yuv)
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

	if (plane == OMAP_DSS_WB)
		frame_width = out_width;
	else
		frame_width = in_width;

	calc_offset(screen_width, frame_width,
			fourcc, fieldmode, field_offset,
			&offset0, &offset1, &row_inc, &pix_inc,
			x_predecim, y_predecim,
			rotation_type, rotation);

	DSSDBG("offset0 %u, offset1 %u, row_inc %d, pix_inc %d\n",
			offset0, offset1, row_inc, pix_inc);

	dispc_ovl_set_color_mode(dispc, plane, fourcc);

	dispc_ovl_configure_burst_type(dispc, plane, rotation_type);

	if (dispc->feat->reverse_ilace_field_order)
		swap(offset0, offset1);

	dispc_ovl_set_ba0(dispc, plane, paddr + offset0);
	dispc_ovl_set_ba1(dispc, plane, paddr + offset1);

	if (fourcc == DRM_FORMAT_NV12) {
		dispc_ovl_set_ba0_uv(dispc, plane, p_uv_addr + offset0);
		dispc_ovl_set_ba1_uv(dispc, plane, p_uv_addr + offset1);
	}

	if (dispc->feat->last_pixel_inc_missing)
		row_inc += pix_inc - 1;

	dispc_ovl_set_row_inc(dispc, plane, row_inc);
	dispc_ovl_set_pix_inc(dispc, plane, pix_inc);

	DSSDBG("%d,%d %dx%d -> %dx%d\n", pos_x, pos_y, in_width,
			in_height, out_width, out_height);

	dispc_ovl_set_pos(dispc, plane, caps, pos_x, pos_y);

	dispc_ovl_set_input_size(dispc, plane, in_width, in_height);

	if (caps & OMAP_DSS_OVL_CAP_SCALE) {
		dispc_ovl_set_scaling(dispc, plane, in_width, in_height,
				      out_width, out_height, ilace, five_taps,
				      fieldmode, fourcc, rotation);
		dispc_ovl_set_output_size(dispc, plane, out_width, out_height);
		dispc_ovl_set_vid_color_conv(dispc, plane, cconv);
	}

	dispc_ovl_set_rotation_attrs(dispc, plane, rotation, rotation_type,
				     fourcc);

	dispc_ovl_set_zorder(dispc, plane, caps, zorder);
	dispc_ovl_set_pre_mult_alpha(dispc, plane, caps, pre_mult_alpha);
	dispc_ovl_setup_global_alpha(dispc, plane, caps, global_alpha);

	dispc_ovl_enable_replication(dispc, plane, caps, replication);

	return 0;
}