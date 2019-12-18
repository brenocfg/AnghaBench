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
struct bnx2x {int fp_array_size; TYPE_1__* ilt; TYPE_1__* msix_table; TYPE_1__* bnx2x_txq; TYPE_1__* fp_stats; TYPE_1__* sp_objs; TYPE_1__* fp; } ;
struct TYPE_2__ {struct TYPE_2__* tpa_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 

void bnx2x_free_mem_bp(struct bnx2x *bp)
{
	int i;

	for (i = 0; i < bp->fp_array_size; i++)
		kfree(bp->fp[i].tpa_info);
	kfree(bp->fp);
	kfree(bp->sp_objs);
	kfree(bp->fp_stats);
	kfree(bp->bnx2x_txq);
	kfree(bp->msix_table);
	kfree(bp->ilt);
}