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
typedef  int u32 ;
struct v4l2_rect {int height; int top; int width; int left; } ;
struct v4l2_pix_format {int height; int width; } ;
struct sh_vou_fmt {int pkf; int yf; int rgb; int /*<<< orphan*/  pfmt; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct sh_vou_device {int std; TYPE_1__ v4l2_dev; struct v4l2_pix_format pix; struct v4l2_rect rect; } ;

/* Variables and functions */
 int V4L2_STD_525_60 ; 
 int /*<<< orphan*/  VOUDFR ; 
 int /*<<< orphan*/  VOUDPR ; 
 int /*<<< orphan*/  VOUDSR ; 
 int /*<<< orphan*/  VOUISR ; 
 int /*<<< orphan*/  VOUVCR ; 
 int /*<<< orphan*/  VOUVPR ; 
 unsigned int VOU_MAX_IMAGE_WIDTH ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,...) ; 
 int /*<<< orphan*/  sh_vou_reg_ab_write (struct sh_vou_device*,int /*<<< orphan*/ ,int) ; 
 struct sh_vou_fmt* vou_fmt ; 
 int* vou_scale_h_fld ; 
 int* vou_scale_v_fld ; 

__attribute__((used)) static void sh_vou_configure_geometry(struct sh_vou_device *vou_dev,
				      int pix_idx, int w_idx, int h_idx)
{
	struct sh_vou_fmt *fmt = vou_fmt + pix_idx;
	unsigned int black_left, black_top, width_max,
		frame_in_height, frame_out_height, frame_out_top;
	struct v4l2_rect *rect = &vou_dev->rect;
	struct v4l2_pix_format *pix = &vou_dev->pix;
	u32 vouvcr = 0, dsr_h, dsr_v;

	if (vou_dev->std & V4L2_STD_525_60) {
		width_max = 858;
		/* height_max = 262; */
	} else {
		width_max = 864;
		/* height_max = 312; */
	}

	frame_in_height = pix->height / 2;
	frame_out_height = rect->height / 2;
	frame_out_top = rect->top / 2;

	/*
	 * Cropping scheme: max useful image is 720x480, and the total video
	 * area is 858x525 (NTSC) or 864x625 (PAL). AK8813 / 8814 starts
	 * sampling data beginning with fixed 276th (NTSC) / 288th (PAL) clock,
	 * of which the first 33 / 25 clocks HSYNC must be held active. This
	 * has to be configured in CR[HW]. 1 pixel equals 2 clock periods.
	 * This gives CR[HW] = 16 / 12, VPR[HVP] = 138 / 144, which gives
	 * exactly 858 - 138 = 864 - 144 = 720! We call the out-of-display area,
	 * beyond DSR, specified on the left and top by the VPR register "black
	 * pixels" and out-of-image area (DPR) "background pixels." We fix VPR
	 * at 138 / 144 : 20, because that's the HSYNC timing, that our first
	 * client requires, and that's exactly what leaves us 720 pixels for the
	 * image; we leave VPR[VVP] at default 20 for now, because the client
	 * doesn't seem to have any special requirements for it. Otherwise we
	 * could also set it to max - 240 = 22 / 72. Thus VPR depends only on
	 * the selected standard, and DPR and DSR are selected according to
	 * cropping. Q: how does the client detect the first valid line? Does
	 * HSYNC stay inactive during invalid (black) lines?
	 */
	black_left = width_max - VOU_MAX_IMAGE_WIDTH;
	black_top = 20;

	dsr_h = rect->width + rect->left;
	dsr_v = frame_out_height + frame_out_top;

	dev_dbg(vou_dev->v4l2_dev.dev,
		"image %ux%u, black %u:%u, offset %u:%u, display %ux%u\n",
		pix->width, frame_in_height, black_left, black_top,
		rect->left, frame_out_top, dsr_h, dsr_v);

	/* VOUISR height - half of a frame height in frame mode */
	sh_vou_reg_ab_write(vou_dev, VOUISR, (pix->width << 16) | frame_in_height);
	sh_vou_reg_ab_write(vou_dev, VOUVPR, (black_left << 16) | black_top);
	sh_vou_reg_ab_write(vou_dev, VOUDPR, (rect->left << 16) | frame_out_top);
	sh_vou_reg_ab_write(vou_dev, VOUDSR, (dsr_h << 16) | dsr_v);

	/*
	 * if necessary, we could set VOUHIR to
	 * max(black_left + dsr_h, width_max) here
	 */

	if (w_idx)
		vouvcr |= (1 << 15) | (vou_scale_h_fld[w_idx - 1] << 4);
	if (h_idx)
		vouvcr |= (1 << 14) | vou_scale_v_fld[h_idx - 1];

	dev_dbg(vou_dev->v4l2_dev.dev, "0x%08x: scaling 0x%x\n",
		fmt->pfmt, vouvcr);

	/* To produce a colour bar for testing set bit 23 of VOUVCR */
	sh_vou_reg_ab_write(vou_dev, VOUVCR, vouvcr);
	sh_vou_reg_ab_write(vou_dev, VOUDFR,
			    fmt->pkf | (fmt->yf << 8) | (fmt->rgb << 16));
}