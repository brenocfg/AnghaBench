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
struct usbhid_device {int /*<<< orphan*/  wait; int /*<<< orphan*/  intf; int /*<<< orphan*/  iofl; int /*<<< orphan*/  ctrltail; int /*<<< orphan*/  ctrlhead; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HID_CTRL_RUNNING ; 
 int /*<<< orphan*/  HID_RESET_PENDING ; 
 int /*<<< orphan*/  HID_SUSPENDED ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hid_dbg (struct hid_device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ hid_submit_ctrl (struct hid_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int usb_autopm_get_interface_async (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_autopm_put_interface_async (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_autopm_put_interface_no_suspend (int /*<<< orphan*/ ) ; 
 struct hid_device* usb_get_intfdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int usbhid_restart_ctrl_queue(struct usbhid_device *usbhid)
{
	struct hid_device *hid = usb_get_intfdata(usbhid->intf);
	int kicked;
	int r;

	WARN_ON(hid == NULL);
	if (!hid || test_bit(HID_RESET_PENDING, &usbhid->iofl) ||
			test_bit(HID_SUSPENDED, &usbhid->iofl))
		return 0;

	if ((kicked = (usbhid->ctrlhead != usbhid->ctrltail))) {
		hid_dbg(hid, "Kicking head %d tail %d", usbhid->ctrlhead, usbhid->ctrltail);

		/* Try to wake up from autosuspend... */
		r = usb_autopm_get_interface_async(usbhid->intf);
		if (r < 0)
			return r;

		/*
		 * If still suspended, don't submit.  Submission will
		 * occur if/when resume drains the queue.
		 */
		if (test_bit(HID_SUSPENDED, &usbhid->iofl)) {
			usb_autopm_put_interface_no_suspend(usbhid->intf);
			return r;
		}

		/* Asynchronously flush queue. */
		set_bit(HID_CTRL_RUNNING, &usbhid->iofl);
		if (hid_submit_ctrl(hid)) {
			clear_bit(HID_CTRL_RUNNING, &usbhid->iofl);
			usb_autopm_put_interface_async(usbhid->intf);
		}
		wake_up(&usbhid->wait);
	}
	return kicked;
}