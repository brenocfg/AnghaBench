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
typedef  int u32 ;
struct v4l2_pix_format {int width; int height; int pixelformat; } ;
struct mcam_camera {struct v4l2_pix_format pix_format; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 scalar_t__ REG_U0BAR ; 
 scalar_t__ REG_V0BAR ; 
 scalar_t__ REG_Y0BAR ; 
#define  V4L2_PIX_FMT_YUV420 129 
#define  V4L2_PIX_FMT_YVU420 128 
 scalar_t__ mcam_fmt_is_planar (int) ; 
 int /*<<< orphan*/  mcam_reg_write (struct mcam_camera*,scalar_t__,int) ; 

__attribute__((used)) static void mcam_write_yuv_bases(struct mcam_camera *cam,
				 unsigned frame, dma_addr_t base)
{
	struct v4l2_pix_format *fmt = &cam->pix_format;
	u32 pixel_count = fmt->width * fmt->height;
	dma_addr_t y, u = 0, v = 0;

	y = base;

	switch (fmt->pixelformat) {
	case V4L2_PIX_FMT_YUV420:
		u = y + pixel_count;
		v = u + pixel_count / 4;
		break;
	case V4L2_PIX_FMT_YVU420:
		v = y + pixel_count;
		u = v + pixel_count / 4;
		break;
	default:
		break;
	}

	mcam_reg_write(cam, REG_Y0BAR + frame * 4, y);
	if (mcam_fmt_is_planar(fmt->pixelformat)) {
		mcam_reg_write(cam, REG_U0BAR + frame * 4, u);
		mcam_reg_write(cam, REG_V0BAR + frame * 4, v);
	}
}