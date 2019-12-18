#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct ccwgroup_driver {scalar_t__ ccw_driver; int (* setup ) (struct ccwgroup_device*) ;int /*<<< orphan*/  driver; } ;
struct TYPE_12__ {int /*<<< orphan*/ * driver; int /*<<< orphan*/  groups; int /*<<< orphan*/  release; struct device* parent; int /*<<< orphan*/ * bus; } ;
struct ccwgroup_device {int count; TYPE_2__ dev; int /*<<< orphan*/  reg_mutex; TYPE_3__** cdev; int /*<<< orphan*/  ungroup_work; int /*<<< orphan*/  onoff; } ;
struct ccw_dev_id {int dummy; } ;
struct TYPE_11__ {scalar_t__ driver_info; } ;
struct TYPE_13__ {scalar_t__ drv; TYPE_2__ dev; int /*<<< orphan*/  ccwlock; TYPE_1__ id; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int __ccwgroup_create_symlinks (struct ccwgroup_device*) ; 
 int __get_next_id (char const**,struct ccw_dev_id*) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccwgroup_attr_groups ; 
 int /*<<< orphan*/  ccwgroup_bus_type ; 
 int /*<<< orphan*/  ccwgroup_release ; 
 int /*<<< orphan*/  ccwgroup_ungroup_workfn ; 
 int /*<<< orphan*/  cdev ; 
 struct ccwgroup_device* dev_get_drvdata (TYPE_2__*) ; 
 int /*<<< orphan*/  dev_name (TYPE_2__*) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_2__*,struct ccwgroup_device*) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int device_add (TYPE_2__*) ; 
 int /*<<< orphan*/  device_del (TYPE_2__*) ; 
 int /*<<< orphan*/  device_initialize (TYPE_2__*) ; 
 TYPE_3__* get_ccwdev_by_dev_id (struct ccw_dev_id*) ; 
 struct ccwgroup_device* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (TYPE_2__*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  struct_size (struct ccwgroup_device*,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct ccwgroup_device*) ; 

int ccwgroup_create_dev(struct device *parent, struct ccwgroup_driver *gdrv,
			int num_devices, const char *buf)
{
	struct ccwgroup_device *gdev;
	struct ccw_dev_id dev_id;
	int rc, i;

	if (num_devices < 1)
		return -EINVAL;

	gdev = kzalloc(struct_size(gdev, cdev, num_devices), GFP_KERNEL);
	if (!gdev)
		return -ENOMEM;

	atomic_set(&gdev->onoff, 0);
	mutex_init(&gdev->reg_mutex);
	mutex_lock(&gdev->reg_mutex);
	INIT_WORK(&gdev->ungroup_work, ccwgroup_ungroup_workfn);
	gdev->count = num_devices;
	gdev->dev.bus = &ccwgroup_bus_type;
	gdev->dev.parent = parent;
	gdev->dev.release = ccwgroup_release;
	device_initialize(&gdev->dev);

	for (i = 0; i < num_devices && buf; i++) {
		rc = __get_next_id(&buf, &dev_id);
		if (rc != 0)
			goto error;
		gdev->cdev[i] = get_ccwdev_by_dev_id(&dev_id);
		/*
		 * All devices have to be of the same type in
		 * order to be grouped.
		 */
		if (!gdev->cdev[i] || !gdev->cdev[i]->drv ||
		    gdev->cdev[i]->drv != gdev->cdev[0]->drv ||
		    gdev->cdev[i]->id.driver_info !=
		    gdev->cdev[0]->id.driver_info) {
			rc = -EINVAL;
			goto error;
		}
		/* Don't allow a device to belong to more than one group. */
		spin_lock_irq(gdev->cdev[i]->ccwlock);
		if (dev_get_drvdata(&gdev->cdev[i]->dev)) {
			spin_unlock_irq(gdev->cdev[i]->ccwlock);
			rc = -EINVAL;
			goto error;
		}
		dev_set_drvdata(&gdev->cdev[i]->dev, gdev);
		spin_unlock_irq(gdev->cdev[i]->ccwlock);
	}
	/* Check for sufficient number of bus ids. */
	if (i < num_devices) {
		rc = -EINVAL;
		goto error;
	}
	/* Check for trailing stuff. */
	if (i == num_devices && buf && strlen(buf) > 0) {
		rc = -EINVAL;
		goto error;
	}
	/* Check if the devices are bound to the required ccw driver. */
	if (gdrv && gdrv->ccw_driver &&
	    gdev->cdev[0]->drv != gdrv->ccw_driver) {
		rc = -EINVAL;
		goto error;
	}

	dev_set_name(&gdev->dev, "%s", dev_name(&gdev->cdev[0]->dev));
	gdev->dev.groups = ccwgroup_attr_groups;

	if (gdrv) {
		gdev->dev.driver = &gdrv->driver;
		rc = gdrv->setup ? gdrv->setup(gdev) : 0;
		if (rc)
			goto error;
	}
	rc = device_add(&gdev->dev);
	if (rc)
		goto error;
	rc = __ccwgroup_create_symlinks(gdev);
	if (rc) {
		device_del(&gdev->dev);
		goto error;
	}
	mutex_unlock(&gdev->reg_mutex);
	return 0;
error:
	for (i = 0; i < num_devices; i++)
		if (gdev->cdev[i]) {
			spin_lock_irq(gdev->cdev[i]->ccwlock);
			if (dev_get_drvdata(&gdev->cdev[i]->dev) == gdev)
				dev_set_drvdata(&gdev->cdev[i]->dev, NULL);
			spin_unlock_irq(gdev->cdev[i]->ccwlock);
			put_device(&gdev->cdev[i]->dev);
			gdev->cdev[i] = NULL;
		}
	mutex_unlock(&gdev->reg_mutex);
	put_device(&gdev->dev);
	return rc;
}