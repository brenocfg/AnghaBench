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
 int /*<<< orphan*/  DMAE_REG_BACKWARD_COMP_EN ; 
 int /*<<< orphan*/  PCI_EXT_CAP_ID_SRIOV ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_find_ext_capability (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void bnx2x_iov_init_dmae(struct bnx2x *bp)
{
	if (pci_find_ext_capability(bp->pdev, PCI_EXT_CAP_ID_SRIOV))
		REG_WR(bp, DMAE_REG_BACKWARD_COMP_EN, 0);
}