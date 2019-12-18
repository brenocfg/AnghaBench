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
struct usbhid_device {int /*<<< orphan*/  intf; } ;
struct hid_device {struct usbhid_device* driver_data; } ;

/* Variables and functions */
#define  PM_HINT_FULLON 129 
#define  PM_HINT_NORMAL 128 
 int usb_autopm_get_interface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usbhid_power(struct hid_device *hid, int lvl)
{
	struct usbhid_device *usbhid = hid->driver_data;
	int r = 0;

	switch (lvl) {
	case PM_HINT_FULLON:
		r = usb_autopm_get_interface(usbhid->intf);
		break;

	case PM_HINT_NORMAL:
		usb_autopm_put_interface(usbhid->intf);
		break;
	}

	return r;
}