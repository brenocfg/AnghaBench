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
struct bnxt {int flags; int /*<<< orphan*/ * irq_tbl; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int BNXT_FLAG_USING_MSIX ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_disable_msix (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnxt_clear_int_mode(struct bnxt *bp)
{
	if (bp->flags & BNXT_FLAG_USING_MSIX)
		pci_disable_msix(bp->pdev);

	kfree(bp->irq_tbl);
	bp->irq_tbl = NULL;
	bp->flags &= ~BNXT_FLAG_USING_MSIX;
}