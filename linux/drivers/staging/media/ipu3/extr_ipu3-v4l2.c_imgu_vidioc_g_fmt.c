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
struct v4l2_format {int /*<<< orphan*/  fmt; } ;
struct TYPE_2__ {int /*<<< orphan*/  fmt; } ;
struct imgu_video_device {TYPE_1__ vdev_fmt; } ;
struct file {int dummy; } ;

/* Variables and functions */
 struct imgu_video_device* file_to_intel_imgu_node (struct file*) ; 

__attribute__((used)) static int imgu_vidioc_g_fmt(struct file *file, void *fh,
			     struct v4l2_format *f)
{
	struct imgu_video_device *node = file_to_intel_imgu_node(file);

	f->fmt = node->vdev_fmt.fmt;

	return 0;
}