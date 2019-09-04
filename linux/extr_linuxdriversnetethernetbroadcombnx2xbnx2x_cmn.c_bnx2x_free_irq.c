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
struct bnx2x {int flags; TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int BNX2X_NUM_ETH_QUEUES (struct bnx2x*) ; 
 int CNIC_SUPPORT (struct bnx2x*) ; 
 scalar_t__ IS_PF (struct bnx2x*) ; 
 int USING_MSIX_FLAG ; 
 int USING_SINGLE_MSIX_FLAG ; 
 int /*<<< orphan*/  bnx2x_free_msix_irqs (struct bnx2x*,int) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,TYPE_1__*) ; 

void bnx2x_free_irq(struct bnx2x *bp)
{
	if (bp->flags & USING_MSIX_FLAG &&
	    !(bp->flags & USING_SINGLE_MSIX_FLAG)) {
		int nvecs = BNX2X_NUM_ETH_QUEUES(bp) + CNIC_SUPPORT(bp);

		/* vfs don't have a default status block */
		if (IS_PF(bp))
			nvecs++;

		bnx2x_free_msix_irqs(bp, nvecs);
	} else {
		free_irq(bp->dev->irq, bp->dev);
	}
}