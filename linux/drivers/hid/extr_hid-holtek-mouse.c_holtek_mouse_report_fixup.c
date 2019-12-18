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
#define  USB_DEVICE_ID_HOLTEK_ALT_MOUSE_A04A 133 
#define  USB_DEVICE_ID_HOLTEK_ALT_MOUSE_A067 132 
#define  USB_DEVICE_ID_HOLTEK_ALT_MOUSE_A070 131 
#define  USB_DEVICE_ID_HOLTEK_ALT_MOUSE_A072 130 
#define  USB_DEVICE_ID_HOLTEK_ALT_MOUSE_A081 129 
#define  USB_DEVICE_ID_HOLTEK_ALT_MOUSE_A0C2 128 
 int /*<<< orphan*/  hid_info (struct hid_device*,char*) ; 
 struct usb_interface* to_usb_interface (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __u8 *holtek_mouse_report_fixup(struct hid_device *hdev, __u8 *rdesc,
		unsigned int *rsize)
{
	struct usb_interface *intf = to_usb_interface(hdev->dev.parent);

	if (intf->cur_altsetting->desc.bInterfaceNumber == 1) {
		/* Change usage maximum and logical maximum from 0x7fff to
		 * 0x2fff, so they don't exceed HID_MAX_USAGES */
		switch (hdev->product) {
		case USB_DEVICE_ID_HOLTEK_ALT_MOUSE_A067:
		case USB_DEVICE_ID_HOLTEK_ALT_MOUSE_A072:
		case USB_DEVICE_ID_HOLTEK_ALT_MOUSE_A0C2:
			if (*rsize >= 122 && rdesc[115] == 0xff && rdesc[116] == 0x7f
					&& rdesc[120] == 0xff && rdesc[121] == 0x7f) {
				hid_info(hdev, "Fixing up report descriptor\n");
				rdesc[116] = rdesc[121] = 0x2f;
			}
			break;
		case USB_DEVICE_ID_HOLTEK_ALT_MOUSE_A04A:
		case USB_DEVICE_ID_HOLTEK_ALT_MOUSE_A070:
		case USB_DEVICE_ID_HOLTEK_ALT_MOUSE_A081:
			if (*rsize >= 113 && rdesc[106] == 0xff && rdesc[107] == 0x7f
					&& rdesc[111] == 0xff && rdesc[112] == 0x7f) {
				hid_info(hdev, "Fixing up report descriptor\n");
				rdesc[107] = rdesc[112] = 0x2f;
			}
			break;
		}

	}
	return rdesc;
}