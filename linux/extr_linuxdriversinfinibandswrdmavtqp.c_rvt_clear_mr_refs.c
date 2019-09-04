#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  ah; } ;
struct rvt_swqe {TYPE_2__ ud_wr; } ;
struct TYPE_5__ {scalar_t__ qp_type; int /*<<< orphan*/  device; } ;
struct rvt_qp {scalar_t__ s_last; scalar_t__ s_head; scalar_t__ s_size; struct rvt_ack_entry* s_ack_queue; int /*<<< orphan*/ * s_rdma_mr; TYPE_1__ ibqp; int /*<<< orphan*/  r_sge; int /*<<< orphan*/  s_rdma_read_sge; int /*<<< orphan*/  r_aflags; } ;
struct rvt_dev_info {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/ * mr; } ;
struct rvt_ack_entry {TYPE_3__ rdma_sge; } ;
struct TYPE_8__ {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 scalar_t__ IB_QPT_GSI ; 
 scalar_t__ IB_QPT_SMI ; 
 scalar_t__ IB_QPT_UD ; 
 int /*<<< orphan*/  RVT_R_REWIND_SGE ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 struct rvt_dev_info* ib_to_rvt (int /*<<< orphan*/ ) ; 
 TYPE_4__* ibah_to_rvtah (int /*<<< orphan*/ ) ; 
 struct rvt_swqe* rvt_get_swqe_ptr (struct rvt_qp*,scalar_t__) ; 
 unsigned int rvt_max_atomic (struct rvt_dev_info*) ; 
 int /*<<< orphan*/  rvt_put_mr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rvt_put_ss (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rvt_put_swqe (struct rvt_swqe*) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rvt_clear_mr_refs(struct rvt_qp *qp, int clr_sends)
{
	unsigned n;
	struct rvt_dev_info *rdi = ib_to_rvt(qp->ibqp.device);

	if (test_and_clear_bit(RVT_R_REWIND_SGE, &qp->r_aflags))
		rvt_put_ss(&qp->s_rdma_read_sge);

	rvt_put_ss(&qp->r_sge);

	if (clr_sends) {
		while (qp->s_last != qp->s_head) {
			struct rvt_swqe *wqe = rvt_get_swqe_ptr(qp, qp->s_last);

			rvt_put_swqe(wqe);

			if (qp->ibqp.qp_type == IB_QPT_UD ||
			    qp->ibqp.qp_type == IB_QPT_SMI ||
			    qp->ibqp.qp_type == IB_QPT_GSI)
				atomic_dec(&ibah_to_rvtah(
						wqe->ud_wr.ah)->refcount);
			if (++qp->s_last >= qp->s_size)
				qp->s_last = 0;
			smp_wmb(); /* see qp_set_savail */
		}
		if (qp->s_rdma_mr) {
			rvt_put_mr(qp->s_rdma_mr);
			qp->s_rdma_mr = NULL;
		}
	}

	for (n = 0; qp->s_ack_queue && n < rvt_max_atomic(rdi); n++) {
		struct rvt_ack_entry *e = &qp->s_ack_queue[n];

		if (e->rdma_sge.mr) {
			rvt_put_mr(e->rdma_sge.mr);
			e->rdma_sge.mr = NULL;
		}
	}
}