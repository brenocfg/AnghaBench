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
struct usb_device {int dummy; } ;
struct em28xx {scalar_t__ ts; int /*<<< orphan*/  lock; int /*<<< orphan*/  devno; scalar_t__ def_i2c_bus; int /*<<< orphan*/  intf; } ;

/* Variables and functions */
 scalar_t__ PRIMARY_TS ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  em28xx_devused ; 
 int /*<<< orphan*/  em28xx_i2c_unregister (struct em28xx*,int) ; 
 int /*<<< orphan*/  em28xx_unregister_media_device (struct em28xx*) ; 
 struct usb_device* interface_to_usbdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_put_dev (struct usb_device*) ; 

__attribute__((used)) static void em28xx_release_resources(struct em28xx *dev)
{
	struct usb_device *udev = interface_to_usbdev(dev->intf);

	/*FIXME: I2C IR should be disconnected */

	mutex_lock(&dev->lock);

	em28xx_unregister_media_device(dev);

	if (dev->def_i2c_bus)
		em28xx_i2c_unregister(dev, 1);
	em28xx_i2c_unregister(dev, 0);

	if (dev->ts == PRIMARY_TS)
		usb_put_dev(udev);

	/* Mark device as unused */
	clear_bit(dev->devno, em28xx_devused);

	mutex_unlock(&dev->lock);
}