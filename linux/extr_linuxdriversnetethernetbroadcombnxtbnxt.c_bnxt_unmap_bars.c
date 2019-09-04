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
struct pci_dev {int dummy; } ;
struct bnxt {int /*<<< orphan*/ * bar0; int /*<<< orphan*/ * bar1; int /*<<< orphan*/ * bar2; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bnxt_unmap_bars(struct bnxt *bp, struct pci_dev *pdev)
{
	if (bp->bar2) {
		pci_iounmap(pdev, bp->bar2);
		bp->bar2 = NULL;
	}

	if (bp->bar1) {
		pci_iounmap(pdev, bp->bar1);
		bp->bar1 = NULL;
	}

	if (bp->bar0) {
		pci_iounmap(pdev, bp->bar0);
		bp->bar0 = NULL;
	}
}