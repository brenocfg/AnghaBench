#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  owner; } ;
struct mei_device {TYPE_2__ cdev; int /*<<< orphan*/  minor; } ;
struct device {TYPE_1__* driver; } ;
struct TYPE_5__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct device*) ; 
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PTR_ERR (struct device*) ; 
 int cdev_add (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  cdev_del (TYPE_2__*) ; 
 int /*<<< orphan*/  cdev_init (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 struct device* device_create_with_groups (int /*<<< orphan*/ ,struct device*,int,struct mei_device*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mei_class ; 
 int /*<<< orphan*/  mei_dbgfs_register (struct mei_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mei_devt ; 
 int /*<<< orphan*/  mei_fops ; 
 int /*<<< orphan*/  mei_groups ; 
 int /*<<< orphan*/  mei_minor_free (struct mei_device*) ; 
 int mei_minor_get (struct mei_device*) ; 

int mei_register(struct mei_device *dev, struct device *parent)
{
	struct device *clsdev; /* class device */
	int ret, devno;

	ret = mei_minor_get(dev);
	if (ret < 0)
		return ret;

	/* Fill in the data structures */
	devno = MKDEV(MAJOR(mei_devt), dev->minor);
	cdev_init(&dev->cdev, &mei_fops);
	dev->cdev.owner = parent->driver->owner;

	/* Add the device */
	ret = cdev_add(&dev->cdev, devno, 1);
	if (ret) {
		dev_err(parent, "unable to add device %d:%d\n",
			MAJOR(mei_devt), dev->minor);
		goto err_dev_add;
	}

	clsdev = device_create_with_groups(mei_class, parent, devno,
					   dev, mei_groups,
					   "mei%d", dev->minor);

	if (IS_ERR(clsdev)) {
		dev_err(parent, "unable to create device %d:%d\n",
			MAJOR(mei_devt), dev->minor);
		ret = PTR_ERR(clsdev);
		goto err_dev_create;
	}

	mei_dbgfs_register(dev, dev_name(clsdev));

	return 0;

err_dev_create:
	cdev_del(&dev->cdev);
err_dev_add:
	mei_minor_free(dev);
	return ret;
}