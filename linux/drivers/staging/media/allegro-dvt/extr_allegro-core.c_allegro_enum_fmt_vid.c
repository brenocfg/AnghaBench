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
struct v4l2_fmtdesc {int type; int /*<<< orphan*/  pixelformat; scalar_t__ index; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_BUF_TYPE_VIDEO_CAPTURE 129 
#define  V4L2_BUF_TYPE_VIDEO_OUTPUT 128 
 int /*<<< orphan*/  V4L2_PIX_FMT_H264 ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_NV12 ; 

__attribute__((used)) static int allegro_enum_fmt_vid(struct file *file, void *fh,
				struct v4l2_fmtdesc *f)
{
	if (f->index)
		return -EINVAL;
	switch (f->type) {
	case V4L2_BUF_TYPE_VIDEO_OUTPUT:
		f->pixelformat = V4L2_PIX_FMT_NV12;
		break;
	case V4L2_BUF_TYPE_VIDEO_CAPTURE:
		f->pixelformat = V4L2_PIX_FMT_H264;
		break;
	default:
		return -EINVAL;
	}
	return 0;
}