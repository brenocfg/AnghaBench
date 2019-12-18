#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct cx231xx {int /*<<< orphan*/  devno; int /*<<< orphan*/  udev; int /*<<< orphan*/  v4l2_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cx231xx_dev_uninit (struct cx231xx*) ; 
 int /*<<< orphan*/  cx231xx_devused ; 
 int /*<<< orphan*/  cx231xx_ir_exit (struct cx231xx*) ; 
 int /*<<< orphan*/  cx231xx_release_analog_resources (struct cx231xx*) ; 
 int /*<<< orphan*/  cx231xx_remove_from_devlist (struct cx231xx*) ; 
 int /*<<< orphan*/  cx231xx_unregister_media_device (struct cx231xx*) ; 
 int /*<<< orphan*/  usb_put_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 

void cx231xx_release_resources(struct cx231xx *dev)
{
	cx231xx_ir_exit(dev);

	cx231xx_release_analog_resources(dev);

	cx231xx_remove_from_devlist(dev);

	/* Release I2C buses */
	cx231xx_dev_uninit(dev);

	/* delete v4l2 device */
	v4l2_device_unregister(&dev->v4l2_dev);

	cx231xx_unregister_media_device(dev);

	usb_put_dev(dev->udev);

	/* Mark device as unused */
	clear_bit(dev->devno, &cx231xx_devused);
}