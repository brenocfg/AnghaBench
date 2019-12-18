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
struct bnx2 {int flags; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int BNX2_FLAG_ONE_SHOT_MSI ; 
 int BNX2_FLAG_USING_MSI ; 
 int BNX2_FLAG_USING_MSIX ; 
 int BNX2_FLAG_USING_MSI_OR_MSIX ; 
 int /*<<< orphan*/  __bnx2_free_irq (struct bnx2*) ; 
 int /*<<< orphan*/  pci_disable_msi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_msix (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bnx2_free_irq(struct bnx2 *bp)
{

	__bnx2_free_irq(bp);
	if (bp->flags & BNX2_FLAG_USING_MSI)
		pci_disable_msi(bp->pdev);
	else if (bp->flags & BNX2_FLAG_USING_MSIX)
		pci_disable_msix(bp->pdev);

	bp->flags &= ~(BNX2_FLAG_USING_MSI_OR_MSIX | BNX2_FLAG_ONE_SHOT_MSI);
}