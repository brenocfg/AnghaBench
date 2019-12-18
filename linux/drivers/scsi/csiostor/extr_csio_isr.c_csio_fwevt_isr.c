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
struct csio_hw {int /*<<< orphan*/  pdev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  CSIO_INC_STATS (struct csio_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  csio_fwevt_handler (struct csio_hw*) ; 
 int /*<<< orphan*/  n_pcich_offline ; 
 int pci_channel_offline (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static irqreturn_t
csio_fwevt_isr(int irq, void *dev_id)
{
	struct csio_hw *hw = (struct csio_hw *) dev_id;

	if (unlikely(!hw))
		return IRQ_NONE;

	if (unlikely(pci_channel_offline(hw->pdev))) {
		CSIO_INC_STATS(hw, n_pcich_offline);
		return IRQ_NONE;
	}

	csio_fwevt_handler(hw);

	return IRQ_HANDLED;
}