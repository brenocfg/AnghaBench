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
struct media_entity {int dummy; } ;
struct v4l2_subdev {int owner_v4l2_dev; scalar_t__ owner; struct v4l2_device* v4l2_dev; int /*<<< orphan*/  list; TYPE_3__* internal_ops; int /*<<< orphan*/  ctrl_handler; int /*<<< orphan*/ * name; struct media_entity entity; } ;
struct v4l2_device {int /*<<< orphan*/  lock; int /*<<< orphan*/  subdevs; scalar_t__ mdev; int /*<<< orphan*/  ctrl_handler; TYPE_2__* dev; } ;
struct TYPE_6__ {int (* registered ) (struct v4l2_subdev*) ;} ;
struct TYPE_5__ {TYPE_1__* driver; } ;
struct TYPE_4__ {scalar_t__ owner; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int media_device_register_entity (scalar_t__,struct media_entity*) ; 
 int /*<<< orphan*/  media_device_unregister_entity (struct media_entity*) ; 
 int /*<<< orphan*/  module_put (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  try_module_get (scalar_t__) ; 
 int v4l2_ctrl_add_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int v4l2_device_register_subdev(struct v4l2_device *v4l2_dev,
				struct v4l2_subdev *sd)
{
#if defined(CONFIG_MEDIA_CONTROLLER)
	struct media_entity *entity = &sd->entity;
#endif
	int err;

	/* Check for valid input */
	if (!v4l2_dev || !sd || sd->v4l2_dev || !sd->name[0])
		return -EINVAL;

	/*
	 * The reason to acquire the module here is to avoid unloading
	 * a module of sub-device which is registered to a media
	 * device. To make it possible to unload modules for media
	 * devices that also register sub-devices, do not
	 * try_module_get() such sub-device owners.
	 */
	sd->owner_v4l2_dev = v4l2_dev->dev && v4l2_dev->dev->driver &&
		sd->owner == v4l2_dev->dev->driver->owner;

	if (!sd->owner_v4l2_dev && !try_module_get(sd->owner))
		return -ENODEV;

	sd->v4l2_dev = v4l2_dev;
	/* This just returns 0 if either of the two args is NULL */
	err = v4l2_ctrl_add_handler(v4l2_dev->ctrl_handler, sd->ctrl_handler,
				    NULL, true);
	if (err)
		goto error_module;

#if defined(CONFIG_MEDIA_CONTROLLER)
	/* Register the entity. */
	if (v4l2_dev->mdev) {
		err = media_device_register_entity(v4l2_dev->mdev, entity);
		if (err < 0)
			goto error_module;
	}
#endif

	if (sd->internal_ops && sd->internal_ops->registered) {
		err = sd->internal_ops->registered(sd);
		if (err)
			goto error_unregister;
	}

	spin_lock(&v4l2_dev->lock);
	list_add_tail(&sd->list, &v4l2_dev->subdevs);
	spin_unlock(&v4l2_dev->lock);

	return 0;

error_unregister:
#if defined(CONFIG_MEDIA_CONTROLLER)
	media_device_unregister_entity(entity);
#endif
error_module:
	if (!sd->owner_v4l2_dev)
		module_put(sd->owner);
	sd->v4l2_dev = NULL;
	return err;
}