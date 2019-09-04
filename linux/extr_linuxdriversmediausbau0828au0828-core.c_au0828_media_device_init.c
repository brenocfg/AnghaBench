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
struct au0828_dev {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int au0828_media_device_init(struct au0828_dev *dev,
				    struct usb_device *udev)
{
#ifdef CONFIG_MEDIA_CONTROLLER
	struct media_device *mdev;

	mdev = kzalloc(sizeof(*mdev), GFP_KERNEL);
	if (!mdev)
		return -ENOMEM;

	/* check if media device is already initialized */
	if (!mdev->dev)
		media_device_usb_init(mdev, udev, udev->product);

	dev->media_dev = mdev;
#endif
	return 0;
}