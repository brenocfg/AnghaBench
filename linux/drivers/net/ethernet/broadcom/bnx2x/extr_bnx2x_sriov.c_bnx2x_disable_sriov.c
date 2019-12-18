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
struct bnx2x {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_MSG_IOV ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pci_disable_sriov (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_vfs_assigned (int /*<<< orphan*/ ) ; 

void bnx2x_disable_sriov(struct bnx2x *bp)
{
	if (pci_vfs_assigned(bp->pdev)) {
		DP(BNX2X_MSG_IOV,
		   "Unloading driver while VFs are assigned - VFs will not be deallocated\n");
		return;
	}

	pci_disable_sriov(bp->pdev);
}