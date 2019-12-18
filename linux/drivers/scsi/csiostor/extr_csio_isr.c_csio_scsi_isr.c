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
struct csio_q {scalar_t__ owner; } ;
struct csio_hw {int /*<<< orphan*/  pdev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  CSIO_INC_STATS (struct csio_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  csio_scsi_isr_handler (struct csio_q*) ; 
 int /*<<< orphan*/  n_pcich_offline ; 
 int pci_channel_offline (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static irqreturn_t
csio_scsi_isr(int irq, void *dev_id)
{
	struct csio_q *iq = (struct csio_q *) dev_id;
	struct csio_hw *hw;

	if (unlikely(!iq))
		return IRQ_NONE;

	hw = (struct csio_hw *)iq->owner;

	if (unlikely(pci_channel_offline(hw->pdev))) {
		CSIO_INC_STATS(hw, n_pcich_offline);
		return IRQ_NONE;
	}

	csio_scsi_isr_handler(iq);

	return IRQ_HANDLED;
}