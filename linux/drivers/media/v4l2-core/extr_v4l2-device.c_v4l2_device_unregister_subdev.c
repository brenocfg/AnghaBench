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
struct v4l2_subdev {scalar_t__ devnode; int /*<<< orphan*/  entity; struct v4l2_device* v4l2_dev; TYPE_1__* internal_ops; int /*<<< orphan*/  list; } ;
struct v4l2_device {scalar_t__ mdev; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* unregistered ) (struct v4l2_subdev*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  media_device_unregister_entity (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_subdev_release (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  video_unregister_device (scalar_t__) ; 

void v4l2_device_unregister_subdev(struct v4l2_subdev *sd)
{
	struct v4l2_device *v4l2_dev;

	/* return if it isn't registered */
	if (sd == NULL || sd->v4l2_dev == NULL)
		return;

	v4l2_dev = sd->v4l2_dev;

	spin_lock(&v4l2_dev->lock);
	list_del(&sd->list);
	spin_unlock(&v4l2_dev->lock);

	if (sd->internal_ops && sd->internal_ops->unregistered)
		sd->internal_ops->unregistered(sd);
	sd->v4l2_dev = NULL;

#if defined(CONFIG_MEDIA_CONTROLLER)
	if (v4l2_dev->mdev) {
		/*
		 * No need to explicitly remove links, as both pads and
		 * links are removed by the function below, in the right order
		 */
		media_device_unregister_entity(&sd->entity);
	}
#endif
	if (sd->devnode)
		video_unregister_device(sd->devnode);
	else
		v4l2_subdev_release(sd);
}