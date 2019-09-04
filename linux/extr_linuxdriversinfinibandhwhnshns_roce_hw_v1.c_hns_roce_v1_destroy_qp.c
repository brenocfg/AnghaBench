#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ib_qp {TYPE_2__* pd; int /*<<< orphan*/  device; } ;
struct TYPE_12__ {int /*<<< orphan*/  qp_wq; } ;
struct hns_roce_v1_priv {TYPE_6__ des_qp; } ;
struct hns_roce_qp_work {int /*<<< orphan*/  work; int /*<<< orphan*/  sche_cnt; int /*<<< orphan*/  sdb_inv_cnt; int /*<<< orphan*/  sdb_issue_ptr; int /*<<< orphan*/  db_wait_stage; struct hns_roce_qp* qp; int /*<<< orphan*/ * ib_dev; } ;
struct TYPE_11__ {scalar_t__ qp_type; scalar_t__ srq; int /*<<< orphan*/  recv_cq; int /*<<< orphan*/  send_cq; } ;
struct TYPE_10__ {struct hns_roce_qp* wrid; } ;
struct TYPE_9__ {struct hns_roce_qp* wrid; } ;
struct hns_roce_qp {int /*<<< orphan*/  qpn; TYPE_5__ ibqp; int /*<<< orphan*/  hr_buf; int /*<<< orphan*/  buff_size; TYPE_4__ rq; TYPE_3__ sq; int /*<<< orphan*/  umem; int /*<<< orphan*/  mtt; } ;
struct hns_roce_dev {scalar_t__ priv; int /*<<< orphan*/  ib_dev; TYPE_1__* pdev; } ;
struct hns_roce_cq {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  uobject; } ;
struct TYPE_7__ {struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IB_QPT_RC ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __hns_roce_v1_cq_clean (struct hns_roce_cq*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int check_qp_reset_state (struct hns_roce_dev*,struct hns_roce_qp*,struct hns_roce_qp_work*,int*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  hns_roce_buf_free (struct hns_roce_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hns_roce_lock_cqs (struct hns_roce_cq*,struct hns_roce_cq*) ; 
 int /*<<< orphan*/  hns_roce_mtt_cleanup (struct hns_roce_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hns_roce_qp_free (struct hns_roce_dev*,struct hns_roce_qp*) ; 
 int /*<<< orphan*/  hns_roce_qp_remove (struct hns_roce_dev*,struct hns_roce_qp*) ; 
 int /*<<< orphan*/  hns_roce_release_range_qp (struct hns_roce_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hns_roce_unlock_cqs (struct hns_roce_cq*,struct hns_roce_cq*) ; 
 int /*<<< orphan*/  hns_roce_v1_destroy_qp_work_fn ; 
 struct hns_roce_qp* hr_to_hr_sqp (struct hns_roce_qp*) ; 
 int /*<<< orphan*/  ib_umem_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct hns_roce_qp*) ; 
 struct hns_roce_qp_work* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct hns_roce_cq* to_hr_cq (int /*<<< orphan*/ ) ; 
 struct hns_roce_dev* to_hr_dev (int /*<<< orphan*/ ) ; 
 struct hns_roce_qp* to_hr_qp (struct ib_qp*) ; 
 int /*<<< orphan*/ * to_hr_srq (scalar_t__) ; 

int hns_roce_v1_destroy_qp(struct ib_qp *ibqp)
{
	struct hns_roce_dev *hr_dev = to_hr_dev(ibqp->device);
	struct hns_roce_qp *hr_qp = to_hr_qp(ibqp);
	struct device *dev = &hr_dev->pdev->dev;
	struct hns_roce_qp_work qp_work_entry;
	struct hns_roce_qp_work *qp_work;
	struct hns_roce_v1_priv *priv;
	struct hns_roce_cq *send_cq, *recv_cq;
	int is_user = !!ibqp->pd->uobject;
	int is_timeout = 0;
	int ret;

	ret = check_qp_reset_state(hr_dev, hr_qp, &qp_work_entry, &is_timeout);
	if (ret) {
		dev_err(dev, "QP reset state check failed(%d)!\n", ret);
		return ret;
	}

	send_cq = to_hr_cq(hr_qp->ibqp.send_cq);
	recv_cq = to_hr_cq(hr_qp->ibqp.recv_cq);

	hns_roce_lock_cqs(send_cq, recv_cq);
	if (!is_user) {
		__hns_roce_v1_cq_clean(recv_cq, hr_qp->qpn, hr_qp->ibqp.srq ?
				       to_hr_srq(hr_qp->ibqp.srq) : NULL);
		if (send_cq != recv_cq)
			__hns_roce_v1_cq_clean(send_cq, hr_qp->qpn, NULL);
	}
	hns_roce_unlock_cqs(send_cq, recv_cq);

	if (!is_timeout) {
		hns_roce_qp_remove(hr_dev, hr_qp);
		hns_roce_qp_free(hr_dev, hr_qp);

		/* RC QP, release QPN */
		if (hr_qp->ibqp.qp_type == IB_QPT_RC)
			hns_roce_release_range_qp(hr_dev, hr_qp->qpn, 1);
	}

	hns_roce_mtt_cleanup(hr_dev, &hr_qp->mtt);

	if (is_user)
		ib_umem_release(hr_qp->umem);
	else {
		kfree(hr_qp->sq.wrid);
		kfree(hr_qp->rq.wrid);

		hns_roce_buf_free(hr_dev, hr_qp->buff_size, &hr_qp->hr_buf);
	}

	if (!is_timeout) {
		if (hr_qp->ibqp.qp_type == IB_QPT_RC)
			kfree(hr_qp);
		else
			kfree(hr_to_hr_sqp(hr_qp));
	} else {
		qp_work = kzalloc(sizeof(*qp_work), GFP_KERNEL);
		if (!qp_work)
			return -ENOMEM;

		INIT_WORK(&qp_work->work, hns_roce_v1_destroy_qp_work_fn);
		qp_work->ib_dev	= &hr_dev->ib_dev;
		qp_work->qp		= hr_qp;
		qp_work->db_wait_stage	= qp_work_entry.db_wait_stage;
		qp_work->sdb_issue_ptr	= qp_work_entry.sdb_issue_ptr;
		qp_work->sdb_inv_cnt	= qp_work_entry.sdb_inv_cnt;
		qp_work->sche_cnt	= qp_work_entry.sche_cnt;

		priv = (struct hns_roce_v1_priv *)hr_dev->priv;
		queue_work(priv->des_qp.qp_wq, &qp_work->work);
		dev_dbg(dev, "Begin destroy QP(0x%lx) work.\n", hr_qp->qpn);
	}

	return 0;
}