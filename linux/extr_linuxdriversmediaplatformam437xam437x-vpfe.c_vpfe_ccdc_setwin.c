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
struct vpfe_ccdc {int dummy; } ;
struct v4l2_rect {int left; int width; int top; int height; } ;
typedef  enum ccdc_frmfmt { ____Placeholder_ccdc_frmfmt } ccdc_frmfmt ;

/* Variables and functions */
 int CCDC_FRMFMT_INTERLACED ; 
 int /*<<< orphan*/  VPFE_HORZ_INFO ; 
 int VPFE_HORZ_INFO_SPH_SHIFT ; 
 int /*<<< orphan*/  VPFE_VDINT ; 
 int VPFE_VDINT_VDINT0_SHIFT ; 
 int VPFE_VDINT_VDINT1_MASK ; 
 int /*<<< orphan*/  VPFE_VERT_LINES ; 
 int /*<<< orphan*/  VPFE_VERT_START ; 
 int VPFE_VERT_START_SLV0_SHIFT ; 
 int /*<<< orphan*/  vpfe_reg_write (struct vpfe_ccdc*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vpfe_ccdc_setwin(struct vpfe_ccdc *ccdc,
			     struct v4l2_rect *image_win,
			     enum ccdc_frmfmt frm_fmt,
			     int bpp)
{
	int horz_start, horz_nr_pixels;
	int vert_start, vert_nr_lines;
	int val, mid_img;

	/*
	 * ppc - per pixel count. indicates how many pixels per cell
	 * output to SDRAM. example, for ycbcr, it is one y and one c, so 2.
	 * raw capture this is 1
	 */
	horz_start = image_win->left * bpp;
	horz_nr_pixels = (image_win->width * bpp) - 1;
	vpfe_reg_write(ccdc, (horz_start << VPFE_HORZ_INFO_SPH_SHIFT) |
				horz_nr_pixels, VPFE_HORZ_INFO);

	vert_start = image_win->top;

	if (frm_fmt == CCDC_FRMFMT_INTERLACED) {
		vert_nr_lines = (image_win->height >> 1) - 1;
		vert_start >>= 1;
		/* Since first line doesn't have any data */
		vert_start += 1;
		/* configure VDINT0 */
		val = (vert_start << VPFE_VDINT_VDINT0_SHIFT);
	} else {
		/* Since first line doesn't have any data */
		vert_start += 1;
		vert_nr_lines = image_win->height - 1;
		/*
		 * configure VDINT0 and VDINT1. VDINT1 will be at half
		 * of image height
		 */
		mid_img = vert_start + (image_win->height / 2);
		val = (vert_start << VPFE_VDINT_VDINT0_SHIFT) |
				(mid_img & VPFE_VDINT_VDINT1_MASK);
	}

	vpfe_reg_write(ccdc, val, VPFE_VDINT);

	vpfe_reg_write(ccdc, (vert_start << VPFE_VERT_START_SLV0_SHIFT) |
				vert_start, VPFE_VERT_START);
	vpfe_reg_write(ccdc, vert_nr_lines, VPFE_VERT_LINES);
}