#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  release; int /*<<< orphan*/ * class; int /*<<< orphan*/  devt; } ;
struct event_device_data {int exist; TYPE_1__ dev; int /*<<< orphan*/  cdev; int /*<<< orphan*/  available; int /*<<< orphan*/  wq; int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  events; } ;
struct acpi_device {struct event_device_data* driver_data; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  EVENT_DEV_NAME_FMT ; 
 scalar_t__ EVENT_MAX_DEV ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int cdev_device_add (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  cdev_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 int /*<<< orphan*/  event_class ; 
 int /*<<< orphan*/  event_fops ; 
 int /*<<< orphan*/  event_ida ; 
 int /*<<< orphan*/  event_major ; 
 int /*<<< orphan*/  event_queue_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_device_data ; 
 int /*<<< orphan*/  hangup_device (struct event_device_data*) ; 
 int ida_alloc_max (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct event_device_data*) ; 
 struct event_device_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_size ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int event_device_add(struct acpi_device *adev)
{
	struct event_device_data *dev_data;
	int error, minor;

	minor = ida_alloc_max(&event_ida, EVENT_MAX_DEV-1, GFP_KERNEL);
	if (minor < 0) {
		error = minor;
		dev_err(&adev->dev, "Failed to find minor number: %d\n", error);
		return error;
	}

	dev_data = kzalloc(sizeof(*dev_data), GFP_KERNEL);
	if (!dev_data) {
		error = -ENOMEM;
		goto free_minor;
	}

	/* Initialize the device data. */
	adev->driver_data = dev_data;
	dev_data->events = event_queue_new(queue_size);
	if (!dev_data->events) {
		kfree(dev_data);
		error = -ENOMEM;
		goto free_minor;
	}
	spin_lock_init(&dev_data->queue_lock);
	init_waitqueue_head(&dev_data->wq);
	dev_data->exist = true;
	atomic_set(&dev_data->available, 1);

	/* Initialize the device. */
	dev_data->dev.devt = MKDEV(event_major, minor);
	dev_data->dev.class = &event_class;
	dev_data->dev.release = free_device_data;
	dev_set_name(&dev_data->dev, EVENT_DEV_NAME_FMT, minor);
	device_initialize(&dev_data->dev);

	/* Initialize the character device, and add it to userspace. */
	cdev_init(&dev_data->cdev, &event_fops);
	error = cdev_device_add(&dev_data->cdev, &dev_data->dev);
	if (error)
		goto free_dev_data;

	return 0;

free_dev_data:
	hangup_device(dev_data);
free_minor:
	ida_simple_remove(&event_ida, minor);
	return error;
}