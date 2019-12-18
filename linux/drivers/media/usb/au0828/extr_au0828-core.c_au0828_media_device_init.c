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
struct media_device {int dummy; } ;
struct au0828_dev {struct media_device* media_dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 struct media_device* media_device_usb_allocate (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int au0828_media_device_init(struct au0828_dev *dev,
				    struct usb_device *udev)
{
#ifdef CONFIG_MEDIA_CONTROLLER
	struct media_device *mdev;

	mdev = media_device_usb_allocate(udev, KBUILD_MODNAME, THIS_MODULE);
	if (!mdev)
		return -ENOMEM;

	dev->media_dev = mdev;
#endif
	return 0;
}