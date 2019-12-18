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
struct bnx2 {int irq_nvecs; TYPE_1__* irq_tbl; int /*<<< orphan*/  dev; int /*<<< orphan*/  intr_sem; } ;
struct TYPE_2__ {int /*<<< orphan*/  vector; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bnx2_disable_int (struct bnx2*) ; 
 int /*<<< orphan*/  netif_running (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bnx2_disable_int_sync(struct bnx2 *bp)
{
	int i;

	atomic_inc(&bp->intr_sem);
	if (!netif_running(bp->dev))
		return;

	bnx2_disable_int(bp);
	for (i = 0; i < bp->irq_nvecs; i++)
		synchronize_irq(bp->irq_tbl[i].vector);
}