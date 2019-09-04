#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct usbhid_device {TYPE_1__* intf; int /*<<< orphan*/  urbin; int /*<<< orphan*/  lock; int /*<<< orphan*/  iofl; } ;
struct hid_device {int quirks; struct usbhid_device* driver_data; } ;
struct TYPE_2__ {scalar_t__ needs_remote_wakeup; } ;

/* Variables and functions */
 int /*<<< orphan*/  HID_IN_POLLING ; 
 int /*<<< orphan*/  HID_OPENED ; 
 int HID_QUIRK_ALWAYS_POLL ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hid_cancel_delayed_stuff (struct usbhid_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usbhid_close(struct hid_device *hid)
{
	struct usbhid_device *usbhid = hid->driver_data;

	/*
	 * Make sure we don't restart data acquisition due to
	 * a resumption we no longer care about by avoiding racing
	 * with hid_start_in().
	 */
	spin_lock_irq(&usbhid->lock);
	clear_bit(HID_OPENED, &usbhid->iofl);
	if (!(hid->quirks & HID_QUIRK_ALWAYS_POLL))
		clear_bit(HID_IN_POLLING, &usbhid->iofl);
	spin_unlock_irq(&usbhid->lock);

	if (hid->quirks & HID_QUIRK_ALWAYS_POLL)
		return;

	hid_cancel_delayed_stuff(usbhid);
	usb_kill_urb(usbhid->urbin);
	usbhid->intf->needs_remote_wakeup = 0;
}