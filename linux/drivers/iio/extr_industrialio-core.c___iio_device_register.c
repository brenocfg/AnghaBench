#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct module {int dummy; } ;
struct TYPE_7__ {TYPE_1__* parent; int /*<<< orphan*/  devt; scalar_t__ of_node; } ;
struct TYPE_6__ {struct module* owner; } ;
struct iio_dev {int modes; TYPE_4__ dev; TYPE_2__ chrdev; int /*<<< orphan*/ * setup_ops; int /*<<< orphan*/  id; int /*<<< orphan*/  info; struct module* driver_module; } ;
struct TYPE_5__ {scalar_t__ of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int INDIO_ALL_BUFFER_MODES ; 
 int INDIO_ALL_TRIGGERED_MODES ; 
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cdev_device_add (TYPE_2__*,TYPE_4__*) ; 
 int /*<<< orphan*/  cdev_init (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int iio_buffer_alloc_sysfs_and_mask (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_buffer_fileops ; 
 int /*<<< orphan*/  iio_buffer_free_sysfs_and_mask (struct iio_dev*) ; 
 int iio_check_unique_scan_index (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_device_register_debugfs (struct iio_dev*) ; 
 int iio_device_register_eventset (struct iio_dev*) ; 
 int iio_device_register_sysfs (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_device_register_trigger_consumer (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_device_unregister_debugfs (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_device_unregister_eventset (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_device_unregister_sysfs (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_devt ; 
 int /*<<< orphan*/  noop_ring_setup_ops ; 

int __iio_device_register(struct iio_dev *indio_dev, struct module *this_mod)
{
	int ret;

	indio_dev->driver_module = this_mod;
	/* If the calling driver did not initialize of_node, do it here */
	if (!indio_dev->dev.of_node && indio_dev->dev.parent)
		indio_dev->dev.of_node = indio_dev->dev.parent->of_node;

	ret = iio_check_unique_scan_index(indio_dev);
	if (ret < 0)
		return ret;

	if (!indio_dev->info)
		return -EINVAL;

	/* configure elements for the chrdev */
	indio_dev->dev.devt = MKDEV(MAJOR(iio_devt), indio_dev->id);

	iio_device_register_debugfs(indio_dev);

	ret = iio_buffer_alloc_sysfs_and_mask(indio_dev);
	if (ret) {
		dev_err(indio_dev->dev.parent,
			"Failed to create buffer sysfs interfaces\n");
		goto error_unreg_debugfs;
	}

	ret = iio_device_register_sysfs(indio_dev);
	if (ret) {
		dev_err(indio_dev->dev.parent,
			"Failed to register sysfs interfaces\n");
		goto error_buffer_free_sysfs;
	}
	ret = iio_device_register_eventset(indio_dev);
	if (ret) {
		dev_err(indio_dev->dev.parent,
			"Failed to register event set\n");
		goto error_free_sysfs;
	}
	if (indio_dev->modes & INDIO_ALL_TRIGGERED_MODES)
		iio_device_register_trigger_consumer(indio_dev);

	if ((indio_dev->modes & INDIO_ALL_BUFFER_MODES) &&
		indio_dev->setup_ops == NULL)
		indio_dev->setup_ops = &noop_ring_setup_ops;

	cdev_init(&indio_dev->chrdev, &iio_buffer_fileops);

	indio_dev->chrdev.owner = this_mod;

	ret = cdev_device_add(&indio_dev->chrdev, &indio_dev->dev);
	if (ret < 0)
		goto error_unreg_eventset;

	return 0;

error_unreg_eventset:
	iio_device_unregister_eventset(indio_dev);
error_free_sysfs:
	iio_device_unregister_sysfs(indio_dev);
error_buffer_free_sysfs:
	iio_buffer_free_sysfs_and_mask(indio_dev);
error_unreg_debugfs:
	iio_device_unregister_debugfs(indio_dev);
	return ret;
}