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
struct TYPE_4__ {TYPE_1__* queue; } ;
struct vivid_dev {int stream_sliced_vbi_cap; TYPE_2__ vbi_cap_dev; int /*<<< orphan*/  vb_vbi_cap_q; } ;
struct v4l2_format {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VBI_CAPTURE ; 
 scalar_t__ vb2_is_busy (int /*<<< orphan*/ *) ; 
 struct vivid_dev* video_drvdata (struct file*) ; 
 int vidioc_g_fmt_vbi_cap (struct file*,void*,struct v4l2_format*) ; 

int vidioc_s_fmt_vbi_cap(struct file *file, void *priv,
					struct v4l2_format *f)
{
	struct vivid_dev *dev = video_drvdata(file);
	int ret = vidioc_g_fmt_vbi_cap(file, priv, f);

	if (ret)
		return ret;
	if (dev->stream_sliced_vbi_cap && vb2_is_busy(&dev->vb_vbi_cap_q))
		return -EBUSY;
	dev->stream_sliced_vbi_cap = false;
	dev->vbi_cap_dev.queue->type = V4L2_BUF_TYPE_VBI_CAPTURE;
	return 0;
}