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
struct csio_hw {int flags; int /*<<< orphan*/  lock; int /*<<< orphan*/  evtq_work; int /*<<< orphan*/  pdev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int CSIO_HWF_FWEVT_PENDING ; 
 int /*<<< orphan*/  CSIO_INC_STATS (struct csio_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  csio_hw_slow_intr_handler (struct csio_hw*) ; 
 int csio_mb_isr_handler (struct csio_hw*) ; 
 int /*<<< orphan*/  n_pcich_offline ; 
 int pci_channel_offline (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static irqreturn_t
csio_nondata_isr(int irq, void *dev_id)
{
	struct csio_hw *hw = (struct csio_hw *) dev_id;
	int rv;
	unsigned long flags;

	if (unlikely(!hw))
		return IRQ_NONE;

	if (unlikely(pci_channel_offline(hw->pdev))) {
		CSIO_INC_STATS(hw, n_pcich_offline);
		return IRQ_NONE;
	}

	spin_lock_irqsave(&hw->lock, flags);
	csio_hw_slow_intr_handler(hw);
	rv = csio_mb_isr_handler(hw);

	if (rv == 0 && !(hw->flags & CSIO_HWF_FWEVT_PENDING)) {
		hw->flags |= CSIO_HWF_FWEVT_PENDING;
		spin_unlock_irqrestore(&hw->lock, flags);
		schedule_work(&hw->evtq_work);
		return IRQ_HANDLED;
	}
	spin_unlock_irqrestore(&hw->lock, flags);
	return IRQ_HANDLED;
}