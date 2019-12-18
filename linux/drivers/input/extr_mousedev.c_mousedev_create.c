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
struct TYPE_8__ {int /*<<< orphan*/  release; int /*<<< orphan*/  devt; int /*<<< orphan*/ * parent; int /*<<< orphan*/ * class; } ;
struct TYPE_9__ {struct mousedev* private; struct input_handler* handler; int /*<<< orphan*/  name; int /*<<< orphan*/  dev; } ;
struct mousedev {int exist; TYPE_1__ dev; TYPE_2__ handle; int /*<<< orphan*/  cdev; int /*<<< orphan*/  close_device; int /*<<< orphan*/  open_device; int /*<<< orphan*/  wait; int /*<<< orphan*/  mutex; int /*<<< orphan*/  client_lock; int /*<<< orphan*/  mixdev_node; int /*<<< orphan*/  client_list; } ;
struct input_handler {int dummy; } ;
struct input_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct mousedev* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INPUT_MAJOR ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int) ; 
 int MOUSEDEV_MINORS ; 
 int MOUSEDEV_MINOR_BASE ; 
 int /*<<< orphan*/  SINGLE_DEPTH_NESTING ; 
 int cdev_device_add (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  cdev_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_name (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_class ; 
 int /*<<< orphan*/  input_free_minor (int) ; 
 int /*<<< orphan*/  input_get_device (struct input_dev*) ; 
 int input_register_handle (TYPE_2__*) ; 
 int /*<<< orphan*/  input_unregister_handle (TYPE_2__*) ; 
 struct mousedev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_set_subclass (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mixdev_close_devices ; 
 int /*<<< orphan*/  mixdev_open_devices ; 
 int /*<<< orphan*/  mousedev_cleanup (struct mousedev*) ; 
 int /*<<< orphan*/  mousedev_close_device ; 
 int /*<<< orphan*/  mousedev_fops ; 
 int /*<<< orphan*/  mousedev_free ; 
 int /*<<< orphan*/  mousedev_open_device ; 
 int mousedev_reserve_minor (int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct mousedev *mousedev_create(struct input_dev *dev,
					struct input_handler *handler,
					bool mixdev)
{
	struct mousedev *mousedev;
	int minor;
	int error;

	minor = mousedev_reserve_minor(mixdev);
	if (minor < 0) {
		error = minor;
		goto err_out;
	}

	mousedev = kzalloc(sizeof(struct mousedev), GFP_KERNEL);
	if (!mousedev) {
		error = -ENOMEM;
		goto err_free_minor;
	}

	INIT_LIST_HEAD(&mousedev->client_list);
	INIT_LIST_HEAD(&mousedev->mixdev_node);
	spin_lock_init(&mousedev->client_lock);
	mutex_init(&mousedev->mutex);
	lockdep_set_subclass(&mousedev->mutex,
			     mixdev ? SINGLE_DEPTH_NESTING : 0);
	init_waitqueue_head(&mousedev->wait);

	if (mixdev) {
		dev_set_name(&mousedev->dev, "mice");

		mousedev->open_device = mixdev_open_devices;
		mousedev->close_device = mixdev_close_devices;
	} else {
		int dev_no = minor;
		/* Normalize device number if it falls into legacy range */
		if (dev_no < MOUSEDEV_MINOR_BASE + MOUSEDEV_MINORS)
			dev_no -= MOUSEDEV_MINOR_BASE;
		dev_set_name(&mousedev->dev, "mouse%d", dev_no);

		mousedev->open_device = mousedev_open_device;
		mousedev->close_device = mousedev_close_device;
	}

	mousedev->exist = true;
	mousedev->handle.dev = input_get_device(dev);
	mousedev->handle.name = dev_name(&mousedev->dev);
	mousedev->handle.handler = handler;
	mousedev->handle.private = mousedev;

	mousedev->dev.class = &input_class;
	if (dev)
		mousedev->dev.parent = &dev->dev;
	mousedev->dev.devt = MKDEV(INPUT_MAJOR, minor);
	mousedev->dev.release = mousedev_free;
	device_initialize(&mousedev->dev);

	if (!mixdev) {
		error = input_register_handle(&mousedev->handle);
		if (error)
			goto err_free_mousedev;
	}

	cdev_init(&mousedev->cdev, &mousedev_fops);

	error = cdev_device_add(&mousedev->cdev, &mousedev->dev);
	if (error)
		goto err_cleanup_mousedev;

	return mousedev;

 err_cleanup_mousedev:
	mousedev_cleanup(mousedev);
	if (!mixdev)
		input_unregister_handle(&mousedev->handle);
 err_free_mousedev:
	put_device(&mousedev->dev);
 err_free_minor:
	input_free_minor(minor);
 err_out:
	return ERR_PTR(error);
}