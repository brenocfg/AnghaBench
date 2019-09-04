#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {struct usb_host_interface* cur_altsetting; } ;
struct TYPE_4__ {int bInterfaceNumber; } ;
struct usb_host_interface {TYPE_2__ desc; } ;
struct usb_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct hid_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int HID_REQ_SET_IDLE ; 
 int hid_set_idle (struct usb_device*,int,int,int) ; 
 struct usb_device* hid_to_usb_dev (struct hid_device*) ; 
 struct usb_interface* to_usb_interface (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usbhid_idle(struct hid_device *hid, int report, int idle,
		int reqtype)
{
	struct usb_device *dev = hid_to_usb_dev(hid);
	struct usb_interface *intf = to_usb_interface(hid->dev.parent);
	struct usb_host_interface *interface = intf->cur_altsetting;
	int ifnum = interface->desc.bInterfaceNumber;

	if (reqtype != HID_REQ_SET_IDLE)
		return -EINVAL;

	return hid_set_idle(dev, ifnum, report, idle);
}