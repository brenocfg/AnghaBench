#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct bnx2x {int flags; TYPE_3__* dev; TYPE_2__* msix_table; TYPE_1__* pdev; } ;
struct TYPE_6__ {int /*<<< orphan*/  irq; } ;
struct TYPE_5__ {int /*<<< orphan*/  vector; } ;
struct TYPE_4__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*,int) ; 
 int USING_MSIX_FLAG ; 
 int USING_MSI_FLAG ; 
 int USING_SINGLE_MSIX_FLAG ; 
 int bnx2x_req_irq (struct bnx2x*) ; 
 int bnx2x_req_msix_irqs (struct bnx2x*) ; 
 int /*<<< orphan*/  netdev_info (TYPE_3__*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bnx2x_setup_irqs(struct bnx2x *bp)
{
	int rc = 0;
	if (bp->flags & USING_MSIX_FLAG &&
	    !(bp->flags & USING_SINGLE_MSIX_FLAG)) {
		rc = bnx2x_req_msix_irqs(bp);
		if (rc)
			return rc;
	} else {
		rc = bnx2x_req_irq(bp);
		if (rc) {
			BNX2X_ERR("IRQ request failed  rc %d, aborting\n", rc);
			return rc;
		}
		if (bp->flags & USING_MSI_FLAG) {
			bp->dev->irq = bp->pdev->irq;
			netdev_info(bp->dev, "using MSI IRQ %d\n",
				    bp->dev->irq);
		}
		if (bp->flags & USING_MSIX_FLAG) {
			bp->dev->irq = bp->msix_table[0].vector;
			netdev_info(bp->dev, "using MSIX IRQ %d\n",
				    bp->dev->irq);
		}
	}

	return 0;
}