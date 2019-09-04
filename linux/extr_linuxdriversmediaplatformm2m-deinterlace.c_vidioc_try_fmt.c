#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int pixelformat; int bytesperline; int width; int sizeimage; int height; } ;
struct TYPE_4__ {TYPE_1__ pix; } ;
struct v4l2_format {TYPE_2__ fmt; } ;
struct deinterlace_fmt {int dummy; } ;

/* Variables and functions */
#define  V4L2_PIX_FMT_YUV420 129 
#define  V4L2_PIX_FMT_YUYV 128 

__attribute__((used)) static int vidioc_try_fmt(struct v4l2_format *f, struct deinterlace_fmt *fmt)
{
	switch (f->fmt.pix.pixelformat) {
	case V4L2_PIX_FMT_YUV420:
		f->fmt.pix.bytesperline = f->fmt.pix.width * 3 / 2;
		break;
	case V4L2_PIX_FMT_YUYV:
	default:
		f->fmt.pix.bytesperline = f->fmt.pix.width * 2;
	}
	f->fmt.pix.sizeimage = f->fmt.pix.height * f->fmt.pix.bytesperline;

	return 0;
}