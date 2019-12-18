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
struct hid_device_id {int product; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HID_CONNECT_DEFAULT ; 
#define  USB_DEVICE_ID_GENIUS_MANTICORE 134 
#define  USB_DEVICE_ID_KYE_EASYPEN_I405X 133 
#define  USB_DEVICE_ID_KYE_EASYPEN_M406XE 132 
#define  USB_DEVICE_ID_KYE_EASYPEN_M610X 131 
#define  USB_DEVICE_ID_KYE_MOUSEPEN_I608X 130 
#define  USB_DEVICE_ID_KYE_MOUSEPEN_I608X_V2 129 
#define  USB_DEVICE_ID_KYE_PENSKETCH_M912 128 
 int /*<<< orphan*/  hid_err (struct hid_device*,char*) ; 
 int /*<<< orphan*/  hid_hw_close (struct hid_device*) ; 
 int /*<<< orphan*/  hid_hw_open (struct hid_device*) ; 
 int hid_hw_start (struct hid_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_hw_stop (struct hid_device*) ; 
 int hid_parse (struct hid_device*) ; 
 int kye_tablet_enable (struct hid_device*) ; 

__attribute__((used)) static int kye_probe(struct hid_device *hdev, const struct hid_device_id *id)
{
	int ret;

	ret = hid_parse(hdev);
	if (ret) {
		hid_err(hdev, "parse failed\n");
		goto err;
	}

	ret = hid_hw_start(hdev, HID_CONNECT_DEFAULT);
	if (ret) {
		hid_err(hdev, "hw start failed\n");
		goto err;
	}

	switch (id->product) {
	case USB_DEVICE_ID_KYE_EASYPEN_I405X:
	case USB_DEVICE_ID_KYE_MOUSEPEN_I608X:
	case USB_DEVICE_ID_KYE_MOUSEPEN_I608X_V2:
	case USB_DEVICE_ID_KYE_EASYPEN_M610X:
	case USB_DEVICE_ID_KYE_EASYPEN_M406XE:
	case USB_DEVICE_ID_KYE_PENSKETCH_M912:
		ret = kye_tablet_enable(hdev);
		if (ret) {
			hid_err(hdev, "tablet enabling failed\n");
			goto enabling_err;
		}
		break;
	case USB_DEVICE_ID_GENIUS_MANTICORE:
		/*
		 * The manticore keyboard needs to have all the interfaces
		 * opened at least once to be fully functional.
		 */
		if (hid_hw_open(hdev))
			hid_hw_close(hdev);
		break;
	}

	return 0;
enabling_err:
	hid_hw_stop(hdev);
err:
	return ret;
}