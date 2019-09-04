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
struct hid_device {int product; } ;
typedef  int __u8 ;

/* Variables and functions */
#define  USB_DEVICE_ID_ELECOM_BM084 135 
#define  USB_DEVICE_ID_ELECOM_M_DT1DRBK 134 
#define  USB_DEVICE_ID_ELECOM_M_DT1URBK 133 
#define  USB_DEVICE_ID_ELECOM_M_HT1DRBK 132 
#define  USB_DEVICE_ID_ELECOM_M_HT1URBK 131 
#define  USB_DEVICE_ID_ELECOM_M_XT3DRBK 130 
#define  USB_DEVICE_ID_ELECOM_M_XT3URBK 129 
#define  USB_DEVICE_ID_ELECOM_M_XT4DRBK 128 
 int /*<<< orphan*/  hid_info (struct hid_device*,char*) ; 
 int /*<<< orphan*/  mouse_button_fixup (struct hid_device*,int*,unsigned int,int) ; 

__attribute__((used)) static __u8 *elecom_report_fixup(struct hid_device *hdev, __u8 *rdesc,
		unsigned int *rsize)
{
	switch (hdev->product) {
	case USB_DEVICE_ID_ELECOM_BM084:
		/* The BM084 Bluetooth mouse includes a non-existing horizontal
		 * wheel in the HID descriptor. */
		if (*rsize >= 48 && rdesc[46] == 0x05 && rdesc[47] == 0x0c) {
			hid_info(hdev, "Fixing up Elecom BM084 report descriptor\n");
			rdesc[47] = 0x00;
		}
		break;
	case USB_DEVICE_ID_ELECOM_M_XT3URBK:
	case USB_DEVICE_ID_ELECOM_M_XT3DRBK:
	case USB_DEVICE_ID_ELECOM_M_XT4DRBK:
		mouse_button_fixup(hdev, rdesc, *rsize, 6);
		break;
	case USB_DEVICE_ID_ELECOM_M_DT1URBK:
	case USB_DEVICE_ID_ELECOM_M_DT1DRBK:
	case USB_DEVICE_ID_ELECOM_M_HT1URBK:
	case USB_DEVICE_ID_ELECOM_M_HT1DRBK:
		mouse_button_fixup(hdev, rdesc, *rsize, 8);
		break;
	}
	return rdesc;
}