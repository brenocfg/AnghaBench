#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct usb_hcd {TYPE_3__* driver; } ;
struct TYPE_4__ {int /*<<< orphan*/  wMaxPacketSize; } ;
struct TYPE_5__ {TYPE_1__ desc; } ;
struct usb_device {TYPE_2__ ep0; int /*<<< orphan*/  speed; int /*<<< orphan*/  bus; } ;
struct lvs_rh {int /*<<< orphan*/  portnum; int /*<<< orphan*/  present; } ;
struct TYPE_6__ {scalar_t__ (* enable_device ) (struct usb_hcd*,struct usb_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  USB_SPEED_SUPER ; 
 int /*<<< orphan*/  USB_STATE_DEFAULT ; 
 struct usb_hcd* bus_to_hcd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 scalar_t__ stub1 (struct usb_hcd*,struct usb_device*) ; 
 struct usb_device* usb_alloc_dev (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct lvs_rh* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_put_dev (struct usb_device*) ; 
 int /*<<< orphan*/  usb_set_device_state (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct usb_device *create_lvs_device(struct usb_interface *intf)
{
	struct usb_device *udev, *hdev;
	struct usb_hcd *hcd;
	struct lvs_rh *lvs = usb_get_intfdata(intf);

	if (!lvs->present) {
		dev_err(&intf->dev, "No LVS device is present\n");
		return NULL;
	}

	hdev = interface_to_usbdev(intf);
	hcd = bus_to_hcd(hdev->bus);

	udev = usb_alloc_dev(hdev, hdev->bus, lvs->portnum);
	if (!udev) {
		dev_err(&intf->dev, "Could not allocate lvs udev\n");
		return NULL;
	}
	udev->speed = USB_SPEED_SUPER;
	udev->ep0.desc.wMaxPacketSize = cpu_to_le16(512);
	usb_set_device_state(udev, USB_STATE_DEFAULT);

	if (hcd->driver->enable_device) {
		if (hcd->driver->enable_device(hcd, udev) < 0) {
			dev_err(&intf->dev, "Failed to enable\n");
			usb_put_dev(udev);
			return NULL;
		}
	}

	return udev;
}