#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct host_sp_status_block {int dummy; } ;
struct bnx2x_slowpath {int dummy; } ;
struct bnx2x {int fw_stats_data_sz; int fw_stats_req_sz; int /*<<< orphan*/  t2_mapping; int /*<<< orphan*/  t2; int /*<<< orphan*/  eq_mapping; int /*<<< orphan*/  eq_ring; int /*<<< orphan*/  spq_mapping; int /*<<< orphan*/  spq; TYPE_2__* ilt; TYPE_1__* context; int /*<<< orphan*/  slowpath_mapping; int /*<<< orphan*/  slowpath; int /*<<< orphan*/  def_status_blk_mapping; int /*<<< orphan*/  def_status_blk; int /*<<< orphan*/  fw_stats_mapping; int /*<<< orphan*/  fw_stats; } ;
struct TYPE_4__ {int /*<<< orphan*/  lines; } ;
struct TYPE_3__ {int size; int /*<<< orphan*/  cxt_mapping; int /*<<< orphan*/  vcxt; } ;

/* Variables and functions */
 int BCM_PAGE_SIZE ; 
 int /*<<< orphan*/  BNX2X_FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BNX2X_PCI_FREE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ILT_MEMOP_FREE ; 
 scalar_t__ IS_VF (struct bnx2x*) ; 
 int L2_ILT_LINES (struct bnx2x*) ; 
 int NUM_EQ_PAGES ; 
 int SRC_T2_SZ ; 
 int /*<<< orphan*/  bnx2x_ilt_mem_op (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_iov_free_mem (struct bnx2x*) ; 

void bnx2x_free_mem(struct bnx2x *bp)
{
	int i;

	BNX2X_PCI_FREE(bp->fw_stats, bp->fw_stats_mapping,
		       bp->fw_stats_data_sz + bp->fw_stats_req_sz);

	if (IS_VF(bp))
		return;

	BNX2X_PCI_FREE(bp->def_status_blk, bp->def_status_blk_mapping,
		       sizeof(struct host_sp_status_block));

	BNX2X_PCI_FREE(bp->slowpath, bp->slowpath_mapping,
		       sizeof(struct bnx2x_slowpath));

	for (i = 0; i < L2_ILT_LINES(bp); i++)
		BNX2X_PCI_FREE(bp->context[i].vcxt, bp->context[i].cxt_mapping,
			       bp->context[i].size);
	bnx2x_ilt_mem_op(bp, ILT_MEMOP_FREE);

	BNX2X_FREE(bp->ilt->lines);

	BNX2X_PCI_FREE(bp->spq, bp->spq_mapping, BCM_PAGE_SIZE);

	BNX2X_PCI_FREE(bp->eq_ring, bp->eq_mapping,
		       BCM_PAGE_SIZE * NUM_EQ_PAGES);

	BNX2X_PCI_FREE(bp->t2, bp->t2_mapping, SRC_T2_SZ);

	bnx2x_iov_free_mem(bp);
}