#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  release; int /*<<< orphan*/ * class; int /*<<< orphan*/  devt; } ;
struct telem_device_data {TYPE_1__ dev; int /*<<< orphan*/  cdev; int /*<<< orphan*/  available; int /*<<< orphan*/  ec; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TELEM_DEV_NAME_FMT ; 
 scalar_t__ TELEM_MAX_DEV ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int cdev_device_add (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  cdev_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 int ida_alloc_max (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int) ; 
 struct telem_device_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct telem_device_data*) ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 
 int /*<<< orphan*/  telem_class ; 
 int /*<<< orphan*/  telem_device_free ; 
 int /*<<< orphan*/  telem_fops ; 
 int /*<<< orphan*/  telem_ida ; 
 int /*<<< orphan*/  telem_major ; 

__attribute__((used)) static int telem_device_probe(struct platform_device *pdev)
{
	struct telem_device_data *dev_data;
	int error, minor;

	/* Get the next available device number */
	minor = ida_alloc_max(&telem_ida, TELEM_MAX_DEV-1, GFP_KERNEL);
	if (minor < 0) {
		error = minor;
		dev_err(&pdev->dev, "Failed to find minor number: %d", error);
		return error;
	}

	dev_data = kzalloc(sizeof(*dev_data), GFP_KERNEL);
	if (!dev_data) {
		ida_simple_remove(&telem_ida, minor);
		return -ENOMEM;
	}

	/* Initialize the device data */
	dev_data->ec = dev_get_platdata(&pdev->dev);
	atomic_set(&dev_data->available, 1);
	platform_set_drvdata(pdev, dev_data);

	/* Initialize the device */
	dev_data->dev.devt = MKDEV(telem_major, minor);
	dev_data->dev.class = &telem_class;
	dev_data->dev.release = telem_device_free;
	dev_set_name(&dev_data->dev, TELEM_DEV_NAME_FMT, minor);
	device_initialize(&dev_data->dev);

	/* Initialize the character device and add it to userspace */;
	cdev_init(&dev_data->cdev, &telem_fops);
	error = cdev_device_add(&dev_data->cdev, &dev_data->dev);
	if (error) {
		put_device(&dev_data->dev);
		ida_simple_remove(&telem_ida, minor);
		return error;
	}

	return 0;
}