#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wlandevice {struct hfa384x* priv; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
struct hfa384x {TYPE_1__ ctlxq; int /*<<< orphan*/  usb_work; int /*<<< orphan*/  usb_flags; TYPE_2__* wlandev; } ;
struct TYPE_4__ {int /*<<< orphan*/  hwremoved; } ;

/* Variables and functions */
 int /*<<< orphan*/  WORK_RX_HALT ; 
 int /*<<< orphan*/  WORK_TX_HALT ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void hfa384x_tx_timeout(struct wlandevice *wlandev)
{
	struct hfa384x *hw = wlandev->priv;
	unsigned long flags;

	spin_lock_irqsave(&hw->ctlxq.lock, flags);

	if (!hw->wlandev->hwremoved) {
		int sched;

		sched = !test_and_set_bit(WORK_TX_HALT, &hw->usb_flags);
		sched |= !test_and_set_bit(WORK_RX_HALT, &hw->usb_flags);
		if (sched)
			schedule_work(&hw->usb_work);
	}

	spin_unlock_irqrestore(&hw->ctlxq.lock, flags);
}