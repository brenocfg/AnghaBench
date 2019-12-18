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
struct hid_device_id {int dummy; } ;
struct hid_device {scalar_t__ product; int rsize; } ;

/* Variables and functions */
 unsigned int HID_CONNECT_DEFAULT ; 
 unsigned int HID_CONNECT_HIDDEV_FORCE ; 
 unsigned int HID_CONNECT_HIDINPUT ; 
 scalar_t__ USB_DEVICE_ID_SAMSUNG_IR_REMOTE ; 
 int /*<<< orphan*/  hid_err (struct hid_device*,char*) ; 
 int hid_hw_start (struct hid_device*,unsigned int) ; 
 int hid_parse (struct hid_device*) ; 

__attribute__((used)) static int samsung_probe(struct hid_device *hdev,
		const struct hid_device_id *id)
{
	int ret;
	unsigned int cmask = HID_CONNECT_DEFAULT;

	ret = hid_parse(hdev);
	if (ret) {
		hid_err(hdev, "parse failed\n");
		goto err_free;
	}

	if (USB_DEVICE_ID_SAMSUNG_IR_REMOTE == hdev->product) {
		if (hdev->rsize == 184) {
			/* disable hidinput, force hiddev */
			cmask = (cmask & ~HID_CONNECT_HIDINPUT) |
				HID_CONNECT_HIDDEV_FORCE;
		}
	}

	ret = hid_hw_start(hdev, cmask);
	if (ret) {
		hid_err(hdev, "hw start failed\n");
		goto err_free;
	}

	return 0;
err_free:
	return ret;
}