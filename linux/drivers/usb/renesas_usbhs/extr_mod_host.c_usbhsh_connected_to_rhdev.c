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
struct usbhsh_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ root_hub; } ;
struct usb_hcd {TYPE_1__ self; } ;
struct usb_device {scalar_t__ parent; } ;

/* Variables and functions */
 struct usb_device* usbhsh_udev_to_usbv (struct usbhsh_device*) ; 

__attribute__((used)) static int usbhsh_connected_to_rhdev(struct usb_hcd *hcd,
				     struct usbhsh_device *udev)
{
	struct usb_device *usbv = usbhsh_udev_to_usbv(udev);

	return hcd->self.root_hub == usbv->parent;
}