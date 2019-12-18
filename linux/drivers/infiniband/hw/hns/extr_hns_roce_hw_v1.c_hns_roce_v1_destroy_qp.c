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
struct ib_udata {int dummy; } ;
struct ib_qp {int /*<<< orphan*/  device; } ;
struct TYPE_6__ {scalar_t__ qp_type; scalar_t__ srq; int /*<<< orphan*/  recv_cq; int /*<<< orphan*/  send_cq; } ;
struct TYPE_5__ {struct hns_roce_qp* wrid; } ;
struct TYPE_4__ {struct hns_roce_qp* wrid; } ;
struct hns_roce_qp {TYPE_3__ ibqp; int /*<<< orphan*/  hr_buf; int /*<<< orphan*/  buff_size; TYPE_2__ rq; TYPE_1__ sq; int /*<<< orphan*/  umem; int /*<<< orphan*/  mtt; int /*<<< orphan*/  qpn; int /*<<< orphan*/  state; } ;
struct hns_roce_dev {int dummy; } ;
struct hns_roce_cq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_QPS_RESET ; 
 scalar_t__ IB_QPT_RC ; 
 int /*<<< orphan*/  __hns_roce_v1_cq_clean (struct hns_roce_cq*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hns_roce_buf_free (struct hns_roce_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hns_roce_lock_cqs (struct hns_roce_cq*,struct hns_roce_cq*) ; 
 int /*<<< orphan*/  hns_roce_mtt_cleanup (struct hns_roce_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hns_roce_qp_free (struct hns_roce_dev*,struct hns_roce_qp*) ; 
 int /*<<< orphan*/  hns_roce_qp_remove (struct hns_roce_dev*,struct hns_roce_qp*) ; 
 int /*<<< orphan*/  hns_roce_release_range_qp (struct hns_roce_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hns_roce_unlock_cqs (struct hns_roce_cq*,struct hns_roce_cq*) ; 
 int hns_roce_v1_modify_qp (struct ib_qp*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hns_roce_qp* hr_to_hr_sqp (struct hns_roce_qp*) ; 
 int /*<<< orphan*/  ib_umem_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct hns_roce_qp*) ; 
 struct hns_roce_cq* to_hr_cq (int /*<<< orphan*/ ) ; 
 struct hns_roce_dev* to_hr_dev (int /*<<< orphan*/ ) ; 
 struct hns_roce_qp* to_hr_qp (struct ib_qp*) ; 
 int /*<<< orphan*/ * to_hr_srq (scalar_t__) ; 

int hns_roce_v1_destroy_qp(struct ib_qp *ibqp, struct ib_udata *udata)
{
	struct hns_roce_dev *hr_dev = to_hr_dev(ibqp->device);
	struct hns_roce_qp *hr_qp = to_hr_qp(ibqp);
	struct hns_roce_cq *send_cq, *recv_cq;
	int ret;

	ret = hns_roce_v1_modify_qp(ibqp, NULL, 0, hr_qp->state, IB_QPS_RESET);
	if (ret)
		return ret;

	send_cq = to_hr_cq(hr_qp->ibqp.send_cq);
	recv_cq = to_hr_cq(hr_qp->ibqp.recv_cq);

	hns_roce_lock_cqs(send_cq, recv_cq);
	if (!udata) {
		__hns_roce_v1_cq_clean(recv_cq, hr_qp->qpn, hr_qp->ibqp.srq ?
				       to_hr_srq(hr_qp->ibqp.srq) : NULL);
		if (send_cq != recv_cq)
			__hns_roce_v1_cq_clean(send_cq, hr_qp->qpn, NULL);
	}
	hns_roce_unlock_cqs(send_cq, recv_cq);

	hns_roce_qp_remove(hr_dev, hr_qp);
	hns_roce_qp_free(hr_dev, hr_qp);

	/* RC QP, release QPN */
	if (hr_qp->ibqp.qp_type == IB_QPT_RC)
		hns_roce_release_range_qp(hr_dev, hr_qp->qpn, 1);

	hns_roce_mtt_cleanup(hr_dev, &hr_qp->mtt);

	ib_umem_release(hr_qp->umem);
	if (!udata) {
		kfree(hr_qp->sq.wrid);
		kfree(hr_qp->rq.wrid);

		hns_roce_buf_free(hr_dev, hr_qp->buff_size, &hr_qp->hr_buf);
	}

	if (hr_qp->ibqp.qp_type == IB_QPT_RC)
		kfree(hr_qp);
	else
		kfree(hr_to_hr_sqp(hr_qp));
	return 0;
}