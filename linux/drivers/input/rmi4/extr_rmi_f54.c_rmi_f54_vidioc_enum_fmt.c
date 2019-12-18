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
struct v4l2_fmtdesc {scalar_t__ type; int /*<<< orphan*/  pixelformat; scalar_t__ index; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pixelformat; } ;
struct f54_data {TYPE_1__ format; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 struct f54_data* video_drvdata (struct file*) ; 

__attribute__((used)) static int rmi_f54_vidioc_enum_fmt(struct file *file, void *priv,
				   struct v4l2_fmtdesc *fmt)
{
	struct f54_data *f54 = video_drvdata(file);

	if (fmt->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return -EINVAL;

	if (fmt->index)
		return -EINVAL;

	fmt->pixelformat = f54->format.pixelformat;

	return 0;
}