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
struct usbhid_device {int /*<<< orphan*/  lock; int /*<<< orphan*/  iofl; scalar_t__ urbout; scalar_t__ retry_delay; int /*<<< orphan*/  reset_work; } ;
struct hid_device {struct usbhid_device* driver_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  HID_CLEAR_HALT ; 
 int /*<<< orphan*/  HID_CTRL_RUNNING ; 
 int /*<<< orphan*/  HID_OUT_RUNNING ; 
 int /*<<< orphan*/  HID_RESET_PENDING ; 
 int /*<<< orphan*/  HID_STARTED ; 
 int /*<<< orphan*/  HID_SUSPENDED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hid_io_error (struct hid_device*) ; 
 scalar_t__ hid_start_in (struct hid_device*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbhid_mark_busy (struct usbhid_device*) ; 
 int /*<<< orphan*/  usbhid_restart_ctrl_queue (struct usbhid_device*) ; 
 int /*<<< orphan*/  usbhid_restart_out_queue (struct usbhid_device*) ; 

__attribute__((used)) static void hid_restart_io(struct hid_device *hid)
{
	struct usbhid_device *usbhid = hid->driver_data;
	int clear_halt = test_bit(HID_CLEAR_HALT, &usbhid->iofl);
	int reset_pending = test_bit(HID_RESET_PENDING, &usbhid->iofl);

	spin_lock_irq(&usbhid->lock);
	clear_bit(HID_SUSPENDED, &usbhid->iofl);
	usbhid_mark_busy(usbhid);

	if (clear_halt || reset_pending)
		schedule_work(&usbhid->reset_work);
	usbhid->retry_delay = 0;
	spin_unlock_irq(&usbhid->lock);

	if (reset_pending || !test_bit(HID_STARTED, &usbhid->iofl))
		return;

	if (!clear_halt) {
		if (hid_start_in(hid) < 0)
			hid_io_error(hid);
	}

	spin_lock_irq(&usbhid->lock);
	if (usbhid->urbout && !test_bit(HID_OUT_RUNNING, &usbhid->iofl))
		usbhid_restart_out_queue(usbhid);
	if (!test_bit(HID_CTRL_RUNNING, &usbhid->iofl))
		usbhid_restart_ctrl_queue(usbhid);
	spin_unlock_irq(&usbhid->lock);
}