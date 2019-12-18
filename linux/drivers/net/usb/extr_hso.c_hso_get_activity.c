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
struct hso_device {int is_active; TYPE_1__* usb; int /*<<< orphan*/  async_get_intf; } ;
struct TYPE_2__ {scalar_t__ state; } ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ USB_STATE_CONFIGURED ; 
 scalar_t__ USB_STATE_SUSPENDED ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_mark_last_busy (TYPE_1__*) ; 

__attribute__((used)) static int hso_get_activity(struct hso_device *hso_dev)
{
	if (hso_dev->usb->state == USB_STATE_SUSPENDED) {
		if (!hso_dev->is_active) {
			hso_dev->is_active = 1;
			schedule_work(&hso_dev->async_get_intf);
		}
	}

	if (hso_dev->usb->state != USB_STATE_CONFIGURED)
		return -EAGAIN;

	usb_mark_last_busy(hso_dev->usb);

	return 0;
}