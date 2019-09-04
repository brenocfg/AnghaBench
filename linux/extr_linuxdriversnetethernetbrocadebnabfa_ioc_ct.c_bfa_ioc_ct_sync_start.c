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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  alt_ioc_fwstate; int /*<<< orphan*/  ioc_fwstate; int /*<<< orphan*/  ioc_usage_reg; int /*<<< orphan*/  ioc_fail_sync; } ;
struct bfa_ioc {TYPE_1__ ioc_regs; } ;

/* Variables and functions */
 int BFI_IOC_UNINIT ; 
 int bfa_ioc_ct_get_sync_reqd (int) ; 
 int bfa_ioc_ct_sync_complete (struct bfa_ioc*) ; 
 int bfa_ioc_ct_sync_pos (struct bfa_ioc*) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
bfa_ioc_ct_sync_start(struct bfa_ioc *ioc)
{
	u32 r32 = readl(ioc->ioc_regs.ioc_fail_sync);
	u32 sync_reqd = bfa_ioc_ct_get_sync_reqd(r32);

	/*
	 * Driver load time.  If the sync required bit for this PCI fn
	 * is set, it is due to an unclean exit by the driver for this
	 * PCI fn in the previous incarnation. Whoever comes here first
	 * should clean it up, no matter which PCI fn.
	 */

	if (sync_reqd & bfa_ioc_ct_sync_pos(ioc)) {
		writel(0, ioc->ioc_regs.ioc_fail_sync);
		writel(1, ioc->ioc_regs.ioc_usage_reg);
		writel(BFI_IOC_UNINIT, ioc->ioc_regs.ioc_fwstate);
		writel(BFI_IOC_UNINIT, ioc->ioc_regs.alt_ioc_fwstate);
		return true;
	}

	return bfa_ioc_ct_sync_complete(ioc);
}