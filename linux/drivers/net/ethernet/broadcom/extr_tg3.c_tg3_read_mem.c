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
struct tg3 {int /*<<< orphan*/  indirect_lock; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 scalar_t__ ASIC_REV_5906 ; 
 scalar_t__ NIC_SRAM_STATS_BLK ; 
 scalar_t__ NIC_SRAM_TX_BUFFER_DESC ; 
 int /*<<< orphan*/  SRAM_USE_CONFIG ; 
 int /*<<< orphan*/  TG3PCI_MEM_WIN_BASE_ADDR ; 
 int /*<<< orphan*/  TG3PCI_MEM_WIN_DATA ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ tg3_asic_rev (struct tg3*) ; 
 scalar_t__ tg3_flag (struct tg3*,int /*<<< orphan*/ ) ; 
 scalar_t__ tr32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw32_f (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void tg3_read_mem(struct tg3 *tp, u32 off, u32 *val)
{
	unsigned long flags;

	if (tg3_asic_rev(tp) == ASIC_REV_5906 &&
	    (off >= NIC_SRAM_STATS_BLK) && (off < NIC_SRAM_TX_BUFFER_DESC)) {
		*val = 0;
		return;
	}

	spin_lock_irqsave(&tp->indirect_lock, flags);
	if (tg3_flag(tp, SRAM_USE_CONFIG)) {
		pci_write_config_dword(tp->pdev, TG3PCI_MEM_WIN_BASE_ADDR, off);
		pci_read_config_dword(tp->pdev, TG3PCI_MEM_WIN_DATA, val);

		/* Always leave this as zero. */
		pci_write_config_dword(tp->pdev, TG3PCI_MEM_WIN_BASE_ADDR, 0);
	} else {
		tw32_f(TG3PCI_MEM_WIN_BASE_ADDR, off);
		*val = tr32(TG3PCI_MEM_WIN_DATA);

		/* Always leave this as zero. */
		tw32_f(TG3PCI_MEM_WIN_BASE_ADDR, 0);
	}
	spin_unlock_irqrestore(&tp->indirect_lock, flags);
}