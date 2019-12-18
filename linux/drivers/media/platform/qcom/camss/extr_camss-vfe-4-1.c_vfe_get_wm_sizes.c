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
typedef  int u8 ;
typedef  int u16 ;
struct v4l2_pix_format_mplane {int pixelformat; int width; int height; TYPE_1__* plane_fmt; } ;
struct TYPE_2__ {int bytesperline; } ;

/* Variables and functions */
#define  V4L2_PIX_FMT_NV12 131 
#define  V4L2_PIX_FMT_NV16 130 
#define  V4L2_PIX_FMT_NV21 129 
#define  V4L2_PIX_FMT_NV61 128 

__attribute__((used)) static void vfe_get_wm_sizes(struct v4l2_pix_format_mplane *pix, u8 plane,
			     u16 *width, u16 *height, u16 *bytesperline)
{
	switch (pix->pixelformat) {
	case V4L2_PIX_FMT_NV12:
	case V4L2_PIX_FMT_NV21:
		*width = pix->width;
		*height = pix->height;
		*bytesperline = pix->plane_fmt[0].bytesperline;
		if (plane == 1)
			*height /= 2;
		break;
	case V4L2_PIX_FMT_NV16:
	case V4L2_PIX_FMT_NV61:
		*width = pix->width;
		*height = pix->height;
		*bytesperline = pix->plane_fmt[0].bytesperline;
		break;
	}
}