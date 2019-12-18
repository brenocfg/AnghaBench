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
typedef  int u32 ;
struct TYPE_3__ {scalar_t__ pd; } ;
struct rvt_qp {TYPE_1__ ibqp; } ;
struct TYPE_4__ {scalar_t__ pd; int lkey; int access_flags; int /*<<< orphan*/  lkey_invalid; int /*<<< orphan*/  iova; } ;
struct rvt_mr {TYPE_2__ mr; scalar_t__ umem; } ;
struct ib_mr {int lkey; int rkey; int /*<<< orphan*/  iova; } ;

/* Variables and functions */
 int EACCES ; 
 int EINVAL ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct rvt_mr* to_imr (struct ib_mr*) ; 

int rvt_fast_reg_mr(struct rvt_qp *qp, struct ib_mr *ibmr, u32 key,
		    int access)
{
	struct rvt_mr *mr = to_imr(ibmr);

	if (qp->ibqp.pd != mr->mr.pd)
		return -EACCES;

	/* not applicable to dma MR or user MR */
	if (!mr->mr.lkey || mr->umem)
		return -EINVAL;

	if ((key & 0xFFFFFF00) != (mr->mr.lkey & 0xFFFFFF00))
		return -EINVAL;

	ibmr->lkey = key;
	ibmr->rkey = key;
	mr->mr.lkey = key;
	mr->mr.access_flags = access;
	mr->mr.iova = ibmr->iova;
	atomic_set(&mr->mr.lkey_invalid, 0);

	return 0;
}