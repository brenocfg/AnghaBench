#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct input_handler {int dummy; } ;
struct input_device_id {int dummy; } ;
struct input_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  release; int /*<<< orphan*/ * parent; int /*<<< orphan*/ * class; int /*<<< orphan*/  devt; } ;
struct TYPE_9__ {struct evdev* private; struct input_handler* handler; int /*<<< orphan*/  name; int /*<<< orphan*/  dev; } ;
struct evdev {int exist; TYPE_1__ dev; TYPE_2__ handle; int /*<<< orphan*/  cdev; int /*<<< orphan*/  wait; int /*<<< orphan*/  mutex; int /*<<< orphan*/  client_lock; int /*<<< orphan*/  client_list; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EVDEV_MINORS ; 
 int EVDEV_MINOR_BASE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INPUT_MAJOR ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int) ; 
 int cdev_device_add (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  cdev_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_name (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 int /*<<< orphan*/  evdev_cleanup (struct evdev*) ; 
 int /*<<< orphan*/  evdev_fops ; 
 int /*<<< orphan*/  evdev_free ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_class ; 
 int /*<<< orphan*/  input_free_minor (int) ; 
 int /*<<< orphan*/  input_get_device (struct input_dev*) ; 
 int input_get_new_minor (int,int,int) ; 
 int input_register_handle (TYPE_2__*) ; 
 int /*<<< orphan*/  input_unregister_handle (TYPE_2__*) ; 
 struct evdev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int evdev_connect(struct input_handler *handler, struct input_dev *dev,
			 const struct input_device_id *id)
{
	struct evdev *evdev;
	int minor;
	int dev_no;
	int error;

	minor = input_get_new_minor(EVDEV_MINOR_BASE, EVDEV_MINORS, true);
	if (minor < 0) {
		error = minor;
		pr_err("failed to reserve new minor: %d\n", error);
		return error;
	}

	evdev = kzalloc(sizeof(struct evdev), GFP_KERNEL);
	if (!evdev) {
		error = -ENOMEM;
		goto err_free_minor;
	}

	INIT_LIST_HEAD(&evdev->client_list);
	spin_lock_init(&evdev->client_lock);
	mutex_init(&evdev->mutex);
	init_waitqueue_head(&evdev->wait);
	evdev->exist = true;

	dev_no = minor;
	/* Normalize device number if it falls into legacy range */
	if (dev_no < EVDEV_MINOR_BASE + EVDEV_MINORS)
		dev_no -= EVDEV_MINOR_BASE;
	dev_set_name(&evdev->dev, "event%d", dev_no);

	evdev->handle.dev = input_get_device(dev);
	evdev->handle.name = dev_name(&evdev->dev);
	evdev->handle.handler = handler;
	evdev->handle.private = evdev;

	evdev->dev.devt = MKDEV(INPUT_MAJOR, minor);
	evdev->dev.class = &input_class;
	evdev->dev.parent = &dev->dev;
	evdev->dev.release = evdev_free;
	device_initialize(&evdev->dev);

	error = input_register_handle(&evdev->handle);
	if (error)
		goto err_free_evdev;

	cdev_init(&evdev->cdev, &evdev_fops);

	error = cdev_device_add(&evdev->cdev, &evdev->dev);
	if (error)
		goto err_cleanup_evdev;

	return 0;

 err_cleanup_evdev:
	evdev_cleanup(evdev);
	input_unregister_handle(&evdev->handle);
 err_free_evdev:
	put_device(&evdev->dev);
 err_free_minor:
	input_free_minor(minor);
	return error;
}