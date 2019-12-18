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
typedef  int /*<<< orphan*/  u32 ;
struct ib_recv_wr {int num_sge; int /*<<< orphan*/  wr_id; scalar_t__ sg_list; struct ib_recv_wr* next; } ;
struct ib_qp {scalar_t__ qp_type; int /*<<< orphan*/  device; } ;
struct hns_roce_wqe_data_seg {int dummy; } ;
struct hns_roce_rq_wqe_ctrl {scalar_t__ rwqe_byte_12; } ;
struct hns_roce_rq_db {scalar_t__ u32_8; scalar_t__ u32_4; } ;
struct TYPE_6__ {int head; int wqe_cnt; int max_gs; int /*<<< orphan*/  lock; int /*<<< orphan*/  db_reg_l; int /*<<< orphan*/ * wrid; } ;
struct TYPE_5__ {int /*<<< orphan*/  recv_cq; } ;
struct hns_roce_qp {int phy_port; int qpn; TYPE_3__ rq; TYPE_2__ ibqp; } ;
struct hns_roce_dev {TYPE_1__* pdev; } ;
struct device {int dummy; } ;
typedef  scalar_t__ __le32 ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ IB_QPT_GSI ; 
 int QP1C_CFGN_OFFSET ; 
 scalar_t__ ROCEE_QP1C_CFG3_0_REG ; 
 int /*<<< orphan*/  ROCEE_QP1C_CFG3_0_ROCEE_QP1C_RQ_HEAD_M ; 
 int /*<<< orphan*/  ROCEE_QP1C_CFG3_0_ROCEE_QP1C_RQ_HEAD_S ; 
 int /*<<< orphan*/  RQ_DOORBELL_U32_4_RQ_HEAD_M ; 
 int /*<<< orphan*/  RQ_DOORBELL_U32_4_RQ_HEAD_S ; 
 int /*<<< orphan*/  RQ_DOORBELL_U32_8_CMD_M ; 
 int /*<<< orphan*/  RQ_DOORBELL_U32_8_CMD_S ; 
 int /*<<< orphan*/  RQ_DOORBELL_U32_8_HW_SYNC_S ; 
 int /*<<< orphan*/  RQ_DOORBELL_U32_8_QPN_M ; 
 int /*<<< orphan*/  RQ_DOORBELL_U32_8_QPN_S ; 
 int /*<<< orphan*/  RQ_WQE_CTRL_RWQE_BYTE_12_RWQE_SGE_NUM_M ; 
 int /*<<< orphan*/  RQ_WQE_CTRL_RWQE_BYTE_12_RWQE_SGE_NUM_S ; 
 scalar_t__ cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,int) ; 
 struct hns_roce_rq_wqe_ctrl* get_recv_wqe (struct hns_roce_qp*,int) ; 
 scalar_t__ hns_roce_wq_overflow (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_roce_write64_k (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (scalar_t__) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  roce_read (struct hns_roce_dev*,scalar_t__) ; 
 int /*<<< orphan*/  roce_set_bit (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  roce_set_field (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  roce_write (struct hns_roce_dev*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_data_seg (struct hns_roce_wqe_data_seg*,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct hns_roce_dev* to_hr_dev (int /*<<< orphan*/ ) ; 
 struct hns_roce_qp* to_hr_qp (struct ib_qp*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int hns_roce_v1_post_recv(struct ib_qp *ibqp,
				 const struct ib_recv_wr *wr,
				 const struct ib_recv_wr **bad_wr)
{
	int ret = 0;
	int nreq = 0;
	int ind = 0;
	int i = 0;
	u32 reg_val;
	unsigned long flags = 0;
	struct hns_roce_rq_wqe_ctrl *ctrl = NULL;
	struct hns_roce_wqe_data_seg *scat = NULL;
	struct hns_roce_qp *hr_qp = to_hr_qp(ibqp);
	struct hns_roce_dev *hr_dev = to_hr_dev(ibqp->device);
	struct device *dev = &hr_dev->pdev->dev;
	struct hns_roce_rq_db rq_db;
	__le32 doorbell[2] = {0};

	spin_lock_irqsave(&hr_qp->rq.lock, flags);
	ind = hr_qp->rq.head & (hr_qp->rq.wqe_cnt - 1);

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

		ctrl = get_recv_wqe(hr_qp, ind);

		roce_set_field(ctrl->rwqe_byte_12,
			       RQ_WQE_CTRL_RWQE_BYTE_12_RWQE_SGE_NUM_M,
			       RQ_WQE_CTRL_RWQE_BYTE_12_RWQE_SGE_NUM_S,
			       wr->num_sge);

		scat = (struct hns_roce_wqe_data_seg *)(ctrl + 1);

		for (i = 0; i < wr->num_sge; i++)
			set_data_seg(scat + i, wr->sg_list + i);

		hr_qp->rq.wrid[ind] = wr->wr_id;

		ind = (ind + 1) & (hr_qp->rq.wqe_cnt - 1);
	}

out:
	if (likely(nreq)) {
		hr_qp->rq.head += nreq;
		/* Memory barrier */
		wmb();

		if (ibqp->qp_type == IB_QPT_GSI) {
			__le32 tmp;

			/* SW update GSI rq header */
			reg_val = roce_read(to_hr_dev(ibqp->device),
					    ROCEE_QP1C_CFG3_0_REG +
					    QP1C_CFGN_OFFSET * hr_qp->phy_port);
			tmp = cpu_to_le32(reg_val);
			roce_set_field(tmp,
				       ROCEE_QP1C_CFG3_0_ROCEE_QP1C_RQ_HEAD_M,
				       ROCEE_QP1C_CFG3_0_ROCEE_QP1C_RQ_HEAD_S,
				       hr_qp->rq.head);
			reg_val = le32_to_cpu(tmp);
			roce_write(to_hr_dev(ibqp->device),
				   ROCEE_QP1C_CFG3_0_REG +
				   QP1C_CFGN_OFFSET * hr_qp->phy_port, reg_val);
		} else {
			rq_db.u32_4 = 0;
			rq_db.u32_8 = 0;

			roce_set_field(rq_db.u32_4, RQ_DOORBELL_U32_4_RQ_HEAD_M,
				       RQ_DOORBELL_U32_4_RQ_HEAD_S,
				       hr_qp->rq.head);
			roce_set_field(rq_db.u32_8, RQ_DOORBELL_U32_8_QPN_M,
				       RQ_DOORBELL_U32_8_QPN_S, hr_qp->qpn);
			roce_set_field(rq_db.u32_8, RQ_DOORBELL_U32_8_CMD_M,
				       RQ_DOORBELL_U32_8_CMD_S, 1);
			roce_set_bit(rq_db.u32_8, RQ_DOORBELL_U32_8_HW_SYNC_S,
				     1);

			doorbell[0] = rq_db.u32_4;
			doorbell[1] = rq_db.u32_8;

			hns_roce_write64_k(doorbell, hr_qp->rq.db_reg_l);
		}
	}
	spin_unlock_irqrestore(&hr_qp->rq.lock, flags);

	return ret;
}