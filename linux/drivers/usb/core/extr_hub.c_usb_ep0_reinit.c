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
struct usb_device {int /*<<< orphan*/  ep0; } ;

/* Variables and functions */
 scalar_t__ USB_DIR_IN ; 
 scalar_t__ USB_DIR_OUT ; 
 int /*<<< orphan*/  usb_disable_endpoint (struct usb_device*,scalar_t__,int) ; 
 int /*<<< orphan*/  usb_enable_endpoint (struct usb_device*,int /*<<< orphan*/ *,int) ; 

void usb_ep0_reinit(struct usb_device *udev)
{
	usb_disable_endpoint(udev, 0 + USB_DIR_IN, true);
	usb_disable_endpoint(udev, 0 + USB_DIR_OUT, true);
	usb_enable_endpoint(udev, &udev->ep0, true);
}