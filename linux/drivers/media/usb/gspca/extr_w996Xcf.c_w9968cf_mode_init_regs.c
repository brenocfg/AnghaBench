#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int width; int height; } ;
struct TYPE_5__ {size_t curr_mode; scalar_t__ empty_packet; TYPE_1__ pixfmt; } ;
struct sd {scalar_t__ sensor; TYPE_2__ gspca_dev; int /*<<< orphan*/  jpegqual; int /*<<< orphan*/  jpeg_hdr; } ;
struct TYPE_6__ {scalar_t__ pixelformat; } ;

/* Variables and functions */
 scalar_t__ SEN_OV7620 ; 
 scalar_t__ V4L2_PIX_FMT_JPEG ; 
 int /*<<< orphan*/  jpeg_define (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  jpeg_set_qual (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_w (struct sd*,int,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_g_ctrl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_ctrl_grab (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  w9968cf_set_crop_window (struct sd*) ; 
 int /*<<< orphan*/  w9968cf_upload_quantizationtables (struct sd*) ; 
 TYPE_3__* w9968cf_vga_mode ; 

__attribute__((used)) static void w9968cf_mode_init_regs(struct sd *sd)
{
	int val, vs_polarity, hs_polarity;

	w9968cf_set_crop_window(sd);

	reg_w(sd, 0x14, sd->gspca_dev.pixfmt.width);
	reg_w(sd, 0x15, sd->gspca_dev.pixfmt.height);

	/* JPEG width & height */
	reg_w(sd, 0x30, sd->gspca_dev.pixfmt.width);
	reg_w(sd, 0x31, sd->gspca_dev.pixfmt.height);

	/* Y & UV frame buffer strides (in WORD) */
	if (w9968cf_vga_mode[sd->gspca_dev.curr_mode].pixelformat ==
	    V4L2_PIX_FMT_JPEG) {
		reg_w(sd, 0x2c, sd->gspca_dev.pixfmt.width / 2);
		reg_w(sd, 0x2d, sd->gspca_dev.pixfmt.width / 4);
	} else
		reg_w(sd, 0x2c, sd->gspca_dev.pixfmt.width);

	reg_w(sd, 0x00, 0xbf17); /* reset everything */
	reg_w(sd, 0x00, 0xbf10); /* normal operation */

	/* Transfer size in WORDS (for UYVY format only) */
	val = sd->gspca_dev.pixfmt.width * sd->gspca_dev.pixfmt.height;
	reg_w(sd, 0x3d, val & 0xffff); /* low bits */
	reg_w(sd, 0x3e, val >> 16);    /* high bits */

	if (w9968cf_vga_mode[sd->gspca_dev.curr_mode].pixelformat ==
	    V4L2_PIX_FMT_JPEG) {
		/* We may get called multiple times (usb isoc bw negotiat.) */
		jpeg_define(sd->jpeg_hdr, sd->gspca_dev.pixfmt.height,
			    sd->gspca_dev.pixfmt.width, 0x22); /* JPEG 420 */
		jpeg_set_qual(sd->jpeg_hdr, v4l2_ctrl_g_ctrl(sd->jpegqual));
		w9968cf_upload_quantizationtables(sd);
		v4l2_ctrl_grab(sd->jpegqual, true);
	}

	/* Video Capture Control Register */
	if (sd->sensor == SEN_OV7620) {
		/* Seems to work around a bug in the image sensor */
		vs_polarity = 1;
		hs_polarity = 1;
	} else {
		vs_polarity = 1;
		hs_polarity = 0;
	}

	val = (vs_polarity << 12) | (hs_polarity << 11);

	/* NOTE: We may not have enough memory to do double buffering while
	   doing compression (amount of memory differs per model cam).
	   So we use the second image buffer also as jpeg stream buffer
	   (see w9968cf_init), and disable double buffering. */
	if (w9968cf_vga_mode[sd->gspca_dev.curr_mode].pixelformat ==
	    V4L2_PIX_FMT_JPEG) {
		/* val |= 0x0002; YUV422P */
		val |= 0x0003; /* YUV420P */
	} else
		val |= 0x0080; /* Enable HW double buffering */

	/* val |= 0x0020; enable clamping */
	/* val |= 0x0008; enable (1-2-1) filter */
	/* val |= 0x000c; enable (2-3-6-3-2) filter */

	val |= 0x8000; /* capt. enable */

	reg_w(sd, 0x16, val);

	sd->gspca_dev.empty_packet = 0;
}