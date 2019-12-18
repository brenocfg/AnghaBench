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
struct bnx2_irq {int requested; int /*<<< orphan*/  name; int /*<<< orphan*/  handler; int /*<<< orphan*/  vector; } ;
struct bnx2 {int flags; int irq_nvecs; int /*<<< orphan*/ * bnx2_napi; struct bnx2_irq* irq_tbl; } ;

/* Variables and functions */
 int BNX2_FLAG_USING_MSI_OR_MSIX ; 
 unsigned long IRQF_SHARED ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
bnx2_request_irq(struct bnx2 *bp)
{
	unsigned long flags;
	struct bnx2_irq *irq;
	int rc = 0, i;

	if (bp->flags & BNX2_FLAG_USING_MSI_OR_MSIX)
		flags = 0;
	else
		flags = IRQF_SHARED;

	for (i = 0; i < bp->irq_nvecs; i++) {
		irq = &bp->irq_tbl[i];
		rc = request_irq(irq->vector, irq->handler, flags, irq->name,
				 &bp->bnx2_napi[i]);
		if (rc)
			break;
		irq->requested = 1;
	}
	return rc;
}