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
struct usbhid_device {int /*<<< orphan*/  lock; int /*<<< orphan*/  iofl; int /*<<< orphan*/  urbin; } ;
struct hid_device {struct usbhid_device* driver_data; } ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  HID_DISCONNECTED ; 
 int /*<<< orphan*/  HID_IN_POLLING ; 
 int /*<<< orphan*/  HID_IN_RUNNING ; 
 int /*<<< orphan*/  HID_NO_BANDWIDTH ; 
 int /*<<< orphan*/  HID_SUSPENDED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hid_start_in(struct hid_device *hid)
{
	unsigned long flags;
	int rc = 0;
	struct usbhid_device *usbhid = hid->driver_data;

	spin_lock_irqsave(&usbhid->lock, flags);
	if (test_bit(HID_IN_POLLING, &usbhid->iofl) &&
	    !test_bit(HID_DISCONNECTED, &usbhid->iofl) &&
	    !test_bit(HID_SUSPENDED, &usbhid->iofl) &&
	    !test_and_set_bit(HID_IN_RUNNING, &usbhid->iofl)) {
		rc = usb_submit_urb(usbhid->urbin, GFP_ATOMIC);
		if (rc != 0) {
			clear_bit(HID_IN_RUNNING, &usbhid->iofl);
			if (rc == -ENOSPC)
				set_bit(HID_NO_BANDWIDTH, &usbhid->iofl);
		} else {
			clear_bit(HID_NO_BANDWIDTH, &usbhid->iofl);
		}
	}
	spin_unlock_irqrestore(&usbhid->lock, flags);
	return rc;
}