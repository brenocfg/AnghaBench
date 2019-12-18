#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct v4l2_fmtdesc {int index; scalar_t__ pixelformat; } ;
struct file {int dummy; } ;
struct TYPE_3__ {scalar_t__ fourcc; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 scalar_t__ V4L2_PIX_FMT_JPEG ; 
 scalar_t__ V4L2_PIX_FMT_MJPEG ; 
 TYPE_1__* formats ; 
 int /*<<< orphan*/  jpeg_enable ; 

__attribute__((used)) static int vidioc_enum_fmt_vid_cap(struct file *file, void *priv,
			       struct v4l2_fmtdesc *f)
{
	int index = f->index;

	if (index >= ARRAY_SIZE(formats))
		return -EINVAL;
	if (!jpeg_enable && ((formats[index].fourcc == V4L2_PIX_FMT_JPEG) ||
			(formats[index].fourcc == V4L2_PIX_FMT_MJPEG)))
		return -EINVAL;
	f->pixelformat = formats[index].fourcc;
	return 0;
}