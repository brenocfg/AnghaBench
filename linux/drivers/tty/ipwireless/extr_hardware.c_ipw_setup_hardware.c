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
struct ipw_hardware {scalar_t__ hw_version; int /*<<< orphan*/  lock; TYPE_1__* memregs_CCR; scalar_t__ base_port; } ;
struct TYPE_2__ {int /*<<< orphan*/  reg_config_and_status; } ;

/* Variables and functions */
 int DCR_RXRESET ; 
 int DCR_TXRESET ; 
 scalar_t__ HW_VERSION_1 ; 
 int IER_RXENABLED ; 
 int IER_TXENABLED ; 
 scalar_t__ IODCR ; 
 scalar_t__ IOIER ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 
 unsigned short readw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writew (unsigned short,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipw_setup_hardware(struct ipw_hardware *hw)
{
	unsigned long flags;

	spin_lock_irqsave(&hw->lock, flags);
	if (hw->hw_version == HW_VERSION_1) {
		/* Reset RX FIFO */
		outw(DCR_RXRESET, hw->base_port + IODCR);
		/* SB: Reset TX FIFO */
		outw(DCR_TXRESET, hw->base_port + IODCR);

		/* Enable TX and RX interrupts. */
		outw(IER_TXENABLED | IER_RXENABLED, hw->base_port + IOIER);
	} else {
		/*
		 * Set INTRACK bit (bit 0), which means we must explicitly
		 * acknowledge interrupts by clearing bit 2 of reg_config_and_status.
		 */
		unsigned short csr = readw(&hw->memregs_CCR->reg_config_and_status);

		csr |= 1;
		writew(csr, &hw->memregs_CCR->reg_config_and_status);
	}
	spin_unlock_irqrestore(&hw->lock, flags);
}