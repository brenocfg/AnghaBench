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
struct ilo_hwinfo {int /*<<< orphan*/  alloc_lock; TYPE_1__** ccb_alloc; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  ccb_waitq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  clear_pending_db (struct ilo_hwinfo*,int) ; 
 int get_device_outbound (struct ilo_hwinfo*) ; 
 int /*<<< orphan*/  ilo_set_reset (struct ilo_hwinfo*) ; 
 scalar_t__ is_db_reset (int) ; 
 int max_ccb ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t ilo_isr(int irq, void *data)
{
	struct ilo_hwinfo *hw = data;
	int pending, i;

	spin_lock(&hw->alloc_lock);

	/* check for ccbs which have data */
	pending = get_device_outbound(hw);
	if (!pending) {
		spin_unlock(&hw->alloc_lock);
		return IRQ_NONE;
	}

	if (is_db_reset(pending)) {
		/* wake up all ccbs if the device was reset */
		pending = -1;
		ilo_set_reset(hw);
	}

	for (i = 0; i < max_ccb; i++) {
		if (!hw->ccb_alloc[i])
			continue;
		if (pending & (1 << i))
			wake_up_interruptible(&hw->ccb_alloc[i]->ccb_waitq);
	}

	/* clear the device of the channels that have been handled */
	clear_pending_db(hw, pending);

	spin_unlock(&hw->alloc_lock);

	return IRQ_HANDLED;
}