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
typedef  scalar_t__ u32 ;
struct TYPE_8__ {scalar_t__ max_inline_data; int /*<<< orphan*/  max_send_sge; int /*<<< orphan*/  max_send_wr; int /*<<< orphan*/  max_recv_sge; int /*<<< orphan*/  max_recv_wr; } ;
struct ib_qp_init_attr {scalar_t__ create_flags; TYPE_4__ cap; } ;
struct TYPE_5__ {int /*<<< orphan*/  type; } ;
struct ib_qp_attr {scalar_t__ qp_state; int dest_qp_num; int qp_access_flags; int port_num; scalar_t__ cur_qp_state; TYPE_4__ cap; scalar_t__ alt_timeout; scalar_t__ rnr_retry; scalar_t__ retry_cnt; scalar_t__ timeout; scalar_t__ min_rnr_timer; scalar_t__ max_dest_rd_atomic; scalar_t__ max_rd_atomic; scalar_t__ sq_draining; void* pkey_index; scalar_t__ sq_psn; scalar_t__ rq_psn; TYPE_1__ ah_attr; int /*<<< orphan*/  qkey; int /*<<< orphan*/  path_mig_state; int /*<<< orphan*/  path_mtu; } ;
struct ib_qp {int /*<<< orphan*/  device; } ;
struct hns_roce_sqp_context {void* qp1c_bytes_20; void* qp1c_bytes_4; void* qp1c_bytes_40; void* cur_sq_wqe_ba_l; void* qp1c_bytes_32; void* qp1c_bytes_28; void* cur_rq_wqe_ba_l; void* qp1c_bytes_16; void* qp1c_bytes_12; void* sq_rq_bt_l; } ;
struct TYPE_7__ {int /*<<< orphan*/  max_gs; int /*<<< orphan*/  wqe_cnt; } ;
struct TYPE_6__ {int /*<<< orphan*/  max_gs; int /*<<< orphan*/  wqe_cnt; } ;
struct hns_roce_qp {scalar_t__ state; int port; int /*<<< orphan*/  mutex; TYPE_3__ sq; TYPE_2__ rq; } ;
struct hns_roce_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_MIG_ARMED ; 
 int /*<<< orphan*/  IB_MTU_256 ; 
 scalar_t__ IB_QPS_RESET ; 
 int /*<<< orphan*/  QKEY_VAL ; 
 int /*<<< orphan*/  QP1C_BYTES_20_PKEY_IDX_M ; 
 int /*<<< orphan*/  QP1C_BYTES_20_PKEY_IDX_S ; 
 int /*<<< orphan*/  QP1C_BYTES_4_QP_STATE_M ; 
 int /*<<< orphan*/  QP1C_BYTES_4_QP_STATE_S ; 
 int /*<<< orphan*/  RDMA_AH_ATTR_TYPE_ROCE ; 
 scalar_t__ ROCEE_QP1C_CFG0_0_REG ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 void* roce_get_field (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  roce_read (struct hns_roce_dev*,scalar_t__) ; 
 struct hns_roce_dev* to_hr_dev (int /*<<< orphan*/ ) ; 
 struct hns_roce_qp* to_hr_qp (struct ib_qp*) ; 

__attribute__((used)) static int hns_roce_v1_q_sqp(struct ib_qp *ibqp, struct ib_qp_attr *qp_attr,
			     int qp_attr_mask,
			     struct ib_qp_init_attr *qp_init_attr)
{
	struct hns_roce_dev *hr_dev = to_hr_dev(ibqp->device);
	struct hns_roce_qp *hr_qp = to_hr_qp(ibqp);
	struct hns_roce_sqp_context context;
	u32 addr;

	mutex_lock(&hr_qp->mutex);

	if (hr_qp->state == IB_QPS_RESET) {
		qp_attr->qp_state = IB_QPS_RESET;
		goto done;
	}

	addr = ROCEE_QP1C_CFG0_0_REG +
		hr_qp->port * sizeof(struct hns_roce_sqp_context);
	context.qp1c_bytes_4 = cpu_to_le32(roce_read(hr_dev, addr));
	context.sq_rq_bt_l = cpu_to_le32(roce_read(hr_dev, addr + 1));
	context.qp1c_bytes_12 = cpu_to_le32(roce_read(hr_dev, addr + 2));
	context.qp1c_bytes_16 = cpu_to_le32(roce_read(hr_dev, addr + 3));
	context.qp1c_bytes_20 = cpu_to_le32(roce_read(hr_dev, addr + 4));
	context.cur_rq_wqe_ba_l = cpu_to_le32(roce_read(hr_dev, addr + 5));
	context.qp1c_bytes_28 = cpu_to_le32(roce_read(hr_dev, addr + 6));
	context.qp1c_bytes_32 = cpu_to_le32(roce_read(hr_dev, addr + 7));
	context.cur_sq_wqe_ba_l = cpu_to_le32(roce_read(hr_dev, addr + 8));
	context.qp1c_bytes_40 = cpu_to_le32(roce_read(hr_dev, addr + 9));

	hr_qp->state = roce_get_field(context.qp1c_bytes_4,
				      QP1C_BYTES_4_QP_STATE_M,
				      QP1C_BYTES_4_QP_STATE_S);
	qp_attr->qp_state	= hr_qp->state;
	qp_attr->path_mtu	= IB_MTU_256;
	qp_attr->path_mig_state	= IB_MIG_ARMED;
	qp_attr->qkey		= QKEY_VAL;
	qp_attr->ah_attr.type   = RDMA_AH_ATTR_TYPE_ROCE;
	qp_attr->rq_psn		= 0;
	qp_attr->sq_psn		= 0;
	qp_attr->dest_qp_num	= 1;
	qp_attr->qp_access_flags = 6;

	qp_attr->pkey_index = roce_get_field(context.qp1c_bytes_20,
					     QP1C_BYTES_20_PKEY_IDX_M,
					     QP1C_BYTES_20_PKEY_IDX_S);
	qp_attr->port_num = hr_qp->port + 1;
	qp_attr->sq_draining = 0;
	qp_attr->max_rd_atomic = 0;
	qp_attr->max_dest_rd_atomic = 0;
	qp_attr->min_rnr_timer = 0;
	qp_attr->timeout = 0;
	qp_attr->retry_cnt = 0;
	qp_attr->rnr_retry = 0;
	qp_attr->alt_timeout = 0;

done:
	qp_attr->cur_qp_state = qp_attr->qp_state;
	qp_attr->cap.max_recv_wr = hr_qp->rq.wqe_cnt;
	qp_attr->cap.max_recv_sge = hr_qp->rq.max_gs;
	qp_attr->cap.max_send_wr = hr_qp->sq.wqe_cnt;
	qp_attr->cap.max_send_sge = hr_qp->sq.max_gs;
	qp_attr->cap.max_inline_data = 0;
	qp_init_attr->cap = qp_attr->cap;
	qp_init_attr->create_flags = 0;

	mutex_unlock(&hr_qp->mutex);

	return 0;
}