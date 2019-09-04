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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  pci_win_wr_data_lo; int /*<<< orphan*/  pci_win_wr_data_hi; int /*<<< orphan*/  pci_win_wr_addr; } ;
struct octeon_device {int /*<<< orphan*/  pci_win_lock; TYPE_1__ reg_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeq (int,int /*<<< orphan*/ ) ; 

void lio_pci_writeq(struct octeon_device *oct,
		    u64 val,
		    u64 addr)
{
	u32 val32;
	unsigned long flags;

	spin_lock_irqsave(&oct->pci_win_lock, flags);

	writeq(addr, oct->reg_list.pci_win_wr_addr);

	/* The write happens when the LSB is written. So write MSB first. */
	writel(val >> 32, oct->reg_list.pci_win_wr_data_hi);
	/* Read the MSB to ensure ordering of writes. */
	val32 = readl(oct->reg_list.pci_win_wr_data_hi);

	writel(val & 0xffffffff, oct->reg_list.pci_win_wr_data_lo);

	spin_unlock_irqrestore(&oct->pci_win_lock, flags);
}