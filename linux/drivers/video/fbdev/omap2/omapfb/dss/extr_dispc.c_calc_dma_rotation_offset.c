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
typedef  int u8 ;
typedef  unsigned int u16 ;
typedef  int /*<<< orphan*/  s32 ;
typedef  enum omap_color_mode { ____Placeholder_omap_color_mode } omap_color_mode ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  DSSDBG (char*,int,unsigned int,unsigned int,unsigned int) ; 
#define  OMAP_DSS_COLOR_CLUT1 135 
#define  OMAP_DSS_COLOR_CLUT2 134 
#define  OMAP_DSS_COLOR_CLUT4 133 
#define  OMAP_DSS_COLOR_CLUT8 132 
 int OMAP_DSS_COLOR_UYVY ; 
 int OMAP_DSS_COLOR_YUV2 ; 
#define  OMAP_DSS_ROT_0 131 
#define  OMAP_DSS_ROT_180 130 
#define  OMAP_DSS_ROT_270 129 
#define  OMAP_DSS_ROT_90 128 
 int color_mode_to_bpp (int) ; 
 int /*<<< orphan*/  pixinc (int,int) ; 

__attribute__((used)) static void calc_dma_rotation_offset(u8 rotation, bool mirror,
		u16 screen_width,
		u16 width, u16 height,
		enum omap_color_mode color_mode, bool fieldmode,
		unsigned int field_offset,
		unsigned *offset0, unsigned *offset1,
		s32 *row_inc, s32 *pix_inc, int x_predecim, int y_predecim)
{
	u8 ps;
	u16 fbw, fbh;

	/* FIXME CLUT formats */
	switch (color_mode) {
	case OMAP_DSS_COLOR_CLUT1:
	case OMAP_DSS_COLOR_CLUT2:
	case OMAP_DSS_COLOR_CLUT4:
	case OMAP_DSS_COLOR_CLUT8:
		BUG();
		return;
	default:
		ps = color_mode_to_bpp(color_mode) / 8;
		break;
	}

	DSSDBG("calc_rot(%d): scrw %d, %dx%d\n", rotation, screen_width,
			width, height);

	/* width & height are overlay sizes, convert to fb sizes */

	if (rotation == OMAP_DSS_ROT_0 || rotation == OMAP_DSS_ROT_180) {
		fbw = width;
		fbh = height;
	} else {
		fbw = height;
		fbh = width;
	}

	/*
	 * field 0 = even field = bottom field
	 * field 1 = odd field = top field
	 */
	switch (rotation + mirror * 4) {
	case OMAP_DSS_ROT_0:
		*offset1 = 0;
		if (field_offset)
			*offset0 = *offset1 + field_offset * screen_width * ps;
		else
			*offset0 = *offset1;
		*row_inc = pixinc(1 +
			(y_predecim * screen_width - fbw * x_predecim) +
			(fieldmode ? screen_width : 0),	ps);
		if (color_mode == OMAP_DSS_COLOR_YUV2 ||
			color_mode == OMAP_DSS_COLOR_UYVY)
			*pix_inc = pixinc(x_predecim, 2 * ps);
		else
			*pix_inc = pixinc(x_predecim, ps);
		break;
	case OMAP_DSS_ROT_90:
		*offset1 = screen_width * (fbh - 1) * ps;
		if (field_offset)
			*offset0 = *offset1 + field_offset * ps;
		else
			*offset0 = *offset1;
		*row_inc = pixinc(screen_width * (fbh * x_predecim - 1) +
				y_predecim + (fieldmode ? 1 : 0), ps);
		*pix_inc = pixinc(-x_predecim * screen_width, ps);
		break;
	case OMAP_DSS_ROT_180:
		*offset1 = (screen_width * (fbh - 1) + fbw - 1) * ps;
		if (field_offset)
			*offset0 = *offset1 - field_offset * screen_width * ps;
		else
			*offset0 = *offset1;
		*row_inc = pixinc(-1 -
			(y_predecim * screen_width - fbw * x_predecim) -
			(fieldmode ? screen_width : 0),	ps);
		if (color_mode == OMAP_DSS_COLOR_YUV2 ||
			color_mode == OMAP_DSS_COLOR_UYVY)
			*pix_inc = pixinc(-x_predecim, 2 * ps);
		else
			*pix_inc = pixinc(-x_predecim, ps);
		break;
	case OMAP_DSS_ROT_270:
		*offset1 = (fbw - 1) * ps;
		if (field_offset)
			*offset0 = *offset1 - field_offset * ps;
		else
			*offset0 = *offset1;
		*row_inc = pixinc(-screen_width * (fbh * x_predecim - 1) -
				y_predecim - (fieldmode ? 1 : 0), ps);
		*pix_inc = pixinc(x_predecim * screen_width, ps);
		break;

	/* mirroring */
	case OMAP_DSS_ROT_0 + 4:
		*offset1 = (fbw - 1) * ps;
		if (field_offset)
			*offset0 = *offset1 + field_offset * screen_width * ps;
		else
			*offset0 = *offset1;
		*row_inc = pixinc(y_predecim * screen_width * 2 - 1 +
				(fieldmode ? screen_width : 0),
				ps);
		if (color_mode == OMAP_DSS_COLOR_YUV2 ||
			color_mode == OMAP_DSS_COLOR_UYVY)
			*pix_inc = pixinc(-x_predecim, 2 * ps);
		else
			*pix_inc = pixinc(-x_predecim, ps);
		break;

	case OMAP_DSS_ROT_90 + 4:
		*offset1 = 0;
		if (field_offset)
			*offset0 = *offset1 + field_offset * ps;
		else
			*offset0 = *offset1;
		*row_inc = pixinc(-screen_width * (fbh * x_predecim - 1) +
				y_predecim + (fieldmode ? 1 : 0),
				ps);
		*pix_inc = pixinc(x_predecim * screen_width, ps);
		break;

	case OMAP_DSS_ROT_180 + 4:
		*offset1 = screen_width * (fbh - 1) * ps;
		if (field_offset)
			*offset0 = *offset1 - field_offset * screen_width * ps;
		else
			*offset0 = *offset1;
		*row_inc = pixinc(1 - y_predecim * screen_width * 2 -
				(fieldmode ? screen_width : 0),
				ps);
		if (color_mode == OMAP_DSS_COLOR_YUV2 ||
			color_mode == OMAP_DSS_COLOR_UYVY)
			*pix_inc = pixinc(x_predecim, 2 * ps);
		else
			*pix_inc = pixinc(x_predecim, ps);
		break;

	case OMAP_DSS_ROT_270 + 4:
		*offset1 = (screen_width * (fbh - 1) + fbw - 1) * ps;
		if (field_offset)
			*offset0 = *offset1 - field_offset * ps;
		else
			*offset0 = *offset1;
		*row_inc = pixinc(screen_width * (fbh * x_predecim - 1) -
				y_predecim - (fieldmode ? 1 : 0),
				ps);
		*pix_inc = pixinc(-x_predecim * screen_width, ps);
		break;

	default:
		BUG();
		return;
	}
}