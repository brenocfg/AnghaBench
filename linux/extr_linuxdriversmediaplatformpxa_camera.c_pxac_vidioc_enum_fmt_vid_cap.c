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
struct v4l2_fmtdesc {unsigned int index; int /*<<< orphan*/  pixelformat; } ;
struct pxa_mbus_pixelfmt {int /*<<< orphan*/  fourcc; } ;
struct pxa_camera_dev {TYPE_1__* user_formats; } ;
struct file {int dummy; } ;
struct TYPE_2__ {struct pxa_mbus_pixelfmt* host_fmt; scalar_t__ code; } ;

/* Variables and functions */
 int EINVAL ; 
 struct pxa_camera_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int pxac_vidioc_enum_fmt_vid_cap(struct file *filp, void  *priv,
					struct v4l2_fmtdesc *f)
{
	struct pxa_camera_dev *pcdev = video_drvdata(filp);
	const struct pxa_mbus_pixelfmt *format;
	unsigned int idx;

	for (idx = 0; pcdev->user_formats[idx].code; idx++);
	if (f->index >= idx)
		return -EINVAL;

	format = pcdev->user_formats[f->index].host_fmt;
	f->pixelformat = format->fourcc;
	return 0;
}