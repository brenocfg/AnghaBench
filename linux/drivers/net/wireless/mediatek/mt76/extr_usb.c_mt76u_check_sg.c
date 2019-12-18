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
struct usb_device {scalar_t__ speed; TYPE_1__* bus; } ;
struct mt76_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {scalar_t__ sg_tablesize; scalar_t__ no_sg_constraint; } ;

/* Variables and functions */
 scalar_t__ USB_SPEED_WIRELESS ; 
 int /*<<< orphan*/  disable_usb_sg ; 
 struct usb_device* to_usb_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool mt76u_check_sg(struct mt76_dev *dev)
{
	struct usb_device *udev = to_usb_device(dev->dev);

	return (!disable_usb_sg && udev->bus->sg_tablesize > 0 &&
		(udev->bus->no_sg_constraint ||
		 udev->speed == USB_SPEED_WIRELESS));
}