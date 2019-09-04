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
struct v4l2_rect {int left; int width; int top; int height; } ;
typedef  enum ccdc_frmfmt { ____Placeholder_ccdc_frmfmt } ccdc_frmfmt ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CCDC_FRMFMT_INTERLACED ; 
 int /*<<< orphan*/  LNH ; 
 int /*<<< orphan*/  LNV ; 
 int NUM_LINES_VER ; 
 int NUM_PX_HOR_MASK ; 
 int /*<<< orphan*/  SLV0 ; 
 int /*<<< orphan*/  SLV1 ; 
 int /*<<< orphan*/  SPH ; 
 int START_PX_HOR_MASK ; 
 int START_VER_ONE_MASK ; 
 int START_VER_TWO_MASK ; 
 int /*<<< orphan*/  VDINT0 ; 
 int /*<<< orphan*/  VDINT1 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__ isif_cfg ; 
 int /*<<< orphan*/  regw (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void isif_setwin(struct v4l2_rect *image_win,
			enum ccdc_frmfmt frm_fmt, int ppc)
{
	int horz_start, horz_nr_pixels;
	int vert_start, vert_nr_lines;
	int mid_img = 0;

	dev_dbg(isif_cfg.dev, "\nStarting isif_setwin...");
	/*
	 * ppc - per pixel count. indicates how many pixels per cell
	 * output to SDRAM. example, for ycbcr, it is one y and one c, so 2.
	 * raw capture this is 1
	 */
	horz_start = image_win->left << (ppc - 1);
	horz_nr_pixels = ((image_win->width) << (ppc - 1)) - 1;

	/* Writing the horizontal info into the registers */
	regw(horz_start & START_PX_HOR_MASK, SPH);
	regw(horz_nr_pixels & NUM_PX_HOR_MASK, LNH);
	vert_start = image_win->top;

	if (frm_fmt == CCDC_FRMFMT_INTERLACED) {
		vert_nr_lines = (image_win->height >> 1) - 1;
		vert_start >>= 1;
		/* To account for VD since line 0 doesn't have any data */
		vert_start += 1;
	} else {
		/* To account for VD since line 0 doesn't have any data */
		vert_start += 1;
		vert_nr_lines = image_win->height - 1;
		/* configure VDINT0 and VDINT1 */
		mid_img = vert_start + (image_win->height / 2);
		regw(mid_img, VDINT1);
	}

	regw(0, VDINT0);
	regw(vert_start & START_VER_ONE_MASK, SLV0);
	regw(vert_start & START_VER_TWO_MASK, SLV1);
	regw(vert_nr_lines & NUM_LINES_VER, LNV);
}