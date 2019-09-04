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
struct bnxt {int cp_nr_rings; TYPE_1__* irq_tbl; int /*<<< orphan*/  intr_sem; } ;
struct TYPE_2__ {int /*<<< orphan*/  vector; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int bnxt_cp_num_to_irq_num (struct bnxt*,int) ; 
 int /*<<< orphan*/  bnxt_disable_int (struct bnxt*) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnxt_disable_int_sync(struct bnxt *bp)
{
	int i;

	atomic_inc(&bp->intr_sem);

	bnxt_disable_int(bp);
	for (i = 0; i < bp->cp_nr_rings; i++) {
		int map_idx = bnxt_cp_num_to_irq_num(bp, i);

		synchronize_irq(bp->irq_tbl[map_idx].vector);
	}
}