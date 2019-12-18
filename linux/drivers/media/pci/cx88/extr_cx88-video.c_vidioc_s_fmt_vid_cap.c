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
struct TYPE_5__ {int /*<<< orphan*/  field; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  pixelformat; } ;
struct TYPE_6__ {TYPE_2__ pix; } ;
struct v4l2_format {TYPE_3__ fmt; } ;
struct file {int dummy; } ;
struct cx88_core {int /*<<< orphan*/  field; int /*<<< orphan*/  height; int /*<<< orphan*/  width; TYPE_1__* dvbdev; } ;
struct cx8800_dev {int /*<<< orphan*/  fmt; int /*<<< orphan*/  vb2_vbiq; int /*<<< orphan*/  vb2_vidq; struct cx88_core* core; } ;
struct TYPE_4__ {int /*<<< orphan*/  vb2_mpegq; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  format_by_fourcc (int /*<<< orphan*/ ) ; 
 scalar_t__ vb2_is_busy (int /*<<< orphan*/ *) ; 
 struct cx8800_dev* video_drvdata (struct file*) ; 
 int vidioc_try_fmt_vid_cap (struct file*,void*,struct v4l2_format*) ; 

__attribute__((used)) static int vidioc_s_fmt_vid_cap(struct file *file, void *priv,
				struct v4l2_format *f)
{
	struct cx8800_dev *dev = video_drvdata(file);
	struct cx88_core *core = dev->core;
	int err = vidioc_try_fmt_vid_cap(file, priv, f);

	if (err != 0)
		return err;
	if (vb2_is_busy(&dev->vb2_vidq) || vb2_is_busy(&dev->vb2_vbiq))
		return -EBUSY;
	if (core->dvbdev && vb2_is_busy(&core->dvbdev->vb2_mpegq))
		return -EBUSY;
	dev->fmt = format_by_fourcc(f->fmt.pix.pixelformat);
	core->width = f->fmt.pix.width;
	core->height = f->fmt.pix.height;
	core->field = f->fmt.pix.field;
	return 0;
}