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
typedef  scalar_t__ u32 ;
struct tg3 {scalar_t__ grc_local_ctrl; int /*<<< orphan*/  pdev; int /*<<< orphan*/  indirect_lock; } ;

/* Variables and functions */
 scalar_t__ GRC_LCLCTRL_CLEARINT ; 
 scalar_t__ MAILBOX_INTERRUPT_0 ; 
 scalar_t__ MAILBOX_RCVRET_CON_IDX_0 ; 
 scalar_t__ TG3PCI_MISC_LOCAL_CTRL ; 
 scalar_t__ TG3PCI_RCV_RET_RING_CON_IDX ; 
 scalar_t__ TG3PCI_REG_BASE_ADDR ; 
 scalar_t__ TG3PCI_REG_DATA ; 
 scalar_t__ TG3PCI_STD_RING_PROD_IDX ; 
 scalar_t__ TG3_64BIT_REG_LOW ; 
 scalar_t__ TG3_RX_STD_PROD_IDX_REG ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void tg3_write_indirect_mbox(struct tg3 *tp, u32 off, u32 val)
{
	unsigned long flags;

	if (off == (MAILBOX_RCVRET_CON_IDX_0 + TG3_64BIT_REG_LOW)) {
		pci_write_config_dword(tp->pdev, TG3PCI_RCV_RET_RING_CON_IDX +
				       TG3_64BIT_REG_LOW, val);
		return;
	}
	if (off == TG3_RX_STD_PROD_IDX_REG) {
		pci_write_config_dword(tp->pdev, TG3PCI_STD_RING_PROD_IDX +
				       TG3_64BIT_REG_LOW, val);
		return;
	}

	spin_lock_irqsave(&tp->indirect_lock, flags);
	pci_write_config_dword(tp->pdev, TG3PCI_REG_BASE_ADDR, off + 0x5600);
	pci_write_config_dword(tp->pdev, TG3PCI_REG_DATA, val);
	spin_unlock_irqrestore(&tp->indirect_lock, flags);

	/* In indirect mode when disabling interrupts, we also need
	 * to clear the interrupt bit in the GRC local ctrl register.
	 */
	if ((off == (MAILBOX_INTERRUPT_0 + TG3_64BIT_REG_LOW)) &&
	    (val == 0x1)) {
		pci_write_config_dword(tp->pdev, TG3PCI_MISC_LOCAL_CTRL,
				       tp->grc_local_ctrl|GRC_LCLCTRL_CLEARINT);
	}
}