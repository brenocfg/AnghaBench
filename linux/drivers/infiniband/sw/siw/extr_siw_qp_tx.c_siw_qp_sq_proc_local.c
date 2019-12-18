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
struct TYPE_2__ {int /*<<< orphan*/  rkey; } ;
struct siw_wqe {TYPE_1__ sqe; } ;
struct siw_qp {int /*<<< orphan*/  pd; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SIW_OP_INVAL_STAG 129 
#define  SIW_OP_REG_MR 128 
 int siw_fastreg_mr (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int siw_invalidate_stag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tx_type (struct siw_wqe*) ; 

__attribute__((used)) static int siw_qp_sq_proc_local(struct siw_qp *qp, struct siw_wqe *wqe)
{
	int rv;

	switch (tx_type(wqe)) {
	case SIW_OP_REG_MR:
		rv = siw_fastreg_mr(qp->pd, &wqe->sqe);
		break;

	case SIW_OP_INVAL_STAG:
		rv = siw_invalidate_stag(qp->pd, wqe->sqe.rkey);
		break;

	default:
		rv = -EINVAL;
	}
	return rv;
}