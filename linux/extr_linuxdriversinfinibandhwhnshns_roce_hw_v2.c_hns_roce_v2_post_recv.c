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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct ib_recv_wr {int num_sge; int /*<<< orphan*/  wr_id; TYPE_5__* sg_list; struct ib_recv_wr* next; } ;
struct ib_qp_attr {scalar_t__ qp_state; } ;
struct ib_qp {int /*<<< orphan*/  device; } ;
struct hns_roce_v2_wqe_data_seg {scalar_t__ addr; int /*<<< orphan*/  lkey; } ;
struct hns_roce_rinl_sge {scalar_t__ len; void* addr; } ;
struct TYPE_13__ {int head; int wqe_cnt; int max_gs; int /*<<< orphan*/  lock; int /*<<< orphan*/ * wrid; } ;
struct TYPE_14__ {int /*<<< orphan*/  recv_cq; } ;
struct TYPE_11__ {int* db_record; } ;
struct TYPE_10__ {TYPE_2__* wqe_list; } ;
struct hns_roce_qp {scalar_t__ state; TYPE_6__ rq; TYPE_7__ ibqp; TYPE_4__ rdb; TYPE_3__ rq_inl_buf; } ;
struct TYPE_8__ {int flags; } ;
struct hns_roce_dev {TYPE_1__ caps; struct device* dev; } ;
struct device {int dummy; } ;
struct TYPE_12__ {scalar_t__ length; scalar_t__ addr; } ;
struct TYPE_9__ {scalar_t__ sge_cnt; struct hns_roce_rinl_sge* sg_list; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int HNS_ROCE_CAP_FLAG_RQ_INLINE ; 
 int /*<<< orphan*/  HNS_ROCE_INVALID_LKEY ; 
 scalar_t__ IB_QPS_ERR ; 
 scalar_t__ IB_QPS_RESET ; 
 int IB_QP_STATE ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,int) ; 
 void* get_recv_wqe (struct hns_roce_qp*,int) ; 
 int hns_roce_v2_modify_qp (TYPE_7__*,struct ib_qp_attr*,int,scalar_t__,scalar_t__) ; 
 scalar_t__ hns_roce_wq_overflow (TYPE_6__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  set_data_seg_v2 (struct hns_roce_v2_wqe_data_seg*,TYPE_5__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct hns_roce_dev* to_hr_dev (int /*<<< orphan*/ ) ; 
 struct hns_roce_qp* to_hr_qp (struct ib_qp*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int hns_roce_v2_post_recv(struct ib_qp *ibqp,
				 const struct ib_recv_wr *wr,
				 const struct ib_recv_wr **bad_wr)
{
	struct hns_roce_dev *hr_dev = to_hr_dev(ibqp->device);
	struct hns_roce_qp *hr_qp = to_hr_qp(ibqp);
	struct hns_roce_v2_wqe_data_seg *dseg;
	struct hns_roce_rinl_sge *sge_list;
	struct device *dev = hr_dev->dev;
	struct ib_qp_attr attr;
	unsigned long flags;
	void *wqe = NULL;
	int attr_mask;
	int ret = 0;
	int nreq;
	int ind;
	int i;

	spin_lock_irqsave(&hr_qp->rq.lock, flags);
	ind = hr_qp->rq.head & (hr_qp->rq.wqe_cnt - 1);

	if (hr_qp->state == IB_QPS_RESET) {
		spin_unlock_irqrestore(&hr_qp->rq.lock, flags);
		*bad_wr = wr;
		return -EINVAL;
	}

	for (nreq = 0; wr; ++nreq, wr = wr->next) {
		if (hns_roce_wq_overflow(&hr_qp->rq, nreq,
			hr_qp->ibqp.recv_cq)) {
			ret = -ENOMEM;
			*bad_wr = wr;
			goto out;
		}

		if (unlikely(wr->num_sge > hr_qp->rq.max_gs)) {
			dev_err(dev, "rq:num_sge=%d > qp->sq.max_gs=%d\n",
				wr->num_sge, hr_qp->rq.max_gs);
			ret = -EINVAL;
			*bad_wr = wr;
			goto out;
		}

		wqe = get_recv_wqe(hr_qp, ind);
		dseg = (struct hns_roce_v2_wqe_data_seg *)wqe;
		for (i = 0; i < wr->num_sge; i++) {
			if (!wr->sg_list[i].length)
				continue;
			set_data_seg_v2(dseg, wr->sg_list + i);
			dseg++;
		}

		if (i < hr_qp->rq.max_gs) {
			dseg->lkey = cpu_to_le32(HNS_ROCE_INVALID_LKEY);
			dseg->addr = 0;
		}

		/* rq support inline data */
		if (hr_dev->caps.flags & HNS_ROCE_CAP_FLAG_RQ_INLINE) {
			sge_list = hr_qp->rq_inl_buf.wqe_list[ind].sg_list;
			hr_qp->rq_inl_buf.wqe_list[ind].sge_cnt =
							       (u32)wr->num_sge;
			for (i = 0; i < wr->num_sge; i++) {
				sge_list[i].addr =
					       (void *)(u64)wr->sg_list[i].addr;
				sge_list[i].len = wr->sg_list[i].length;
			}
		}

		hr_qp->rq.wrid[ind] = wr->wr_id;

		ind = (ind + 1) & (hr_qp->rq.wqe_cnt - 1);
	}

out:
	if (likely(nreq)) {
		hr_qp->rq.head += nreq;
		/* Memory barrier */
		wmb();

		*hr_qp->rdb.db_record = hr_qp->rq.head & 0xffff;

		if (hr_qp->state == IB_QPS_ERR) {
			attr_mask = IB_QP_STATE;
			attr.qp_state = IB_QPS_ERR;

			ret = hns_roce_v2_modify_qp(&hr_qp->ibqp, &attr,
						    attr_mask, hr_qp->state,
						    IB_QPS_ERR);
			if (ret) {
				spin_unlock_irqrestore(&hr_qp->rq.lock, flags);
				*bad_wr = wr;
				return ret;
			}
		}
	}
	spin_unlock_irqrestore(&hr_qp->rq.lock, flags);

	return ret;
}