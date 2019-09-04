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
typedef  unsigned int u8 ;
typedef  scalar_t__ u32 ;
typedef  int u16 ;
typedef  int /*<<< orphan*/  s32 ;
typedef  enum omap_dss_rotation_type { ____Placeholder_omap_dss_rotation_type } omap_dss_rotation_type ;

/* Variables and functions */
 scalar_t__ DRM_FORMAT_UYVY ; 
 scalar_t__ DRM_FORMAT_YUYV ; 
 int /*<<< orphan*/  DSSDBG (char*,int,int) ; 
 int OMAP_DSS_ROT_TILER ; 
 int color_mode_to_bpp (scalar_t__) ; 
 scalar_t__ drm_rotation_90_or_270 (unsigned int) ; 
 int /*<<< orphan*/  pixinc (int,unsigned int) ; 

__attribute__((used)) static void calc_offset(u16 screen_width, u16 width,
		u32 fourcc, bool fieldmode, unsigned int field_offset,
		unsigned int *offset0, unsigned int *offset1,
		s32 *row_inc, s32 *pix_inc, int x_predecim, int y_predecim,
		enum omap_dss_rotation_type rotation_type, u8 rotation)
{
	u8 ps;

	ps = color_mode_to_bpp(fourcc) / 8;

	DSSDBG("scrw %d, width %d\n", screen_width, width);

	if (rotation_type == OMAP_DSS_ROT_TILER &&
	    (fourcc == DRM_FORMAT_UYVY || fourcc == DRM_FORMAT_YUYV) &&
	    drm_rotation_90_or_270(rotation)) {
		/*
		 * HACK: ROW_INC needs to be calculated with TILER units.
		 * We get such 'screen_width' that multiplying it with the
		 * YUV422 pixel size gives the correct TILER container width.
		 * However, 'width' is in pixels and multiplying it with YUV422
		 * pixel size gives incorrect result. We thus multiply it here
		 * with 2 to match the 32 bit TILER unit size.
		 */
		width *= 2;
	}

	/*
	 * field 0 = even field = bottom field
	 * field 1 = odd field = top field
	 */
	*offset0 = field_offset * screen_width * ps;
	*offset1 = 0;

	*row_inc = pixinc(1 + (y_predecim * screen_width - width * x_predecim) +
			(fieldmode ? screen_width : 0), ps);
	if (fourcc == DRM_FORMAT_YUYV || fourcc == DRM_FORMAT_UYVY)
		*pix_inc = pixinc(x_predecim, 2 * ps);
	else
		*pix_inc = pixinc(x_predecim, ps);
}