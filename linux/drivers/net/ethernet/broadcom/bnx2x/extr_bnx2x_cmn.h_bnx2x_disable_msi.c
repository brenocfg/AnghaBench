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
struct bnx2x {int flags; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int USING_MSIX_FLAG ; 
 int USING_MSI_FLAG ; 
 int USING_SINGLE_MSIX_FLAG ; 
 int /*<<< orphan*/  pci_disable_msi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_msix (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void bnx2x_disable_msi(struct bnx2x *bp)
{
	if (bp->flags & USING_MSIX_FLAG) {
		pci_disable_msix(bp->pdev);
		bp->flags &= ~(USING_MSIX_FLAG | USING_SINGLE_MSIX_FLAG);
	} else if (bp->flags & USING_MSI_FLAG) {
		pci_disable_msi(bp->pdev);
		bp->flags &= ~USING_MSI_FLAG;
	}
}