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
struct usbhid_device {int /*<<< orphan*/  iofl; int /*<<< orphan*/  wait; } ;
struct hid_device {struct usbhid_device* driver_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  HID_CTRL_RUNNING ; 
 int /*<<< orphan*/  HID_OUT_RUNNING ; 
 int HZ ; 
 int /*<<< orphan*/  dbg_hid (char*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int usbhid_wait_io(struct hid_device *hid)
{
	struct usbhid_device *usbhid = hid->driver_data;

	if (!wait_event_timeout(usbhid->wait,
				(!test_bit(HID_CTRL_RUNNING, &usbhid->iofl) &&
				!test_bit(HID_OUT_RUNNING, &usbhid->iofl)),
					10*HZ)) {
		dbg_hid("timeout waiting for ctrl or out queue to clear\n");
		return -1;
	}

	return 0;
}