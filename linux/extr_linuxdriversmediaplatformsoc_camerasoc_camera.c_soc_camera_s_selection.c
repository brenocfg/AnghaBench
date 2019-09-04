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
struct TYPE_4__ {scalar_t__ width; scalar_t__ height; } ;
struct v4l2_selection {scalar_t__ type; scalar_t__ target; TYPE_2__ r; } ;
struct soc_camera_host {TYPE_1__* ops; } ;
struct soc_camera_device {scalar_t__ user_width; scalar_t__ user_height; struct file* streamer; int /*<<< orphan*/  vb2_vidq; int /*<<< orphan*/  parent; } ;
struct file {struct soc_camera_device* private_data; } ;
struct TYPE_3__ {int (* set_liveselection ) (struct soc_camera_device*,struct v4l2_selection*) ;int (* set_selection ) (struct soc_camera_device*,struct v4l2_selection*) ;} ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 scalar_t__ V4L2_SEL_TGT_COMPOSE ; 
 scalar_t__ V4L2_SEL_TGT_CROP ; 
 int stub1 (struct soc_camera_device*,struct v4l2_selection*) ; 
 int stub2 (struct soc_camera_device*,struct v4l2_selection*) ; 
 struct soc_camera_host* to_soc_camera_host (int /*<<< orphan*/ ) ; 
 scalar_t__ vb2_is_streaming (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int soc_camera_s_selection(struct file *file, void *fh,
				  struct v4l2_selection *s)
{
	struct soc_camera_device *icd = file->private_data;
	struct soc_camera_host *ici = to_soc_camera_host(icd->parent);
	int ret;

	/* In all these cases cropping emulation will not help */
	if (s->type != V4L2_BUF_TYPE_VIDEO_CAPTURE ||
	    (s->target != V4L2_SEL_TGT_COMPOSE &&
	     s->target != V4L2_SEL_TGT_CROP))
		return -EINVAL;

	if (s->target == V4L2_SEL_TGT_COMPOSE) {
		/* No output size change during a running capture! */
		if (vb2_is_streaming(&icd->vb2_vidq) &&
		    (icd->user_width != s->r.width ||
		     icd->user_height != s->r.height))
			return -EBUSY;

		/*
		 * Only one user is allowed to change the output format, touch
		 * buffers, start / stop streaming, poll for data
		 */
		if (icd->streamer && icd->streamer != file)
			return -EBUSY;
	}

	if (s->target == V4L2_SEL_TGT_CROP &&
	    vb2_is_streaming(&icd->vb2_vidq) &&
	    ici->ops->set_liveselection)
		ret = ici->ops->set_liveselection(icd, s);
	else
		ret = ici->ops->set_selection(icd, s);
	if (!ret &&
	    s->target == V4L2_SEL_TGT_COMPOSE) {
		icd->user_width = s->r.width;
		icd->user_height = s->r.height;
		if (!icd->streamer)
			icd->streamer = file;
	}

	return ret;
}