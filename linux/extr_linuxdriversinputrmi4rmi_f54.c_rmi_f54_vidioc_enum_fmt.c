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
struct v4l2_fmtdesc {scalar_t__ type; int index; int /*<<< orphan*/  pixelformat; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  V4L2_TCH_FMT_DELTA_TD08 ; 
 int /*<<< orphan*/  V4L2_TCH_FMT_DELTA_TD16 ; 
 int /*<<< orphan*/  V4L2_TCH_FMT_TU16 ; 

__attribute__((used)) static int rmi_f54_vidioc_enum_fmt(struct file *file, void *priv,
				   struct v4l2_fmtdesc *fmt)
{
	if (fmt->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return -EINVAL;

	switch (fmt->index) {
	case 0:
		fmt->pixelformat = V4L2_TCH_FMT_DELTA_TD16;
		break;

	case 1:
		fmt->pixelformat = V4L2_TCH_FMT_DELTA_TD08;
		break;

	case 2:
		fmt->pixelformat = V4L2_TCH_FMT_TU16;
		break;

	default:
		return -EINVAL;
	}

	return 0;
}