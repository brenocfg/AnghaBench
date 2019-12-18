#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usbhid_device {int /*<<< orphan*/  iofl; TYPE_1__* intf; } ;
struct hid_device {int quirks; struct usbhid_device* driver_data; } ;
struct TYPE_3__ {int needs_remote_wakeup; } ;

/* Variables and functions */
 int EBUSY ; 
 int EIO ; 
 int ENOSPC ; 
 int /*<<< orphan*/  HID_IN_POLLING ; 
 int /*<<< orphan*/  HID_OPENED ; 
 int HID_QUIRK_ALWAYS_POLL ; 
 int /*<<< orphan*/  HID_RESUME_RUNNING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hid_io_error (struct hid_device*) ; 
 int hid_start_in (struct hid_device*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int usb_autopm_get_interface (TYPE_1__*) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (TYPE_1__*) ; 

__attribute__((used)) static int usbhid_open(struct hid_device *hid)
{
	struct usbhid_device *usbhid = hid->driver_data;
	int res;

	set_bit(HID_OPENED, &usbhid->iofl);

	if (hid->quirks & HID_QUIRK_ALWAYS_POLL)
		return 0;

	res = usb_autopm_get_interface(usbhid->intf);
	/* the device must be awake to reliably request remote wakeup */
	if (res < 0) {
		clear_bit(HID_OPENED, &usbhid->iofl);
		return -EIO;
	}

	usbhid->intf->needs_remote_wakeup = 1;

	set_bit(HID_RESUME_RUNNING, &usbhid->iofl);
	set_bit(HID_IN_POLLING, &usbhid->iofl);

	res = hid_start_in(hid);
	if (res) {
		if (res != -ENOSPC) {
			hid_io_error(hid);
			res = 0;
		} else {
			/* no use opening if resources are insufficient */
			res = -EBUSY;
			clear_bit(HID_OPENED, &usbhid->iofl);
			clear_bit(HID_IN_POLLING, &usbhid->iofl);
			usbhid->intf->needs_remote_wakeup = 0;
		}
	}

	usb_autopm_put_interface(usbhid->intf);

	/*
	 * In case events are generated while nobody was listening,
	 * some are released when the device is re-opened.
	 * Wait 50 msec for the queue to empty before allowing events
	 * to go through hid.
	 */
	if (res == 0)
		msleep(50);

	clear_bit(HID_RESUME_RUNNING, &usbhid->iofl);
	return res;
}