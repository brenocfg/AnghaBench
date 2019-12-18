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
struct video_device {int /*<<< orphan*/  entity; } ;
struct v4l2_subdev {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * pipe; struct video_device vdev; } ;
struct TYPE_4__ {int /*<<< orphan*/ * ctx; TYPE_1__ ve; } ;
struct fimc_dev {int /*<<< orphan*/  lock; TYPE_2__ vid_cap; } ;

/* Variables and functions */
 int /*<<< orphan*/  fimc_ctrls_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fimc_unregister_m2m_device (struct fimc_dev*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  media_entity_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct fimc_dev* v4l2_get_subdevdata (struct v4l2_subdev*) ; 
 scalar_t__ video_is_registered (struct video_device*) ; 
 int /*<<< orphan*/  video_unregister_device (struct video_device*) ; 

__attribute__((used)) static void fimc_capture_subdev_unregistered(struct v4l2_subdev *sd)
{
	struct fimc_dev *fimc = v4l2_get_subdevdata(sd);
	struct video_device *vdev;

	if (fimc == NULL)
		return;

	mutex_lock(&fimc->lock);

	fimc_unregister_m2m_device(fimc);
	vdev = &fimc->vid_cap.ve.vdev;

	if (video_is_registered(vdev)) {
		video_unregister_device(vdev);
		media_entity_cleanup(&vdev->entity);
		fimc_ctrls_delete(fimc->vid_cap.ctx);
		fimc->vid_cap.ve.pipe = NULL;
	}
	kfree(fimc->vid_cap.ctx);
	fimc->vid_cap.ctx = NULL;

	mutex_unlock(&fimc->lock);
}