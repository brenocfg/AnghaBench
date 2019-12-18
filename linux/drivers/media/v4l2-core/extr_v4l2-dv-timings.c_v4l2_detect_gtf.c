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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct v4l2_fract {int numerator; int denominator; } ;
struct TYPE_2__ {int width; int height; int hfrontporch; int vfrontporch; int hsync; unsigned int vsync; int hbackporch; unsigned int vbackporch; unsigned int il_vbackporch; int il_vfrontporch; unsigned int il_vsync; int pixelclock; int /*<<< orphan*/  flags; int /*<<< orphan*/  standards; int /*<<< orphan*/  interlaced; scalar_t__ polarities; } ;
struct v4l2_dv_timings {TYPE_1__ bt; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int GTF_CELL_GRAN ; 
 int GTF_D_C_PRIME ; 
 int GTF_D_M_PRIME ; 
 unsigned int GTF_MIN_VSYNC_BP ; 
 int GTF_PXL_CLK_GRAN ; 
 int GTF_S_C_PRIME ; 
 int GTF_S_M_PRIME ; 
 int GTF_V_FP ; 
 int /*<<< orphan*/  V4L2_DV_BT_656_1120 ; 
 int /*<<< orphan*/  V4L2_DV_BT_STD_GTF ; 
 int /*<<< orphan*/  V4L2_DV_FL_HALF_LINE ; 
 int /*<<< orphan*/  V4L2_DV_FL_REDUCED_BLANKING ; 
 scalar_t__ V4L2_DV_HSYNC_POS_POL ; 
 int /*<<< orphan*/  V4L2_DV_INTERLACED ; 
 int /*<<< orphan*/  V4L2_DV_PROGRESSIVE ; 
 scalar_t__ V4L2_DV_VSYNC_POS_POL ; 
 int div_u64 (int,scalar_t__) ; 

bool v4l2_detect_gtf(unsigned frame_height,
		unsigned hfreq,
		unsigned vsync,
		u32 polarities,
		bool interlaced,
		struct v4l2_fract aspect,
		struct v4l2_dv_timings *fmt)
{
	int pix_clk;
	int  v_fp, v_bp, h_fp, hsync;
	int frame_width, image_height, image_width;
	bool default_gtf;
	int h_blank;

	if (vsync != 3)
		return false;

	if (polarities == V4L2_DV_VSYNC_POS_POL)
		default_gtf = true;
	else if (polarities == V4L2_DV_HSYNC_POS_POL)
		default_gtf = false;
	else
		return false;

	if (hfreq == 0)
		return false;

	/* Vertical */
	v_fp = GTF_V_FP;
	v_bp = (GTF_MIN_VSYNC_BP * hfreq + 500000) / 1000000 - vsync;
	if (interlaced)
		image_height = (frame_height - 2 * v_fp - 2 * vsync - 2 * v_bp) & ~0x1;
	else
		image_height = (frame_height - v_fp - vsync - v_bp + 1) & ~0x1;

	if (image_height < 0)
		return false;

	if (aspect.numerator == 0 || aspect.denominator == 0) {
		aspect.numerator = 16;
		aspect.denominator = 9;
	}
	image_width = ((image_height * aspect.numerator) / aspect.denominator);
	image_width = (image_width + GTF_CELL_GRAN/2) & ~(GTF_CELL_GRAN - 1);

	/* Horizontal */
	if (default_gtf) {
		u64 num;
		u32 den;

		num = ((image_width * GTF_D_C_PRIME * (u64)hfreq) -
		      ((u64)image_width * GTF_D_M_PRIME * 1000));
		den = (hfreq * (100 - GTF_D_C_PRIME) + GTF_D_M_PRIME * 1000) *
		      (2 * GTF_CELL_GRAN);
		h_blank = div_u64((num + (den >> 1)), den);
		h_blank *= (2 * GTF_CELL_GRAN);
	} else {
		u64 num;
		u32 den;

		num = ((image_width * GTF_S_C_PRIME * (u64)hfreq) -
		      ((u64)image_width * GTF_S_M_PRIME * 1000));
		den = (hfreq * (100 - GTF_S_C_PRIME) + GTF_S_M_PRIME * 1000) *
		      (2 * GTF_CELL_GRAN);
		h_blank = div_u64((num + (den >> 1)), den);
		h_blank *= (2 * GTF_CELL_GRAN);
	}

	frame_width = image_width + h_blank;

	pix_clk = (image_width + h_blank) * hfreq;
	pix_clk = pix_clk / GTF_PXL_CLK_GRAN * GTF_PXL_CLK_GRAN;

	hsync = (frame_width * 8 + 50) / 100;
	hsync = ((hsync + GTF_CELL_GRAN / 2) / GTF_CELL_GRAN) * GTF_CELL_GRAN;

	h_fp = h_blank / 2 - hsync;

	fmt->type = V4L2_DV_BT_656_1120;
	fmt->bt.polarities = polarities;
	fmt->bt.width = image_width;
	fmt->bt.height = image_height;
	fmt->bt.hfrontporch = h_fp;
	fmt->bt.vfrontporch = v_fp;
	fmt->bt.hsync = hsync;
	fmt->bt.vsync = vsync;
	fmt->bt.hbackporch = frame_width - image_width - h_fp - hsync;

	if (!interlaced) {
		fmt->bt.vbackporch = frame_height - image_height - v_fp - vsync;
		fmt->bt.interlaced = V4L2_DV_PROGRESSIVE;
	} else {
		fmt->bt.vbackporch = (frame_height - image_height - 2 * v_fp -
				      2 * vsync) / 2;
		fmt->bt.il_vbackporch = frame_height - image_height - 2 * v_fp -
					2 * vsync - fmt->bt.vbackporch;
		fmt->bt.il_vfrontporch = v_fp;
		fmt->bt.il_vsync = vsync;
		fmt->bt.flags |= V4L2_DV_FL_HALF_LINE;
		fmt->bt.interlaced = V4L2_DV_INTERLACED;
	}

	fmt->bt.pixelclock = pix_clk;
	fmt->bt.standards = V4L2_DV_BT_STD_GTF;

	if (!default_gtf)
		fmt->bt.flags |= V4L2_DV_FL_REDUCED_BLANKING;

	return true;
}