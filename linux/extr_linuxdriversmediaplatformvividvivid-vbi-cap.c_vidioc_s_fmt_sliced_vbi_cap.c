#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* queue; } ;
struct vivid_dev {int stream_sliced_vbi_cap; TYPE_2__ vbi_cap_dev; int /*<<< orphan*/  service_set_cap; int /*<<< orphan*/  vb_vbi_cap_q; } ;
struct v4l2_sliced_vbi_format {int /*<<< orphan*/  service_set; } ;
struct TYPE_6__ {struct v4l2_sliced_vbi_format sliced; } ;
struct v4l2_format {TYPE_3__ fmt; } ;
struct file {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_SLICED_VBI_CAPTURE ; 
 scalar_t__ vb2_is_busy (int /*<<< orphan*/ *) ; 
 struct vivid_dev* video_drvdata (struct file*) ; 
 int vidioc_try_fmt_sliced_vbi_cap (struct file*,void*,struct v4l2_format*) ; 

int vidioc_s_fmt_sliced_vbi_cap(struct file *file, void *fh, struct v4l2_format *fmt)
{
	struct vivid_dev *dev = video_drvdata(file);
	struct v4l2_sliced_vbi_format *vbi = &fmt->fmt.sliced;
	int ret = vidioc_try_fmt_sliced_vbi_cap(file, fh, fmt);

	if (ret)
		return ret;
	if (!dev->stream_sliced_vbi_cap && vb2_is_busy(&dev->vb_vbi_cap_q))
		return -EBUSY;
	dev->service_set_cap = vbi->service_set;
	dev->stream_sliced_vbi_cap = true;
	dev->vbi_cap_dev.queue->type = V4L2_BUF_TYPE_SLICED_VBI_CAPTURE;
	return 0;
}