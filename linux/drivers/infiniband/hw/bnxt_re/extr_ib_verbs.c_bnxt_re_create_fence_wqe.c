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
typedef  scalar_t__ u64 ;
struct ib_mr {int /*<<< orphan*/  lkey; } ;
struct TYPE_5__ {int zero_based; int /*<<< orphan*/  mw_type; int /*<<< orphan*/  access_cntl; int /*<<< orphan*/  length; scalar_t__ va; int /*<<< orphan*/  parent_l_key; } ;
struct bnxt_qplib_swqe {TYPE_2__ bind; int /*<<< orphan*/  flags; int /*<<< orphan*/  wr_id; int /*<<< orphan*/  type; } ;
struct bnxt_re_fence_data {TYPE_3__* mw; int /*<<< orphan*/  bind_rkey; int /*<<< orphan*/  size; scalar_t__ va; struct bnxt_qplib_swqe bind_wqe; TYPE_1__* mr; } ;
struct bnxt_re_pd {struct bnxt_re_fence_data fence; } ;
struct TYPE_6__ {int /*<<< orphan*/  rkey; } ;
struct TYPE_4__ {struct ib_mr ib_mr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNXT_QPLIB_FENCE_WRID ; 
 int /*<<< orphan*/  BNXT_QPLIB_SWQE_FLAGS_SIGNAL_COMP ; 
 int /*<<< orphan*/  BNXT_QPLIB_SWQE_FLAGS_UC_FENCE ; 
 int /*<<< orphan*/  BNXT_QPLIB_SWQE_TYPE_BIND_MW ; 
 int /*<<< orphan*/  IB_ACCESS_REMOTE_READ ; 
 int /*<<< orphan*/  SQ_BIND_MW_TYPE_TYPE1 ; 
 int /*<<< orphan*/  __from_ib_access_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_inc_rkey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct bnxt_qplib_swqe*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void bnxt_re_create_fence_wqe(struct bnxt_re_pd *pd)
{
	struct bnxt_re_fence_data *fence = &pd->fence;
	struct ib_mr *ib_mr = &fence->mr->ib_mr;
	struct bnxt_qplib_swqe *wqe = &fence->bind_wqe;

	memset(wqe, 0, sizeof(*wqe));
	wqe->type = BNXT_QPLIB_SWQE_TYPE_BIND_MW;
	wqe->wr_id = BNXT_QPLIB_FENCE_WRID;
	wqe->flags |= BNXT_QPLIB_SWQE_FLAGS_SIGNAL_COMP;
	wqe->flags |= BNXT_QPLIB_SWQE_FLAGS_UC_FENCE;
	wqe->bind.zero_based = false;
	wqe->bind.parent_l_key = ib_mr->lkey;
	wqe->bind.va = (u64)(unsigned long)fence->va;
	wqe->bind.length = fence->size;
	wqe->bind.access_cntl = __from_ib_access_flags(IB_ACCESS_REMOTE_READ);
	wqe->bind.mw_type = SQ_BIND_MW_TYPE_TYPE1;

	/* Save the initial rkey in fence structure for now;
	 * wqe->bind.r_key will be set at (re)bind time.
	 */
	fence->bind_rkey = ib_inc_rkey(fence->mw->rkey);
}