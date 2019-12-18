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
#define  USB_DEVICE_ID_CORSAIR_GLAIVE_RGB 129 
#define  USB_DEVICE_ID_CORSAIR_SCIMITAR_PRO_RGB 128 
 int /*<<< orphan*/  hid_info (struct hid_device*,char*) ; 
 struct usb_interface* to_usb_interface (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __u8 *corsair_mouse_report_fixup(struct hid_device *hdev, __u8 *rdesc,
        unsigned int *rsize)
{
	struct usb_interface *intf = to_usb_interface(hdev->dev.parent);

	if (intf->cur_altsetting->desc.bInterfaceNumber == 1) {
		/*
		 * Corsair GLAIVE RGB and Scimitar RGB Pro report descriptor is
		 * broken and defines two different Logical Minimum for the
		 * Consumer Application. The byte 77 should be a 0x26 defining
		 * a 16 bits integer for the Logical Maximum but it is a 0x16
		 * instead (Logical Minimum)
		 */
		switch (hdev->product) {
		case USB_DEVICE_ID_CORSAIR_GLAIVE_RGB:
		case USB_DEVICE_ID_CORSAIR_SCIMITAR_PRO_RGB:
			if (*rsize >= 172 && rdesc[75] == 0x15 && rdesc[77] == 0x16
			&& rdesc[78] == 0xff && rdesc[79] == 0x0f) {
				hid_info(hdev, "Fixing up report descriptor\n");
				rdesc[77] = 0x26;
			}
			break;
		}

	}
	return rdesc;
}