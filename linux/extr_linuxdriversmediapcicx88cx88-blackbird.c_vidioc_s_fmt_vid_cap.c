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
struct TYPE_5__ {int /*<<< orphan*/  width; int /*<<< orphan*/  height; int /*<<< orphan*/  field; } ;
struct TYPE_6__ {TYPE_2__ pix; } ;
struct v4l2_format {TYPE_3__ fmt; } ;
struct file {int dummy; } ;
struct cx88_core {int /*<<< orphan*/  field; int /*<<< orphan*/  height; int /*<<< orphan*/  width; TYPE_1__* v4ldev; } ;
struct cx8802_dev {int /*<<< orphan*/  vb2_mpegq; struct cx88_core* core; } ;
struct TYPE_4__ {int /*<<< orphan*/  vb2_vbiq; int /*<<< orphan*/  vb2_vidq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX2341X_ENC_SET_FRAME_SIZE ; 
 int EBUSY ; 
 int /*<<< orphan*/  blackbird_api_cmd (struct cx8802_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx88_set_scale (struct cx88_core*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vb2_is_busy (int /*<<< orphan*/ *) ; 
 struct cx8802_dev* video_drvdata (struct file*) ; 
 int /*<<< orphan*/  vidioc_try_fmt_vid_cap (struct file*,void*,struct v4l2_format*) ; 

__attribute__((used)) static int vidioc_s_fmt_vid_cap(struct file *file, void *priv,
				struct v4l2_format *f)
{
	struct cx8802_dev *dev = video_drvdata(file);
	struct cx88_core  *core = dev->core;

	if (vb2_is_busy(&dev->vb2_mpegq))
		return -EBUSY;
	if (core->v4ldev && (vb2_is_busy(&core->v4ldev->vb2_vidq) ||
			     vb2_is_busy(&core->v4ldev->vb2_vbiq)))
		return -EBUSY;
	vidioc_try_fmt_vid_cap(file, priv, f);
	core->width = f->fmt.pix.width;
	core->height = f->fmt.pix.height;
	core->field = f->fmt.pix.field;
	cx88_set_scale(core, f->fmt.pix.width, f->fmt.pix.height,
		       f->fmt.pix.field);
	blackbird_api_cmd(dev, CX2341X_ENC_SET_FRAME_SIZE, 2, 0,
			  f->fmt.pix.height, f->fmt.pix.width);
	return 0;
}