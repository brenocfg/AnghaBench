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
struct bnxt {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  bnxt_unmap_bars (struct bnxt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_is_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnxt_cleanup_pci(struct bnxt *bp)
{
	bnxt_unmap_bars(bp, bp->pdev);
	pci_release_regions(bp->pdev);
	if (pci_is_enabled(bp->pdev))
		pci_disable_device(bp->pdev);
}