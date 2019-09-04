#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_6__* wqe_list; } ;
struct TYPE_10__ {scalar_t__ wqe_cnt; TYPE_6__* wrid; } ;
struct TYPE_9__ {TYPE_6__* wrid; scalar_t__ wqe_cnt; } ;
struct TYPE_14__ {scalar_t__ qp_type; TYPE_1__* uobject; scalar_t__ srq; int /*<<< orphan*/  recv_cq; int /*<<< orphan*/  send_cq; } ;
struct hns_roce_qp {scalar_t__ state; int sdb_en; int rdb_en; TYPE_5__ rq_inl_buf; int /*<<< orphan*/  rdb; TYPE_3__ rq; int /*<<< orphan*/  hr_buf; int /*<<< orphan*/  buff_size; TYPE_2__ sq; int /*<<< orphan*/  umem; TYPE_7__ ibqp; int /*<<< orphan*/  sdb; int /*<<< orphan*/  mtt; int /*<<< orphan*/  qpn; } ;
struct TYPE_11__ {int flags; } ;
struct hns_roce_dev {TYPE_4__ caps; struct device* dev; } ;
struct hns_roce_cq {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_13__ {struct TYPE_13__* sg_list; } ;
struct TYPE_8__ {int /*<<< orphan*/  context; } ;

/* Variables and functions */
 int HNS_ROCE_CAP_FLAG_RQ_INLINE ; 
 scalar_t__ IB_QPS_RESET ; 
 scalar_t__ IB_QPT_RC ; 
 scalar_t__ IB_QPT_UC ; 
 scalar_t__ IB_QPT_UD ; 
 int /*<<< orphan*/  __hns_roce_v2_cq_clean (struct hns_roce_cq*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_roce_buf_free (struct hns_roce_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hns_roce_db_unmap_user (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hns_roce_free_db (struct hns_roce_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hns_roce_lock_cqs (struct hns_roce_cq*,struct hns_roce_cq*) ; 
 int /*<<< orphan*/  hns_roce_mtt_cleanup (struct hns_roce_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hns_roce_qp_free (struct hns_roce_dev*,struct hns_roce_qp*) ; 
 int /*<<< orphan*/  hns_roce_qp_remove (struct hns_roce_dev*,struct hns_roce_qp*) ; 
 int /*<<< orphan*/  hns_roce_release_range_qp (struct hns_roce_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hns_roce_unlock_cqs (struct hns_roce_cq*,struct hns_roce_cq*) ; 
 int hns_roce_v2_modify_qp (TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ib_umem_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_6__*) ; 
 struct hns_roce_cq* to_hr_cq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * to_hr_srq (scalar_t__) ; 
 int /*<<< orphan*/  to_hr_ucontext (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hns_roce_v2_destroy_qp_common(struct hns_roce_dev *hr_dev,
					 struct hns_roce_qp *hr_qp,
					 int is_user)
{
	struct hns_roce_cq *send_cq, *recv_cq;
	struct device *dev = hr_dev->dev;
	int ret;

	if (hr_qp->ibqp.qp_type == IB_QPT_RC && hr_qp->state != IB_QPS_RESET) {
		/* Modify qp to reset before destroying qp */
		ret = hns_roce_v2_modify_qp(&hr_qp->ibqp, NULL, 0,
					    hr_qp->state, IB_QPS_RESET);
		if (ret) {
			dev_err(dev, "modify QP %06lx to ERR failed.\n",
				hr_qp->qpn);
			return ret;
		}
	}

	send_cq = to_hr_cq(hr_qp->ibqp.send_cq);
	recv_cq = to_hr_cq(hr_qp->ibqp.recv_cq);

	hns_roce_lock_cqs(send_cq, recv_cq);

	if (!is_user) {
		__hns_roce_v2_cq_clean(recv_cq, hr_qp->qpn, hr_qp->ibqp.srq ?
				       to_hr_srq(hr_qp->ibqp.srq) : NULL);
		if (send_cq != recv_cq)
			__hns_roce_v2_cq_clean(send_cq, hr_qp->qpn, NULL);
	}

	hns_roce_qp_remove(hr_dev, hr_qp);

	hns_roce_unlock_cqs(send_cq, recv_cq);

	hns_roce_qp_free(hr_dev, hr_qp);

	/* Not special_QP, free their QPN */
	if ((hr_qp->ibqp.qp_type == IB_QPT_RC) ||
	    (hr_qp->ibqp.qp_type == IB_QPT_UC) ||
	    (hr_qp->ibqp.qp_type == IB_QPT_UD))
		hns_roce_release_range_qp(hr_dev, hr_qp->qpn, 1);

	hns_roce_mtt_cleanup(hr_dev, &hr_qp->mtt);

	if (is_user) {
		if (hr_qp->sq.wqe_cnt && (hr_qp->sdb_en == 1))
			hns_roce_db_unmap_user(
				to_hr_ucontext(hr_qp->ibqp.uobject->context),
				&hr_qp->sdb);

		if (hr_qp->rq.wqe_cnt && (hr_qp->rdb_en == 1))
			hns_roce_db_unmap_user(
				to_hr_ucontext(hr_qp->ibqp.uobject->context),
				&hr_qp->rdb);
		ib_umem_release(hr_qp->umem);
	} else {
		kfree(hr_qp->sq.wrid);
		kfree(hr_qp->rq.wrid);
		hns_roce_buf_free(hr_dev, hr_qp->buff_size, &hr_qp->hr_buf);
		if (hr_qp->rq.wqe_cnt)
			hns_roce_free_db(hr_dev, &hr_qp->rdb);
	}

	if (hr_dev->caps.flags & HNS_ROCE_CAP_FLAG_RQ_INLINE) {
		kfree(hr_qp->rq_inl_buf.wqe_list[0].sg_list);
		kfree(hr_qp->rq_inl_buf.wqe_list);
	}

	return 0;
}