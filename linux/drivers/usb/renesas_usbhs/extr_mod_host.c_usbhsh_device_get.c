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
struct usbhsh_hpriv {int dummy; } ;
struct usbhsh_device {int dummy; } ;
struct usb_device {int dummy; } ;
struct urb {int /*<<< orphan*/  pipe; } ;

/* Variables and functions */
 scalar_t__ usb_pipedevice (int /*<<< orphan*/ ) ; 
 struct usbhsh_device* usbhsh_device0 (struct usbhsh_hpriv*) ; 
 struct usb_device* usbhsh_urb_to_usbv (struct urb*) ; 
 struct usbhsh_device* usbhsh_usbv_to_udev (struct usb_device*) ; 

__attribute__((used)) static struct usbhsh_device *usbhsh_device_get(struct usbhsh_hpriv *hpriv,
					       struct urb *urb)
{
	struct usb_device *usbv = usbhsh_urb_to_usbv(urb);
	struct usbhsh_device *udev = usbhsh_usbv_to_udev(usbv);

	/* usbhsh_device_attach() is still not called */
	if (!udev)
		return NULL;

	/* if it is device0, return it */
	if (0 == usb_pipedevice(urb->pipe))
		return usbhsh_device0(hpriv);

	/* return attached device */
	return udev;
}