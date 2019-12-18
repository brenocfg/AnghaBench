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
struct csio_hw {int flags; int /*<<< orphan*/  lock; int /*<<< orphan*/  evtq_work; } ;

/* Variables and functions */
 int CSIO_HWF_FWEVT_PENDING ; 
 int csio_fwevtq_handler (struct csio_hw*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
csio_fwevt_handler(struct csio_hw *hw)
{
	int rv;
	unsigned long flags;

	rv = csio_fwevtq_handler(hw);

	spin_lock_irqsave(&hw->lock, flags);
	if (rv == 0 && !(hw->flags & CSIO_HWF_FWEVT_PENDING)) {
		hw->flags |= CSIO_HWF_FWEVT_PENDING;
		spin_unlock_irqrestore(&hw->lock, flags);
		schedule_work(&hw->evtq_work);
		return;
	}
	spin_unlock_irqrestore(&hw->lock, flags);

}