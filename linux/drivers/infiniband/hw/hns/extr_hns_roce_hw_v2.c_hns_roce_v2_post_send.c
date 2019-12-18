#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct TYPE_15__ {int invalidate_rkey; int /*<<< orphan*/  imm_data; } ;
struct ib_send_wr {int num_sge; int opcode; int send_flags; TYPE_6__* sg_list; TYPE_3__ ex; int /*<<< orphan*/  wr_id; struct ib_send_wr* next; } ;
struct ib_qp_attr {scalar_t__ qp_state; } ;
struct ib_qp {scalar_t__ qp_type; int /*<<< orphan*/  pd; int /*<<< orphan*/  device; } ;
struct hns_roce_wqe_frmr_seg {int dummy; } ;
struct hns_roce_v2_wqe_data_seg {int dummy; } ;
struct hns_roce_v2_ud_send_wqe {scalar_t__ byte_16; scalar_t__ byte_4; void* va; void* rkey; void* inv_key; void* immtdata; void* msg_len; int /*<<< orphan*/ * dgid; scalar_t__ byte_48; scalar_t__ byte_40; scalar_t__ byte_36; scalar_t__ byte_32; void* qkey; scalar_t__ byte_24; scalar_t__ byte_20; scalar_t__ dmac; } ;
struct hns_roce_v2_rc_send_wqe {scalar_t__ byte_16; scalar_t__ byte_4; void* va; void* rkey; void* inv_key; void* immtdata; void* msg_len; int /*<<< orphan*/ * dgid; scalar_t__ byte_48; scalar_t__ byte_40; scalar_t__ byte_36; scalar_t__ byte_32; void* qkey; scalar_t__ byte_24; scalar_t__ byte_20; scalar_t__ dmac; } ;
struct hns_roce_v2_db {scalar_t__ parameter; scalar_t__ byte_4; } ;
struct TYPE_21__ {int max_gs; int wqe_cnt; int head; int /*<<< orphan*/  lock; int /*<<< orphan*/  db_reg_l; int /*<<< orphan*/ * wrid; } ;
struct TYPE_12__ {int /*<<< orphan*/  send_cq; } ;
struct TYPE_13__ {int sge_cnt; } ;
struct hns_roce_qp {scalar_t__ state; unsigned int sq_next_wqe; unsigned int next_sge; size_t port; int qkey; int doorbell_qpn; int sl; TYPE_9__ sq; TYPE_10__ ibqp; int /*<<< orphan*/  phy_port; TYPE_1__ sge; } ;
struct hns_roce_dev {scalar_t__* dev_addr; struct device* dev; } ;
struct TYPE_14__ {int* mac; int hop_limit; int tclass; int flowlabel; int sl; int /*<<< orphan*/ * dgid; int /*<<< orphan*/  gid_index; scalar_t__ vlan_en; int /*<<< orphan*/  vlan; } ;
struct hns_roce_ah {TYPE_2__ av; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_20__ {int rkey; int /*<<< orphan*/  remote_addr; } ;
struct TYPE_19__ {int rkey; int /*<<< orphan*/  remote_addr; } ;
struct TYPE_18__ {int length; } ;
struct TYPE_17__ {int pdn; } ;
struct TYPE_16__ {int remote_qkey; int remote_qpn; int /*<<< orphan*/  ah; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GID_LEN_V2 ; 
 int HNS_ROCE_V2_SQ_DB ; 
 int HNS_ROCE_V2_WQE_OP_ATOM_CMP_AND_SWAP ; 
 int HNS_ROCE_V2_WQE_OP_ATOM_FETCH_AND_ADD ; 
 int HNS_ROCE_V2_WQE_OP_ATOM_MSK_CMP_AND_SWAP ; 
 int HNS_ROCE_V2_WQE_OP_ATOM_MSK_FETCH_AND_ADD ; 
 int HNS_ROCE_V2_WQE_OP_FAST_REG_PMR ; 
 int HNS_ROCE_V2_WQE_OP_LOCAL_INV ; 
 int HNS_ROCE_V2_WQE_OP_MASK ; 
 int HNS_ROCE_V2_WQE_OP_RDMA_READ ; 
 int HNS_ROCE_V2_WQE_OP_RDMA_WRITE ; 
 int HNS_ROCE_V2_WQE_OP_RDMA_WRITE_WITH_IMM ; 
 int HNS_ROCE_V2_WQE_OP_SEND ; 
 int HNS_ROCE_V2_WQE_OP_SEND_WITH_IMM ; 
 int HNS_ROCE_V2_WQE_OP_SEND_WITH_INV ; 
 scalar_t__ IB_QPS_ERR ; 
 scalar_t__ IB_QPS_INIT ; 
 scalar_t__ IB_QPS_RESET ; 
 scalar_t__ IB_QPS_RTR ; 
 scalar_t__ IB_QPT_GSI ; 
 scalar_t__ IB_QPT_RC ; 
 scalar_t__ IB_QPT_UD ; 
 int IB_QP_STATE ; 
 int IB_SEND_FENCE ; 
 int IB_SEND_SIGNALED ; 
 int IB_SEND_SOLICITED ; 
#define  IB_WR_ATOMIC_CMP_AND_SWP 139 
#define  IB_WR_ATOMIC_FETCH_AND_ADD 138 
#define  IB_WR_LOCAL_INV 137 
#define  IB_WR_MASKED_ATOMIC_CMP_AND_SWP 136 
#define  IB_WR_MASKED_ATOMIC_FETCH_AND_ADD 135 
#define  IB_WR_RDMA_READ 134 
#define  IB_WR_RDMA_WRITE 133 
#define  IB_WR_RDMA_WRITE_WITH_IMM 132 
#define  IB_WR_REG_MR 131 
#define  IB_WR_SEND 130 
#define  IB_WR_SEND_WITH_IMM 129 
#define  IB_WR_SEND_WITH_INV 128 
 int /*<<< orphan*/  V2_DB_BYTE_4_CMD_M ; 
 int /*<<< orphan*/  V2_DB_BYTE_4_CMD_S ; 
 int /*<<< orphan*/  V2_DB_BYTE_4_TAG_M ; 
 int /*<<< orphan*/  V2_DB_BYTE_4_TAG_S ; 
 int /*<<< orphan*/  V2_DB_PARAMETER_IDX_M ; 
 int /*<<< orphan*/  V2_DB_PARAMETER_IDX_S ; 
 int /*<<< orphan*/  V2_DB_PARAMETER_SL_M ; 
 int /*<<< orphan*/  V2_DB_PARAMETER_SL_S ; 
 int /*<<< orphan*/  V2_RC_SEND_WQE_BYTE_16_SGE_NUM_M ; 
 int /*<<< orphan*/  V2_RC_SEND_WQE_BYTE_16_SGE_NUM_S ; 
 int /*<<< orphan*/  V2_RC_SEND_WQE_BYTE_4_CQE_S ; 
 int /*<<< orphan*/  V2_RC_SEND_WQE_BYTE_4_FENCE_S ; 
 int /*<<< orphan*/  V2_RC_SEND_WQE_BYTE_4_OPCODE_M ; 
 int /*<<< orphan*/  V2_RC_SEND_WQE_BYTE_4_OPCODE_S ; 
 int /*<<< orphan*/  V2_RC_SEND_WQE_BYTE_4_OWNER_S ; 
 int /*<<< orphan*/  V2_RC_SEND_WQE_BYTE_4_SE_S ; 
 int /*<<< orphan*/  V2_RC_SEND_WQE_BYTE_4_SO_S ; 
 int /*<<< orphan*/  V2_UD_SEND_WQE_BYTE_16_PD_M ; 
 int /*<<< orphan*/  V2_UD_SEND_WQE_BYTE_16_PD_S ; 
 int /*<<< orphan*/  V2_UD_SEND_WQE_BYTE_16_SGE_NUM_M ; 
 int /*<<< orphan*/  V2_UD_SEND_WQE_BYTE_16_SGE_NUM_S ; 
 int /*<<< orphan*/  V2_UD_SEND_WQE_BYTE_20_MSG_START_SGE_IDX_M ; 
 int /*<<< orphan*/  V2_UD_SEND_WQE_BYTE_20_MSG_START_SGE_IDX_S ; 
 int /*<<< orphan*/  V2_UD_SEND_WQE_BYTE_24_UDPSPN_M ; 
 int /*<<< orphan*/  V2_UD_SEND_WQE_BYTE_24_UDPSPN_S ; 
 int /*<<< orphan*/  V2_UD_SEND_WQE_BYTE_32_DQPN_M ; 
 int /*<<< orphan*/  V2_UD_SEND_WQE_BYTE_32_DQPN_S ; 
 int /*<<< orphan*/  V2_UD_SEND_WQE_BYTE_36_HOPLIMIT_M ; 
 int /*<<< orphan*/  V2_UD_SEND_WQE_BYTE_36_HOPLIMIT_S ; 
 int /*<<< orphan*/  V2_UD_SEND_WQE_BYTE_36_TCLASS_M ; 
 int /*<<< orphan*/  V2_UD_SEND_WQE_BYTE_36_TCLASS_S ; 
 int /*<<< orphan*/  V2_UD_SEND_WQE_BYTE_36_VLAN_M ; 
 int /*<<< orphan*/  V2_UD_SEND_WQE_BYTE_36_VLAN_S ; 
 int /*<<< orphan*/  V2_UD_SEND_WQE_BYTE_40_FLOW_LABEL_M ; 
 int /*<<< orphan*/  V2_UD_SEND_WQE_BYTE_40_FLOW_LABEL_S ; 
 int /*<<< orphan*/  V2_UD_SEND_WQE_BYTE_40_LBI_S ; 
 int /*<<< orphan*/  V2_UD_SEND_WQE_BYTE_40_PORTN_M ; 
 int /*<<< orphan*/  V2_UD_SEND_WQE_BYTE_40_PORTN_S ; 
 int /*<<< orphan*/  V2_UD_SEND_WQE_BYTE_40_SL_M ; 
 int /*<<< orphan*/  V2_UD_SEND_WQE_BYTE_40_SL_S ; 
 int /*<<< orphan*/  V2_UD_SEND_WQE_BYTE_40_UD_VLAN_EN_S ; 
 int /*<<< orphan*/  V2_UD_SEND_WQE_BYTE_48_DMAC_4_M ; 
 int /*<<< orphan*/  V2_UD_SEND_WQE_BYTE_48_DMAC_4_S ; 
 int /*<<< orphan*/  V2_UD_SEND_WQE_BYTE_48_DMAC_5_M ; 
 int /*<<< orphan*/  V2_UD_SEND_WQE_BYTE_48_DMAC_5_S ; 
 int /*<<< orphan*/  V2_UD_SEND_WQE_BYTE_48_SGID_INDX_M ; 
 int /*<<< orphan*/  V2_UD_SEND_WQE_BYTE_48_SGID_INDX_S ; 
 int /*<<< orphan*/  V2_UD_SEND_WQE_BYTE_4_CQE_S ; 
 int /*<<< orphan*/  V2_UD_SEND_WQE_BYTE_4_OPCODE_M ; 
 int /*<<< orphan*/  V2_UD_SEND_WQE_BYTE_4_OPCODE_S ; 
 int /*<<< orphan*/  V2_UD_SEND_WQE_BYTE_4_OWNER_S ; 
 int /*<<< orphan*/  V2_UD_SEND_WQE_BYTE_4_SE_S ; 
 int /*<<< orphan*/  V2_UD_SEND_WQE_DMAC_0_M ; 
 int /*<<< orphan*/  V2_UD_SEND_WQE_DMAC_0_S ; 
 int /*<<< orphan*/  V2_UD_SEND_WQE_DMAC_1_M ; 
 int /*<<< orphan*/  V2_UD_SEND_WQE_DMAC_1_S ; 
 int /*<<< orphan*/  V2_UD_SEND_WQE_DMAC_2_M ; 
 int /*<<< orphan*/  V2_UD_SEND_WQE_DMAC_2_S ; 
 int /*<<< orphan*/  V2_UD_SEND_WQE_DMAC_3_M ; 
 int /*<<< orphan*/  V2_UD_SEND_WQE_DMAC_3_S ; 
 TYPE_7__* atomic_wr (struct ib_send_wr const*) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int) ; 
 void* cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,scalar_t__,...) ; 
 scalar_t__ ether_addr_equal_unaligned (int*,int /*<<< orphan*/ *) ; 
 void* get_send_wqe (struct hns_roce_qp*,unsigned int) ; 
 int hns_get_gid_index (struct hns_roce_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hns_roce_v2_modify_qp (TYPE_10__*,struct ib_qp_attr*,int,scalar_t__,scalar_t__) ; 
 scalar_t__ hns_roce_wq_overflow (TYPE_9__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_roce_write64 (struct hns_roce_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ilog2 (int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (void*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct hns_roce_v2_ud_send_wqe*,int /*<<< orphan*/ ,int) ; 
 TYPE_8__* rdma_wr (struct ib_send_wr const*) ; 
 int /*<<< orphan*/  reg_wr (struct ib_send_wr const*) ; 
 int /*<<< orphan*/  roce_set_bit (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  roce_set_field (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_atomic_seg (void*,TYPE_7__*) ; 
 int /*<<< orphan*/  set_data_seg_v2 (struct hns_roce_v2_wqe_data_seg*,TYPE_6__*) ; 
 int /*<<< orphan*/  set_extend_sge (struct hns_roce_qp*,struct ib_send_wr const*,unsigned int*) ; 
 int /*<<< orphan*/  set_frmr_seg (struct hns_roce_v2_ud_send_wqe*,struct hns_roce_wqe_frmr_seg*,int /*<<< orphan*/ ) ; 
 int set_rwqe_data_seg (struct ib_qp*,struct ib_send_wr const*,struct hns_roce_v2_ud_send_wqe*,void*,unsigned int*,struct ib_send_wr const**) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct hns_roce_ah* to_hr_ah (int /*<<< orphan*/ ) ; 
 struct hns_roce_dev* to_hr_dev (int /*<<< orphan*/ ) ; 
 TYPE_5__* to_hr_pd (int /*<<< orphan*/ ) ; 
 struct hns_roce_qp* to_hr_qp (struct ib_qp*) ; 
 TYPE_4__* ud_wr (struct ib_send_wr const*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int hns_roce_v2_post_send(struct ib_qp *ibqp,
				 const struct ib_send_wr *wr,
				 const struct ib_send_wr **bad_wr)
{
	struct hns_roce_dev *hr_dev = to_hr_dev(ibqp->device);
	struct hns_roce_ah *ah = to_hr_ah(ud_wr(wr)->ah);
	struct hns_roce_v2_ud_send_wqe *ud_sq_wqe;
	struct hns_roce_v2_rc_send_wqe *rc_sq_wqe;
	struct hns_roce_qp *qp = to_hr_qp(ibqp);
	struct hns_roce_wqe_frmr_seg *fseg;
	struct device *dev = hr_dev->dev;
	struct hns_roce_v2_db sq_db;
	struct ib_qp_attr attr;
	unsigned int sge_ind;
	unsigned int owner_bit;
	unsigned long flags;
	unsigned int ind;
	void *wqe = NULL;
	bool loopback;
	int attr_mask;
	u32 tmp_len;
	int ret = 0;
	u32 hr_op;
	u8 *smac;
	int nreq;
	int i;

	if (unlikely(ibqp->qp_type != IB_QPT_RC &&
		     ibqp->qp_type != IB_QPT_GSI &&
		     ibqp->qp_type != IB_QPT_UD)) {
		dev_err(dev, "Not supported QP(0x%x)type!\n", ibqp->qp_type);
		*bad_wr = wr;
		return -EOPNOTSUPP;
	}

	if (unlikely(qp->state == IB_QPS_RESET || qp->state == IB_QPS_INIT ||
		     qp->state == IB_QPS_RTR)) {
		dev_err(dev, "Post WQE fail, QP state %d err!\n", qp->state);
		*bad_wr = wr;
		return -EINVAL;
	}

	spin_lock_irqsave(&qp->sq.lock, flags);
	ind = qp->sq_next_wqe;
	sge_ind = qp->next_sge;

	for (nreq = 0; wr; ++nreq, wr = wr->next) {
		if (hns_roce_wq_overflow(&qp->sq, nreq, qp->ibqp.send_cq)) {
			ret = -ENOMEM;
			*bad_wr = wr;
			goto out;
		}

		if (unlikely(wr->num_sge > qp->sq.max_gs)) {
			dev_err(dev, "num_sge=%d > qp->sq.max_gs=%d\n",
				wr->num_sge, qp->sq.max_gs);
			ret = -EINVAL;
			*bad_wr = wr;
			goto out;
		}

		wqe = get_send_wqe(qp, ind & (qp->sq.wqe_cnt - 1));
		qp->sq.wrid[(qp->sq.head + nreq) & (qp->sq.wqe_cnt - 1)] =
								      wr->wr_id;

		owner_bit =
		       ~(((qp->sq.head + nreq) >> ilog2(qp->sq.wqe_cnt)) & 0x1);
		tmp_len = 0;

		/* Corresponding to the QP type, wqe process separately */
		if (ibqp->qp_type == IB_QPT_GSI) {
			ud_sq_wqe = wqe;
			memset(ud_sq_wqe, 0, sizeof(*ud_sq_wqe));

			roce_set_field(ud_sq_wqe->dmac, V2_UD_SEND_WQE_DMAC_0_M,
				       V2_UD_SEND_WQE_DMAC_0_S, ah->av.mac[0]);
			roce_set_field(ud_sq_wqe->dmac, V2_UD_SEND_WQE_DMAC_1_M,
				       V2_UD_SEND_WQE_DMAC_1_S, ah->av.mac[1]);
			roce_set_field(ud_sq_wqe->dmac, V2_UD_SEND_WQE_DMAC_2_M,
				       V2_UD_SEND_WQE_DMAC_2_S, ah->av.mac[2]);
			roce_set_field(ud_sq_wqe->dmac, V2_UD_SEND_WQE_DMAC_3_M,
				       V2_UD_SEND_WQE_DMAC_3_S, ah->av.mac[3]);
			roce_set_field(ud_sq_wqe->byte_48,
				       V2_UD_SEND_WQE_BYTE_48_DMAC_4_M,
				       V2_UD_SEND_WQE_BYTE_48_DMAC_4_S,
				       ah->av.mac[4]);
			roce_set_field(ud_sq_wqe->byte_48,
				       V2_UD_SEND_WQE_BYTE_48_DMAC_5_M,
				       V2_UD_SEND_WQE_BYTE_48_DMAC_5_S,
				       ah->av.mac[5]);

			/* MAC loopback */
			smac = (u8 *)hr_dev->dev_addr[qp->port];
			loopback = ether_addr_equal_unaligned(ah->av.mac,
							      smac) ? 1 : 0;

			roce_set_bit(ud_sq_wqe->byte_40,
				     V2_UD_SEND_WQE_BYTE_40_LBI_S, loopback);

			roce_set_field(ud_sq_wqe->byte_4,
				       V2_UD_SEND_WQE_BYTE_4_OPCODE_M,
				       V2_UD_SEND_WQE_BYTE_4_OPCODE_S,
				       HNS_ROCE_V2_WQE_OP_SEND);

			for (i = 0; i < wr->num_sge; i++)
				tmp_len += wr->sg_list[i].length;

			ud_sq_wqe->msg_len =
			 cpu_to_le32(le32_to_cpu(ud_sq_wqe->msg_len) + tmp_len);

			switch (wr->opcode) {
			case IB_WR_SEND_WITH_IMM:
			case IB_WR_RDMA_WRITE_WITH_IMM:
				ud_sq_wqe->immtdata =
				      cpu_to_le32(be32_to_cpu(wr->ex.imm_data));
				break;
			default:
				ud_sq_wqe->immtdata = 0;
				break;
			}

			/* Set sig attr */
			roce_set_bit(ud_sq_wqe->byte_4,
				   V2_UD_SEND_WQE_BYTE_4_CQE_S,
				   (wr->send_flags & IB_SEND_SIGNALED) ? 1 : 0);

			/* Set se attr */
			roce_set_bit(ud_sq_wqe->byte_4,
				  V2_UD_SEND_WQE_BYTE_4_SE_S,
				  (wr->send_flags & IB_SEND_SOLICITED) ? 1 : 0);

			roce_set_bit(ud_sq_wqe->byte_4,
				     V2_UD_SEND_WQE_BYTE_4_OWNER_S, owner_bit);

			roce_set_field(ud_sq_wqe->byte_16,
				       V2_UD_SEND_WQE_BYTE_16_PD_M,
				       V2_UD_SEND_WQE_BYTE_16_PD_S,
				       to_hr_pd(ibqp->pd)->pdn);

			roce_set_field(ud_sq_wqe->byte_16,
				       V2_UD_SEND_WQE_BYTE_16_SGE_NUM_M,
				       V2_UD_SEND_WQE_BYTE_16_SGE_NUM_S,
				       wr->num_sge);

			roce_set_field(ud_sq_wqe->byte_20,
				     V2_UD_SEND_WQE_BYTE_20_MSG_START_SGE_IDX_M,
				     V2_UD_SEND_WQE_BYTE_20_MSG_START_SGE_IDX_S,
				     sge_ind & (qp->sge.sge_cnt - 1));

			roce_set_field(ud_sq_wqe->byte_24,
				       V2_UD_SEND_WQE_BYTE_24_UDPSPN_M,
				       V2_UD_SEND_WQE_BYTE_24_UDPSPN_S, 0);
			ud_sq_wqe->qkey =
			     cpu_to_le32(ud_wr(wr)->remote_qkey & 0x80000000 ?
			     qp->qkey : ud_wr(wr)->remote_qkey);
			roce_set_field(ud_sq_wqe->byte_32,
				       V2_UD_SEND_WQE_BYTE_32_DQPN_M,
				       V2_UD_SEND_WQE_BYTE_32_DQPN_S,
				       ud_wr(wr)->remote_qpn);

			roce_set_field(ud_sq_wqe->byte_36,
				       V2_UD_SEND_WQE_BYTE_36_VLAN_M,
				       V2_UD_SEND_WQE_BYTE_36_VLAN_S,
				       le16_to_cpu(ah->av.vlan));
			roce_set_field(ud_sq_wqe->byte_36,
				       V2_UD_SEND_WQE_BYTE_36_HOPLIMIT_M,
				       V2_UD_SEND_WQE_BYTE_36_HOPLIMIT_S,
				       ah->av.hop_limit);
			roce_set_field(ud_sq_wqe->byte_36,
				       V2_UD_SEND_WQE_BYTE_36_TCLASS_M,
				       V2_UD_SEND_WQE_BYTE_36_TCLASS_S,
				       ah->av.tclass);
			roce_set_field(ud_sq_wqe->byte_40,
				       V2_UD_SEND_WQE_BYTE_40_FLOW_LABEL_M,
				       V2_UD_SEND_WQE_BYTE_40_FLOW_LABEL_S,
				       ah->av.flowlabel);
			roce_set_field(ud_sq_wqe->byte_40,
				       V2_UD_SEND_WQE_BYTE_40_SL_M,
				       V2_UD_SEND_WQE_BYTE_40_SL_S,
				       ah->av.sl);
			roce_set_field(ud_sq_wqe->byte_40,
				       V2_UD_SEND_WQE_BYTE_40_PORTN_M,
				       V2_UD_SEND_WQE_BYTE_40_PORTN_S,
				       qp->port);

			roce_set_bit(ud_sq_wqe->byte_40,
				     V2_UD_SEND_WQE_BYTE_40_UD_VLAN_EN_S,
				     ah->av.vlan_en ? 1 : 0);
			roce_set_field(ud_sq_wqe->byte_48,
				       V2_UD_SEND_WQE_BYTE_48_SGID_INDX_M,
				       V2_UD_SEND_WQE_BYTE_48_SGID_INDX_S,
				       hns_get_gid_index(hr_dev, qp->phy_port,
							 ah->av.gid_index));

			memcpy(&ud_sq_wqe->dgid[0], &ah->av.dgid[0],
			       GID_LEN_V2);

			set_extend_sge(qp, wr, &sge_ind);
			ind++;
		} else if (ibqp->qp_type == IB_QPT_RC) {
			rc_sq_wqe = wqe;
			memset(rc_sq_wqe, 0, sizeof(*rc_sq_wqe));
			for (i = 0; i < wr->num_sge; i++)
				tmp_len += wr->sg_list[i].length;

			rc_sq_wqe->msg_len =
			 cpu_to_le32(le32_to_cpu(rc_sq_wqe->msg_len) + tmp_len);

			switch (wr->opcode) {
			case IB_WR_SEND_WITH_IMM:
			case IB_WR_RDMA_WRITE_WITH_IMM:
				rc_sq_wqe->immtdata =
				      cpu_to_le32(be32_to_cpu(wr->ex.imm_data));
				break;
			case IB_WR_SEND_WITH_INV:
				rc_sq_wqe->inv_key =
					cpu_to_le32(wr->ex.invalidate_rkey);
				break;
			default:
				rc_sq_wqe->immtdata = 0;
				break;
			}

			roce_set_bit(rc_sq_wqe->byte_4,
				     V2_RC_SEND_WQE_BYTE_4_FENCE_S,
				     (wr->send_flags & IB_SEND_FENCE) ? 1 : 0);

			roce_set_bit(rc_sq_wqe->byte_4,
				  V2_RC_SEND_WQE_BYTE_4_SE_S,
				  (wr->send_flags & IB_SEND_SOLICITED) ? 1 : 0);

			roce_set_bit(rc_sq_wqe->byte_4,
				   V2_RC_SEND_WQE_BYTE_4_CQE_S,
				   (wr->send_flags & IB_SEND_SIGNALED) ? 1 : 0);

			roce_set_bit(rc_sq_wqe->byte_4,
				     V2_RC_SEND_WQE_BYTE_4_OWNER_S, owner_bit);

			wqe += sizeof(struct hns_roce_v2_rc_send_wqe);
			switch (wr->opcode) {
			case IB_WR_RDMA_READ:
				hr_op = HNS_ROCE_V2_WQE_OP_RDMA_READ;
				rc_sq_wqe->rkey =
					cpu_to_le32(rdma_wr(wr)->rkey);
				rc_sq_wqe->va =
					cpu_to_le64(rdma_wr(wr)->remote_addr);
				break;
			case IB_WR_RDMA_WRITE:
				hr_op = HNS_ROCE_V2_WQE_OP_RDMA_WRITE;
				rc_sq_wqe->rkey =
					cpu_to_le32(rdma_wr(wr)->rkey);
				rc_sq_wqe->va =
					cpu_to_le64(rdma_wr(wr)->remote_addr);
				break;
			case IB_WR_RDMA_WRITE_WITH_IMM:
				hr_op = HNS_ROCE_V2_WQE_OP_RDMA_WRITE_WITH_IMM;
				rc_sq_wqe->rkey =
					cpu_to_le32(rdma_wr(wr)->rkey);
				rc_sq_wqe->va =
					cpu_to_le64(rdma_wr(wr)->remote_addr);
				break;
			case IB_WR_SEND:
				hr_op = HNS_ROCE_V2_WQE_OP_SEND;
				break;
			case IB_WR_SEND_WITH_INV:
				hr_op = HNS_ROCE_V2_WQE_OP_SEND_WITH_INV;
				break;
			case IB_WR_SEND_WITH_IMM:
				hr_op = HNS_ROCE_V2_WQE_OP_SEND_WITH_IMM;
				break;
			case IB_WR_LOCAL_INV:
				hr_op = HNS_ROCE_V2_WQE_OP_LOCAL_INV;
				roce_set_bit(rc_sq_wqe->byte_4,
					       V2_RC_SEND_WQE_BYTE_4_SO_S, 1);
				rc_sq_wqe->inv_key =
					    cpu_to_le32(wr->ex.invalidate_rkey);
				break;
			case IB_WR_REG_MR:
				hr_op = HNS_ROCE_V2_WQE_OP_FAST_REG_PMR;
				fseg = wqe;
				set_frmr_seg(rc_sq_wqe, fseg, reg_wr(wr));
				break;
			case IB_WR_ATOMIC_CMP_AND_SWP:
				hr_op = HNS_ROCE_V2_WQE_OP_ATOM_CMP_AND_SWAP;
				rc_sq_wqe->rkey =
					cpu_to_le32(atomic_wr(wr)->rkey);
				rc_sq_wqe->va =
					cpu_to_le64(atomic_wr(wr)->remote_addr);
				break;
			case IB_WR_ATOMIC_FETCH_AND_ADD:
				hr_op = HNS_ROCE_V2_WQE_OP_ATOM_FETCH_AND_ADD;
				rc_sq_wqe->rkey =
					cpu_to_le32(atomic_wr(wr)->rkey);
				rc_sq_wqe->va =
					cpu_to_le64(atomic_wr(wr)->remote_addr);
				break;
			case IB_WR_MASKED_ATOMIC_CMP_AND_SWP:
				hr_op =
				       HNS_ROCE_V2_WQE_OP_ATOM_MSK_CMP_AND_SWAP;
				break;
			case IB_WR_MASKED_ATOMIC_FETCH_AND_ADD:
				hr_op =
				      HNS_ROCE_V2_WQE_OP_ATOM_MSK_FETCH_AND_ADD;
				break;
			default:
				hr_op = HNS_ROCE_V2_WQE_OP_MASK;
				break;
			}

			roce_set_field(rc_sq_wqe->byte_4,
				       V2_RC_SEND_WQE_BYTE_4_OPCODE_M,
				       V2_RC_SEND_WQE_BYTE_4_OPCODE_S, hr_op);

			if (wr->opcode == IB_WR_ATOMIC_CMP_AND_SWP ||
			    wr->opcode == IB_WR_ATOMIC_FETCH_AND_ADD) {
				struct hns_roce_v2_wqe_data_seg *dseg;

				dseg = wqe;
				set_data_seg_v2(dseg, wr->sg_list);
				wqe += sizeof(struct hns_roce_v2_wqe_data_seg);
				set_atomic_seg(wqe, atomic_wr(wr));
				roce_set_field(rc_sq_wqe->byte_16,
					       V2_RC_SEND_WQE_BYTE_16_SGE_NUM_M,
					       V2_RC_SEND_WQE_BYTE_16_SGE_NUM_S,
					       wr->num_sge);
			} else if (wr->opcode != IB_WR_REG_MR) {
				ret = set_rwqe_data_seg(ibqp, wr, rc_sq_wqe,
							wqe, &sge_ind, bad_wr);
				if (ret)
					goto out;
			}

			ind++;
		} else {
			dev_err(dev, "Illegal qp_type(0x%x)\n", ibqp->qp_type);
			spin_unlock_irqrestore(&qp->sq.lock, flags);
			*bad_wr = wr;
			return -EOPNOTSUPP;
		}
	}

out:
	if (likely(nreq)) {
		qp->sq.head += nreq;
		/* Memory barrier */
		wmb();

		sq_db.byte_4 = 0;
		sq_db.parameter = 0;

		roce_set_field(sq_db.byte_4, V2_DB_BYTE_4_TAG_M,
			       V2_DB_BYTE_4_TAG_S, qp->doorbell_qpn);
		roce_set_field(sq_db.byte_4, V2_DB_BYTE_4_CMD_M,
			       V2_DB_BYTE_4_CMD_S, HNS_ROCE_V2_SQ_DB);
		roce_set_field(sq_db.parameter, V2_DB_PARAMETER_IDX_M,
			       V2_DB_PARAMETER_IDX_S,
			       qp->sq.head & ((qp->sq.wqe_cnt << 1) - 1));
		roce_set_field(sq_db.parameter, V2_DB_PARAMETER_SL_M,
			       V2_DB_PARAMETER_SL_S, qp->sl);

		hns_roce_write64(hr_dev, (__le32 *)&sq_db, qp->sq.db_reg_l);

		qp->sq_next_wqe = ind;
		qp->next_sge = sge_ind;

		if (qp->state == IB_QPS_ERR) {
			attr_mask = IB_QP_STATE;
			attr.qp_state = IB_QPS_ERR;

			ret = hns_roce_v2_modify_qp(&qp->ibqp, &attr, attr_mask,
						    qp->state, IB_QPS_ERR);
			if (ret) {
				spin_unlock_irqrestore(&qp->sq.lock, flags);
				*bad_wr = wr;
				return ret;
			}
		}
	}

	spin_unlock_irqrestore(&qp->sq.lock, flags);

	return ret;
}