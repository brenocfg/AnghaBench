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
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  pci_win_rd_data; int /*<<< orphan*/  pci_win_rd_addr_lo; int /*<<< orphan*/  pci_win_rd_addr_hi; } ;
struct octeon_device {scalar_t__ chip_id; int /*<<< orphan*/  pci_win_lock; TYPE_1__ reg_list; } ;

/* Variables and functions */
 scalar_t__ OCTEON_CN23XX_PF_VID ; 
 scalar_t__ OCTEON_CN66XX ; 
 scalar_t__ OCTEON_CN68XX ; 
 int readl (int /*<<< orphan*/ ) ; 
 int readq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

u64 lio_pci_readq(struct octeon_device *oct, u64 addr)
{
	u64 val64;
	unsigned long flags;
	u32 val32, addrhi;

	spin_lock_irqsave(&oct->pci_win_lock, flags);

	/* The windowed read happens when the LSB of the addr is written.
	 * So write MSB first
	 */
	addrhi = (addr >> 32);
	if ((oct->chip_id == OCTEON_CN66XX) ||
	    (oct->chip_id == OCTEON_CN68XX) ||
	    (oct->chip_id == OCTEON_CN23XX_PF_VID))
		addrhi |= 0x00060000;
	writel(addrhi, oct->reg_list.pci_win_rd_addr_hi);

	/* Read back to preserve ordering of writes */
	val32 = readl(oct->reg_list.pci_win_rd_addr_hi);

	writel(addr & 0xffffffff, oct->reg_list.pci_win_rd_addr_lo);
	val32 = readl(oct->reg_list.pci_win_rd_addr_lo);

	val64 = readq(oct->reg_list.pci_win_rd_data);

	spin_unlock_irqrestore(&oct->pci_win_lock, flags);

	return val64;
}