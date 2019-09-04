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
struct file {int dummy; } ;
struct camif_vp {void* owner; int /*<<< orphan*/  vb_queue; int /*<<< orphan*/  id; struct camif_dev* camif; } ;
struct TYPE_4__ {TYPE_1__* sd; } ;
struct camif_dev {TYPE_2__ sensor; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;
struct TYPE_3__ {int /*<<< orphan*/  entity; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  media_pipeline_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int vb2_streamoff (int /*<<< orphan*/ *,int) ; 
 struct camif_vp* video_drvdata (struct file*) ; 

__attribute__((used)) static int s3c_camif_streamoff(struct file *file, void *priv,
			       enum v4l2_buf_type type)
{
	struct camif_vp *vp = video_drvdata(file);
	struct camif_dev *camif = vp->camif;
	int ret;

	pr_debug("[vp%d]\n", vp->id);

	if (type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return -EINVAL;

	if (vp->owner && vp->owner != priv)
		return -EBUSY;

	ret = vb2_streamoff(&vp->vb_queue, type);
	if (ret == 0)
		media_pipeline_stop(&camif->sensor.sd->entity);
	return ret;
}