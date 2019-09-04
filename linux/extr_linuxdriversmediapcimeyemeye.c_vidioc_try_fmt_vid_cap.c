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
struct TYPE_3__ {scalar_t__ pixelformat; scalar_t__ field; int width; int height; int bytesperline; int sizeimage; scalar_t__ colorspace; } ;
struct TYPE_4__ {TYPE_1__ pix; } ;
struct v4l2_format {TYPE_2__ fmt; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_FIELD_ANY ; 
 scalar_t__ V4L2_FIELD_NONE ; 
 scalar_t__ V4L2_PIX_FMT_MJPEG ; 
 scalar_t__ V4L2_PIX_FMT_YUYV ; 

__attribute__((used)) static int vidioc_try_fmt_vid_cap(struct file *file, void *fh,
				struct v4l2_format *f)
{
	if (f->fmt.pix.pixelformat != V4L2_PIX_FMT_YUYV &&
	    f->fmt.pix.pixelformat != V4L2_PIX_FMT_MJPEG)
		return -EINVAL;

	if (f->fmt.pix.field != V4L2_FIELD_ANY &&
	    f->fmt.pix.field != V4L2_FIELD_NONE)
		return -EINVAL;

	f->fmt.pix.field = V4L2_FIELD_NONE;

	if (f->fmt.pix.width <= 320) {
		f->fmt.pix.width = 320;
		f->fmt.pix.height = 240;
	} else {
		f->fmt.pix.width = 640;
		f->fmt.pix.height = 480;
	}

	f->fmt.pix.bytesperline = f->fmt.pix.width * 2;
	f->fmt.pix.sizeimage = f->fmt.pix.height *
			       f->fmt.pix.bytesperline;
	f->fmt.pix.colorspace = 0;

	return 0;
}