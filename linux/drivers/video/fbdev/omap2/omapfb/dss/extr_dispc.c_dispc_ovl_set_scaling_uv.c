#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
typedef  enum omap_plane { ____Placeholder_omap_plane } omap_plane ;
typedef  enum omap_color_mode { ____Placeholder_omap_color_mode } omap_color_mode ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  DISPC_COLOR_COMPONENT_UV ; 
 int /*<<< orphan*/  DISPC_OVL_ATTRIBUTES (int) ; 
 int /*<<< orphan*/  DISPC_OVL_ATTRIBUTES2 (int) ; 
 int /*<<< orphan*/  FEAT_HANDLE_UV_SEPARATE ; 
#define  OMAP_DSS_COLOR_NV12 130 
#define  OMAP_DSS_COLOR_UYVY 129 
#define  OMAP_DSS_COLOR_YUV2 128 
 int /*<<< orphan*/  OMAP_DSS_ROT_0 ; 
 int /*<<< orphan*/  OMAP_DSS_ROT_180 ; 
 int OMAP_DSS_WB ; 
 int /*<<< orphan*/  REG_FLD_MOD (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  dispc_ovl_set_accu_uv (int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dispc_ovl_set_scale_param (int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dss_has_feature (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dispc_ovl_set_scaling_uv(enum omap_plane plane,
		u16 orig_width, u16 orig_height,
		u16 out_width, u16 out_height,
		bool ilace, bool five_taps,
		bool fieldmode, enum omap_color_mode color_mode,
		u8 rotation)
{
	int scale_x = out_width != orig_width;
	int scale_y = out_height != orig_height;
	bool chroma_upscale = plane != OMAP_DSS_WB ? true : false;

	if (!dss_has_feature(FEAT_HANDLE_UV_SEPARATE))
		return;
	if ((color_mode != OMAP_DSS_COLOR_YUV2 &&
			color_mode != OMAP_DSS_COLOR_UYVY &&
			color_mode != OMAP_DSS_COLOR_NV12)) {
		/* reset chroma resampling for RGB formats  */
		if (plane != OMAP_DSS_WB)
			REG_FLD_MOD(DISPC_OVL_ATTRIBUTES2(plane), 0, 8, 8);
		return;
	}

	dispc_ovl_set_accu_uv(plane, orig_width, orig_height, out_width,
			out_height, ilace, color_mode, rotation);

	switch (color_mode) {
	case OMAP_DSS_COLOR_NV12:
		if (chroma_upscale) {
			/* UV is subsampled by 2 horizontally and vertically */
			orig_height >>= 1;
			orig_width >>= 1;
		} else {
			/* UV is downsampled by 2 horizontally and vertically */
			orig_height <<= 1;
			orig_width <<= 1;
		}

		break;
	case OMAP_DSS_COLOR_YUV2:
	case OMAP_DSS_COLOR_UYVY:
		/* For YUV422 with 90/270 rotation, we don't upsample chroma */
		if (rotation == OMAP_DSS_ROT_0 ||
				rotation == OMAP_DSS_ROT_180) {
			if (chroma_upscale)
				/* UV is subsampled by 2 horizontally */
				orig_width >>= 1;
			else
				/* UV is downsampled by 2 horizontally */
				orig_width <<= 1;
		}

		/* must use FIR for YUV422 if rotated */
		if (rotation != OMAP_DSS_ROT_0)
			scale_x = scale_y = true;

		break;
	default:
		BUG();
		return;
	}

	if (out_width != orig_width)
		scale_x = true;
	if (out_height != orig_height)
		scale_y = true;

	dispc_ovl_set_scale_param(plane, orig_width, orig_height,
			out_width, out_height, five_taps,
				rotation, DISPC_COLOR_COMPONENT_UV);

	if (plane != OMAP_DSS_WB)
		REG_FLD_MOD(DISPC_OVL_ATTRIBUTES2(plane),
			(scale_x || scale_y) ? 1 : 0, 8, 8);

	/* set H scaling */
	REG_FLD_MOD(DISPC_OVL_ATTRIBUTES(plane), scale_x ? 1 : 0, 5, 5);
	/* set V scaling */
	REG_FLD_MOD(DISPC_OVL_ATTRIBUTES(plane), scale_y ? 1 : 0, 6, 6);
}