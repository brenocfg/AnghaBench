#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct v4l2_subdev {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  entity; } ;
struct TYPE_4__ {int /*<<< orphan*/ * pipe; TYPE_2__ vdev; } ;
struct fimc_lite {int /*<<< orphan*/  lock; TYPE_1__ ve; } ;

/* Variables and functions */
 int /*<<< orphan*/  media_entity_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct fimc_lite* v4l2_get_subdevdata (struct v4l2_subdev*) ; 
 scalar_t__ video_is_registered (TYPE_2__*) ; 
 int /*<<< orphan*/  video_unregister_device (TYPE_2__*) ; 

__attribute__((used)) static void fimc_lite_subdev_unregistered(struct v4l2_subdev *sd)
{
	struct fimc_lite *fimc = v4l2_get_subdevdata(sd);

	if (fimc == NULL)
		return;

	mutex_lock(&fimc->lock);

	if (video_is_registered(&fimc->ve.vdev)) {
		video_unregister_device(&fimc->ve.vdev);
		media_entity_cleanup(&fimc->ve.vdev.entity);
		fimc->ve.pipe = NULL;
	}

	mutex_unlock(&fimc->lock);
}