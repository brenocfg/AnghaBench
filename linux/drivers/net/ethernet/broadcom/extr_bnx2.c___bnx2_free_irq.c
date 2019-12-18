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
struct bnx2_irq {scalar_t__ requested; int /*<<< orphan*/  vector; } ;
struct bnx2 {int irq_nvecs; int /*<<< orphan*/ * bnx2_napi; struct bnx2_irq* irq_tbl; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
__bnx2_free_irq(struct bnx2 *bp)
{
	struct bnx2_irq *irq;
	int i;

	for (i = 0; i < bp->irq_nvecs; i++) {
		irq = &bp->irq_tbl[i];
		if (irq->requested)
			free_irq(irq->vector, &bp->bnx2_napi[i]);
		irq->requested = 0;
	}
}