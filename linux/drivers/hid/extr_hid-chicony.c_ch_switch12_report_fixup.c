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
struct usb_interface {TYPE_3__* cur_altsetting; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct hid_device {int product; TYPE_1__ dev; } ;
typedef  int __u8 ;
struct TYPE_5__ {int bInterfaceNumber; } ;
struct TYPE_6__ {TYPE_2__ desc; } ;

/* Variables and functions */
#define  USB_DEVICE_ID_CHICONY_ACER_SWITCH12 128 
 int /*<<< orphan*/  hid_info (struct hid_device*,char*) ; 
 struct usb_interface* to_usb_interface (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __u8 *ch_switch12_report_fixup(struct hid_device *hdev, __u8 *rdesc,
		unsigned int *rsize)
{
	struct usb_interface *intf = to_usb_interface(hdev->dev.parent);
	
	if (intf->cur_altsetting->desc.bInterfaceNumber == 1) {
		/* Change usage maximum and logical maximum from 0x7fff to
		 * 0x2fff, so they don't exceed HID_MAX_USAGES */
		switch (hdev->product) {
		case USB_DEVICE_ID_CHICONY_ACER_SWITCH12:
			if (*rsize >= 128 && rdesc[64] == 0xff && rdesc[65] == 0x7f
					&& rdesc[69] == 0xff && rdesc[70] == 0x7f) {
				hid_info(hdev, "Fixing up report descriptor\n");
				rdesc[65] = rdesc[70] = 0x2f;
			}
			break;
		}

	}
	return rdesc;
}