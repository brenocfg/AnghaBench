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
typedef  int u16 ;
struct ocrdma_qp {int dummy; } ;
struct ocrdma_dev {struct ocrdma_qp** qp_tbl; } ;
struct TYPE_4__ {scalar_t__ qpn; } ;
struct ocrdma_cqe {TYPE_2__ cmn; } ;
struct TYPE_3__ {int /*<<< orphan*/  device; } ;
struct ocrdma_cq {int getp; int max_hw_cqe; int /*<<< orphan*/  id; struct ocrdma_cqe* va; TYPE_1__ ibcq; } ;
struct ib_wc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int OCRDMA_CQE_QPN_MASK ; 
 struct ocrdma_dev* get_ocrdma_dev (int /*<<< orphan*/ ) ; 
 scalar_t__ is_cqe_for_sq (struct ocrdma_cqe*) ; 
 int /*<<< orphan*/  is_cqe_valid (struct ocrdma_cq*,struct ocrdma_cqe*) ; 
 int le32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  ocrdma_change_cq_phase (struct ocrdma_cq*,struct ocrdma_cqe*,int) ; 
 int ocrdma_poll_rcqe (struct ocrdma_qp*,struct ocrdma_cqe*,struct ib_wc*,int*,int*) ; 
 int ocrdma_poll_scqe (struct ocrdma_qp*,struct ocrdma_cqe*,struct ib_wc*,int*,int*) ; 
 int /*<<< orphan*/  ocrdma_ring_cq_db (struct ocrdma_dev*,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int ocrdma_poll_hwcq(struct ocrdma_cq *cq, int num_entries,
			    struct ib_wc *ibwc)
{
	u16 qpn = 0;
	int i = 0;
	bool expand = false;
	int polled_hw_cqes = 0;
	struct ocrdma_qp *qp = NULL;
	struct ocrdma_dev *dev = get_ocrdma_dev(cq->ibcq.device);
	struct ocrdma_cqe *cqe;
	u16 cur_getp; bool polled = false; bool stop = false;

	cur_getp = cq->getp;
	while (num_entries) {
		cqe = cq->va + cur_getp;
		/* check whether valid cqe or not */
		if (!is_cqe_valid(cq, cqe))
			break;
		qpn = (le32_to_cpu(cqe->cmn.qpn) & OCRDMA_CQE_QPN_MASK);
		/* ignore discarded cqe */
		if (qpn == 0)
			goto skip_cqe;
		qp = dev->qp_tbl[qpn];
		BUG_ON(qp == NULL);

		if (is_cqe_for_sq(cqe)) {
			expand = ocrdma_poll_scqe(qp, cqe, ibwc, &polled,
						  &stop);
		} else {
			expand = ocrdma_poll_rcqe(qp, cqe, ibwc, &polled,
						  &stop);
		}
		if (expand)
			goto expand_cqe;
		if (stop)
			goto stop_cqe;
		/* clear qpn to avoid duplicate processing by discard_cqe() */
		cqe->cmn.qpn = 0;
skip_cqe:
		polled_hw_cqes += 1;
		cur_getp = (cur_getp + 1) % cq->max_hw_cqe;
		ocrdma_change_cq_phase(cq, cqe, cur_getp);
expand_cqe:
		if (polled) {
			num_entries -= 1;
			i += 1;
			ibwc = ibwc + 1;
			polled = false;
		}
	}
stop_cqe:
	cq->getp = cur_getp;

	if (polled_hw_cqes)
		ocrdma_ring_cq_db(dev, cq->id, false, false, polled_hw_cqes);

	return i;
}