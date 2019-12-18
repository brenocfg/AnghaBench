#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct usb_device {int /*<<< orphan*/  manufacturer; int /*<<< orphan*/  product; } ;
struct media_device {int dummy; } ;
struct em28xx {struct media_device* media_dev; TYPE_1__* intf; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 struct media_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  media_device_usb_init (struct media_device*,struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int em28xx_media_device_init(struct em28xx *dev,
				    struct usb_device *udev)
{
#ifdef CONFIG_MEDIA_CONTROLLER
	struct media_device *mdev;

	mdev = kzalloc(sizeof(*mdev), GFP_KERNEL);
	if (!mdev)
		return -ENOMEM;

	if (udev->product)
		media_device_usb_init(mdev, udev, udev->product);
	else if (udev->manufacturer)
		media_device_usb_init(mdev, udev, udev->manufacturer);
	else
		media_device_usb_init(mdev, udev, dev_name(&dev->intf->dev));

	dev->media_dev = mdev;
#endif
	return 0;
}