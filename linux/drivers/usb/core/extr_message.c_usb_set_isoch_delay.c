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
struct TYPE_2__ {scalar_t__ bDeviceClass; } ;
struct usb_device {scalar_t__ speed; int /*<<< orphan*/  hub_delay; TYPE_1__ descriptor; } ;

/* Variables and functions */
 scalar_t__ USB_CLASS_HUB ; 
 int /*<<< orphan*/  USB_CTRL_SET_TIMEOUT ; 
 int USB_DIR_OUT ; 
 int USB_RECIP_DEVICE ; 
 int /*<<< orphan*/  USB_REQ_SET_ISOCH_DELAY ; 
 scalar_t__ USB_SPEED_SUPER ; 
 int USB_TYPE_STANDARD ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

int usb_set_isoch_delay(struct usb_device *dev)
{
	/* skip hub devices */
	if (dev->descriptor.bDeviceClass == USB_CLASS_HUB)
		return 0;

	/* skip non-SS/non-SSP devices */
	if (dev->speed < USB_SPEED_SUPER)
		return 0;

	return usb_control_msg(dev, usb_sndctrlpipe(dev, 0),
			USB_REQ_SET_ISOCH_DELAY,
			USB_DIR_OUT | USB_TYPE_STANDARD | USB_RECIP_DEVICE,
			dev->hub_delay, 0, NULL, 0,
			USB_CTRL_SET_TIMEOUT);
}