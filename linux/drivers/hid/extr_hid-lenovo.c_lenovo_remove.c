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

/* Variables and functions */
#define  USB_DEVICE_ID_LENOVO_CBTKBD 130 
#define  USB_DEVICE_ID_LENOVO_CUSBKBD 129 
#define  USB_DEVICE_ID_LENOVO_TPKBD 128 
 int /*<<< orphan*/  hid_hw_stop (struct hid_device*) ; 
 int /*<<< orphan*/  lenovo_remove_cptkbd (struct hid_device*) ; 
 int /*<<< orphan*/  lenovo_remove_tpkbd (struct hid_device*) ; 

__attribute__((used)) static void lenovo_remove(struct hid_device *hdev)
{
	switch (hdev->product) {
	case USB_DEVICE_ID_LENOVO_TPKBD:
		lenovo_remove_tpkbd(hdev);
		break;
	case USB_DEVICE_ID_LENOVO_CUSBKBD:
	case USB_DEVICE_ID_LENOVO_CBTKBD:
		lenovo_remove_cptkbd(hdev);
		break;
	}

	hid_hw_stop(hdev);
}