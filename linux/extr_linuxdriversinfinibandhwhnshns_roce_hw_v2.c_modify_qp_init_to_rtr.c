#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u64 ;
typedef  size_t u32 ;
typedef  int u16 ;
struct TYPE_13__ {scalar_t__ dmac; } ;
struct TYPE_17__ {TYPE_4__ roce; } ;
struct ib_qp_attr {int min_rnr_timer; int rq_psn; int port_num; int dest_qp_num; int path_mtu; TYPE_8__ ah_attr; scalar_t__ max_dest_rd_atomic; } ;
struct ib_qp {scalar_t__ qp_type; int /*<<< orphan*/  device; } ;
struct ib_global_route {int /*<<< orphan*/  sgid_index; } ;
struct hns_roce_v2_qp_context {size_t wqe_sge_ba; size_t rq_cur_blk_addr; size_t rq_nxt_blk_addr; size_t trrl_ba; size_t irrl_ba; int /*<<< orphan*/  byte_168_irrl_idx; int /*<<< orphan*/  byte_132_trrl; int /*<<< orphan*/  byte_152_raq; scalar_t__ rq_rnr_timer; int /*<<< orphan*/  byte_108_rx_reqepsn; int /*<<< orphan*/  byte_96_rx_reqmsn; int /*<<< orphan*/  byte_84_rq_ci_pi; int /*<<< orphan*/  byte_24_mtu_tc; int /*<<< orphan*/  byte_56_dqpn_err; int /*<<< orphan*/  byte_52_udpspn_dmac; int /*<<< orphan*/  dmac; int /*<<< orphan*/  byte_20_smac_sgid_idx; int /*<<< orphan*/  byte_140_raq; int /*<<< orphan*/  byte_28_at_fl; int /*<<< orphan*/  byte_252_err_txcqn; int /*<<< orphan*/  byte_208_irrl; int /*<<< orphan*/  byte_104_rq_sge; int /*<<< orphan*/  byte_92_srq_info; int /*<<< orphan*/  byte_80_rnr_rx_cqn; int /*<<< orphan*/  byte_16_buf_ba_pg_sz; int /*<<< orphan*/  byte_12_sq_hop; } ;
struct TYPE_16__ {size_t offset; int head; } ;
struct TYPE_14__ {int max_gs; } ;
struct TYPE_11__ {int /*<<< orphan*/  first_seg; } ;
struct hns_roce_qp {int sq_signal_bits; int port; TYPE_7__ rq; TYPE_5__ sq; int /*<<< orphan*/  qpn; TYPE_2__ mtt; } ;
struct TYPE_15__ {scalar_t__ mtt_hop_num; int mtt_ba_pg_sz; int mtt_buf_pg_sz; } ;
struct TYPE_12__ {int /*<<< orphan*/  trrl_table; int /*<<< orphan*/  irrl_table; } ;
struct TYPE_10__ {int /*<<< orphan*/  mtt_table; } ;
struct hns_roce_dev {int loop_idc; scalar_t__* dev_addr; TYPE_6__ caps; TYPE_3__ qp_table; TYPE_1__ mr_table; struct device* dev; } ;
struct device {int dummy; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ HNS_ROCE_HOP_NUM_0 ; 
 int IB_MTU_4096 ; 
 scalar_t__ IB_QPT_GSI ; 
 scalar_t__ IB_QPT_UD ; 
 int IB_QP_ALT_PATH ; 
 int IB_QP_DEST_QPN ; 
 int IB_QP_MAX_DEST_RD_ATOMIC ; 
 int IB_QP_PATH_MTU ; 
 int IB_QP_PORT ; 
 int PAGE_ADDR_SHIFT ; 
 int PAGE_SHIFT ; 
 int PG_SHIFT_OFFSET ; 
 int /*<<< orphan*/  V2_QPC_BYTE_104_RQ_NXT_BLK_ADDR_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_104_RQ_NXT_BLK_ADDR_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_108_RX_REQ_EPSN_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_108_RX_REQ_EPSN_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_108_RX_REQ_LAST_OPTYPE_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_108_RX_REQ_LAST_OPTYPE_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_108_RX_REQ_PSN_ERR_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_12_SQ_HOP_NUM_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_12_SQ_HOP_NUM_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_12_WQE_SGE_BA_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_12_WQE_SGE_BA_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_132_TRRL_BA_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_132_TRRL_BA_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_132_TRRL_HEAD_MAX_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_132_TRRL_HEAD_MAX_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_132_TRRL_TAIL_MAX_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_132_TRRL_TAIL_MAX_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_140_RR_MAX_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_140_RR_MAX_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_140_TRRL_BA_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_140_TRRL_BA_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_152_RAQ_PSN_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_152_RAQ_PSN_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_168_LP_SGEN_INI_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_168_LP_SGEN_INI_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_16_WQE_SGE_BA_PG_SZ_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_16_WQE_SGE_BA_PG_SZ_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_16_WQE_SGE_BUF_PG_SZ_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_16_WQE_SGE_BUF_PG_SZ_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_208_IRRL_BA_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_208_IRRL_BA_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_208_RMT_E2E_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_20_RQ_HOP_NUM_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_20_RQ_HOP_NUM_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_20_SGE_HOP_NUM_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_20_SGE_HOP_NUM_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_20_SGID_IDX_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_20_SGID_IDX_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_24_MTU_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_24_MTU_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_252_SIG_TYPE_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_28_LBI_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_52_DMAC_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_52_DMAC_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_56_DQPN_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_56_DQPN_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_56_LP_PKTN_INI_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_56_LP_PKTN_INI_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_80_MIN_RNR_TIME_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_80_MIN_RNR_TIME_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_84_RQ_CONSUMER_IDX_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_84_RQ_CONSUMER_IDX_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_84_RQ_PRODUCER_IDX_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_84_RQ_PRODUCER_IDX_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_92_RQ_CUR_BLK_ADDR_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_92_RQ_CUR_BLK_ADDR_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_96_RX_REQ_MSN_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_96_RX_REQ_MSN_S ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 scalar_t__ ether_addr_equal_unaligned (scalar_t__*,scalar_t__*) ; 
 int fls (scalar_t__) ; 
 int hns_get_gid_index (struct hns_roce_dev*,scalar_t__,int /*<<< orphan*/ ) ; 
 int* hns_roce_table_find (struct hns_roce_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__*,int) ; 
 scalar_t__ rdma_ah_get_port_num (TYPE_8__*) ; 
 struct ib_global_route* rdma_ah_read_grh (TYPE_8__*) ; 
 int /*<<< orphan*/  roce_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  roce_set_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct hns_roce_dev* to_hr_dev (int /*<<< orphan*/ ) ; 
 struct hns_roce_qp* to_hr_qp (struct ib_qp*) ; 

__attribute__((used)) static int modify_qp_init_to_rtr(struct ib_qp *ibqp,
				 const struct ib_qp_attr *attr, int attr_mask,
				 struct hns_roce_v2_qp_context *context,
				 struct hns_roce_v2_qp_context *qpc_mask)
{
	const struct ib_global_route *grh = rdma_ah_read_grh(&attr->ah_attr);
	struct hns_roce_dev *hr_dev = to_hr_dev(ibqp->device);
	struct hns_roce_qp *hr_qp = to_hr_qp(ibqp);
	struct device *dev = hr_dev->dev;
	dma_addr_t dma_handle_3;
	dma_addr_t dma_handle_2;
	dma_addr_t dma_handle;
	u32 page_size;
	u8 port_num;
	u64 *mtts_3;
	u64 *mtts_2;
	u64 *mtts;
	u8 *dmac;
	u8 *smac;
	int port;

	/* Search qp buf's mtts */
	mtts = hns_roce_table_find(hr_dev, &hr_dev->mr_table.mtt_table,
				   hr_qp->mtt.first_seg, &dma_handle);
	if (!mtts) {
		dev_err(dev, "qp buf pa find failed\n");
		return -EINVAL;
	}

	/* Search IRRL's mtts */
	mtts_2 = hns_roce_table_find(hr_dev, &hr_dev->qp_table.irrl_table,
				     hr_qp->qpn, &dma_handle_2);
	if (!mtts_2) {
		dev_err(dev, "qp irrl_table find failed\n");
		return -EINVAL;
	}

	/* Search TRRL's mtts */
	mtts_3 = hns_roce_table_find(hr_dev, &hr_dev->qp_table.trrl_table,
				     hr_qp->qpn, &dma_handle_3);
	if (!mtts_3) {
		dev_err(dev, "qp trrl_table find failed\n");
		return -EINVAL;
	}

	if (attr_mask & IB_QP_ALT_PATH) {
		dev_err(dev, "INIT2RTR attr_mask (0x%x) error\n", attr_mask);
		return -EINVAL;
	}

	dmac = (u8 *)attr->ah_attr.roce.dmac;
	context->wqe_sge_ba = (u32)(dma_handle >> 3);
	qpc_mask->wqe_sge_ba = 0;

	/*
	 * In v2 engine, software pass context and context mask to hardware
	 * when modifying qp. If software need modify some fields in context,
	 * we should set all bits of the relevant fields in context mask to
	 * 0 at the same time, else set them to 0x1.
	 */
	roce_set_field(context->byte_12_sq_hop, V2_QPC_BYTE_12_WQE_SGE_BA_M,
		       V2_QPC_BYTE_12_WQE_SGE_BA_S, dma_handle >> (32 + 3));
	roce_set_field(qpc_mask->byte_12_sq_hop, V2_QPC_BYTE_12_WQE_SGE_BA_M,
		       V2_QPC_BYTE_12_WQE_SGE_BA_S, 0);

	roce_set_field(context->byte_12_sq_hop, V2_QPC_BYTE_12_SQ_HOP_NUM_M,
		       V2_QPC_BYTE_12_SQ_HOP_NUM_S,
		       hr_dev->caps.mtt_hop_num == HNS_ROCE_HOP_NUM_0 ?
		       0 : hr_dev->caps.mtt_hop_num);
	roce_set_field(qpc_mask->byte_12_sq_hop, V2_QPC_BYTE_12_SQ_HOP_NUM_M,
		       V2_QPC_BYTE_12_SQ_HOP_NUM_S, 0);

	roce_set_field(context->byte_20_smac_sgid_idx,
		       V2_QPC_BYTE_20_SGE_HOP_NUM_M,
		       V2_QPC_BYTE_20_SGE_HOP_NUM_S,
		       ((ibqp->qp_type == IB_QPT_GSI) || hr_qp->sq.max_gs > 2) ?
		       hr_dev->caps.mtt_hop_num : 0);
	roce_set_field(qpc_mask->byte_20_smac_sgid_idx,
		       V2_QPC_BYTE_20_SGE_HOP_NUM_M,
		       V2_QPC_BYTE_20_SGE_HOP_NUM_S, 0);

	roce_set_field(context->byte_20_smac_sgid_idx,
		       V2_QPC_BYTE_20_RQ_HOP_NUM_M,
		       V2_QPC_BYTE_20_RQ_HOP_NUM_S,
		       hr_dev->caps.mtt_hop_num == HNS_ROCE_HOP_NUM_0 ?
		       0 : hr_dev->caps.mtt_hop_num);
	roce_set_field(qpc_mask->byte_20_smac_sgid_idx,
		       V2_QPC_BYTE_20_RQ_HOP_NUM_M,
		       V2_QPC_BYTE_20_RQ_HOP_NUM_S, 0);

	roce_set_field(context->byte_16_buf_ba_pg_sz,
		       V2_QPC_BYTE_16_WQE_SGE_BA_PG_SZ_M,
		       V2_QPC_BYTE_16_WQE_SGE_BA_PG_SZ_S,
		       hr_dev->caps.mtt_ba_pg_sz + PG_SHIFT_OFFSET);
	roce_set_field(qpc_mask->byte_16_buf_ba_pg_sz,
		       V2_QPC_BYTE_16_WQE_SGE_BA_PG_SZ_M,
		       V2_QPC_BYTE_16_WQE_SGE_BA_PG_SZ_S, 0);

	roce_set_field(context->byte_16_buf_ba_pg_sz,
		       V2_QPC_BYTE_16_WQE_SGE_BUF_PG_SZ_M,
		       V2_QPC_BYTE_16_WQE_SGE_BUF_PG_SZ_S,
		       hr_dev->caps.mtt_buf_pg_sz + PG_SHIFT_OFFSET);
	roce_set_field(qpc_mask->byte_16_buf_ba_pg_sz,
		       V2_QPC_BYTE_16_WQE_SGE_BUF_PG_SZ_M,
		       V2_QPC_BYTE_16_WQE_SGE_BUF_PG_SZ_S, 0);

	roce_set_field(context->byte_80_rnr_rx_cqn,
		       V2_QPC_BYTE_80_MIN_RNR_TIME_M,
		       V2_QPC_BYTE_80_MIN_RNR_TIME_S, attr->min_rnr_timer);
	roce_set_field(qpc_mask->byte_80_rnr_rx_cqn,
		       V2_QPC_BYTE_80_MIN_RNR_TIME_M,
		       V2_QPC_BYTE_80_MIN_RNR_TIME_S, 0);

	page_size = 1 << (hr_dev->caps.mtt_buf_pg_sz + PAGE_SHIFT);
	context->rq_cur_blk_addr = (u32)(mtts[hr_qp->rq.offset / page_size]
				    >> PAGE_ADDR_SHIFT);
	qpc_mask->rq_cur_blk_addr = 0;

	roce_set_field(context->byte_92_srq_info,
		       V2_QPC_BYTE_92_RQ_CUR_BLK_ADDR_M,
		       V2_QPC_BYTE_92_RQ_CUR_BLK_ADDR_S,
		       mtts[hr_qp->rq.offset / page_size]
		       >> (32 + PAGE_ADDR_SHIFT));
	roce_set_field(qpc_mask->byte_92_srq_info,
		       V2_QPC_BYTE_92_RQ_CUR_BLK_ADDR_M,
		       V2_QPC_BYTE_92_RQ_CUR_BLK_ADDR_S, 0);

	context->rq_nxt_blk_addr = (u32)(mtts[hr_qp->rq.offset / page_size + 1]
				    >> PAGE_ADDR_SHIFT);
	qpc_mask->rq_nxt_blk_addr = 0;

	roce_set_field(context->byte_104_rq_sge,
		       V2_QPC_BYTE_104_RQ_NXT_BLK_ADDR_M,
		       V2_QPC_BYTE_104_RQ_NXT_BLK_ADDR_S,
		       mtts[hr_qp->rq.offset / page_size + 1]
		       >> (32 + PAGE_ADDR_SHIFT));
	roce_set_field(qpc_mask->byte_104_rq_sge,
		       V2_QPC_BYTE_104_RQ_NXT_BLK_ADDR_M,
		       V2_QPC_BYTE_104_RQ_NXT_BLK_ADDR_S, 0);

	roce_set_field(context->byte_108_rx_reqepsn,
		       V2_QPC_BYTE_108_RX_REQ_EPSN_M,
		       V2_QPC_BYTE_108_RX_REQ_EPSN_S, attr->rq_psn);
	roce_set_field(qpc_mask->byte_108_rx_reqepsn,
		       V2_QPC_BYTE_108_RX_REQ_EPSN_M,
		       V2_QPC_BYTE_108_RX_REQ_EPSN_S, 0);

	roce_set_field(context->byte_132_trrl, V2_QPC_BYTE_132_TRRL_BA_M,
		       V2_QPC_BYTE_132_TRRL_BA_S, dma_handle_3 >> 4);
	roce_set_field(qpc_mask->byte_132_trrl, V2_QPC_BYTE_132_TRRL_BA_M,
		       V2_QPC_BYTE_132_TRRL_BA_S, 0);
	context->trrl_ba = (u32)(dma_handle_3 >> (16 + 4));
	qpc_mask->trrl_ba = 0;
	roce_set_field(context->byte_140_raq, V2_QPC_BYTE_140_TRRL_BA_M,
		       V2_QPC_BYTE_140_TRRL_BA_S,
		       (u32)(dma_handle_3 >> (32 + 16 + 4)));
	roce_set_field(qpc_mask->byte_140_raq, V2_QPC_BYTE_140_TRRL_BA_M,
		       V2_QPC_BYTE_140_TRRL_BA_S, 0);

	context->irrl_ba = (u32)(dma_handle_2 >> 6);
	qpc_mask->irrl_ba = 0;
	roce_set_field(context->byte_208_irrl, V2_QPC_BYTE_208_IRRL_BA_M,
		       V2_QPC_BYTE_208_IRRL_BA_S,
		       dma_handle_2 >> (32 + 6));
	roce_set_field(qpc_mask->byte_208_irrl, V2_QPC_BYTE_208_IRRL_BA_M,
		       V2_QPC_BYTE_208_IRRL_BA_S, 0);

	roce_set_bit(context->byte_208_irrl, V2_QPC_BYTE_208_RMT_E2E_S, 1);
	roce_set_bit(qpc_mask->byte_208_irrl, V2_QPC_BYTE_208_RMT_E2E_S, 0);

	roce_set_bit(context->byte_252_err_txcqn, V2_QPC_BYTE_252_SIG_TYPE_S,
		     hr_qp->sq_signal_bits);
	roce_set_bit(qpc_mask->byte_252_err_txcqn, V2_QPC_BYTE_252_SIG_TYPE_S,
		     0);

	port = (attr_mask & IB_QP_PORT) ? (attr->port_num - 1) : hr_qp->port;

	smac = (u8 *)hr_dev->dev_addr[port];
	/* when dmac equals smac or loop_idc is 1, it should loopback */
	if (ether_addr_equal_unaligned(dmac, smac) ||
	    hr_dev->loop_idc == 0x1) {
		roce_set_bit(context->byte_28_at_fl, V2_QPC_BYTE_28_LBI_S, 1);
		roce_set_bit(qpc_mask->byte_28_at_fl, V2_QPC_BYTE_28_LBI_S, 0);
	}

	if ((attr_mask & IB_QP_MAX_DEST_RD_ATOMIC) &&
	     attr->max_dest_rd_atomic) {
		roce_set_field(context->byte_140_raq, V2_QPC_BYTE_140_RR_MAX_M,
			       V2_QPC_BYTE_140_RR_MAX_S,
			       fls(attr->max_dest_rd_atomic - 1));
		roce_set_field(qpc_mask->byte_140_raq, V2_QPC_BYTE_140_RR_MAX_M,
			       V2_QPC_BYTE_140_RR_MAX_S, 0);
	}

	if (attr_mask & IB_QP_DEST_QPN) {
		roce_set_field(context->byte_56_dqpn_err, V2_QPC_BYTE_56_DQPN_M,
			       V2_QPC_BYTE_56_DQPN_S, attr->dest_qp_num);
		roce_set_field(qpc_mask->byte_56_dqpn_err,
			       V2_QPC_BYTE_56_DQPN_M, V2_QPC_BYTE_56_DQPN_S, 0);
	}

	/* Configure GID index */
	port_num = rdma_ah_get_port_num(&attr->ah_attr);
	roce_set_field(context->byte_20_smac_sgid_idx,
		       V2_QPC_BYTE_20_SGID_IDX_M,
		       V2_QPC_BYTE_20_SGID_IDX_S,
		       hns_get_gid_index(hr_dev, port_num - 1,
					 grh->sgid_index));
	roce_set_field(qpc_mask->byte_20_smac_sgid_idx,
		       V2_QPC_BYTE_20_SGID_IDX_M,
		       V2_QPC_BYTE_20_SGID_IDX_S, 0);
	memcpy(&(context->dmac), dmac, 4);
	roce_set_field(context->byte_52_udpspn_dmac, V2_QPC_BYTE_52_DMAC_M,
		       V2_QPC_BYTE_52_DMAC_S, *((u16 *)(&dmac[4])));
	qpc_mask->dmac = 0;
	roce_set_field(qpc_mask->byte_52_udpspn_dmac, V2_QPC_BYTE_52_DMAC_M,
		       V2_QPC_BYTE_52_DMAC_S, 0);

	roce_set_field(context->byte_56_dqpn_err, V2_QPC_BYTE_56_LP_PKTN_INI_M,
		       V2_QPC_BYTE_56_LP_PKTN_INI_S, 4);
	roce_set_field(qpc_mask->byte_56_dqpn_err, V2_QPC_BYTE_56_LP_PKTN_INI_M,
		       V2_QPC_BYTE_56_LP_PKTN_INI_S, 0);

	if (ibqp->qp_type == IB_QPT_GSI || ibqp->qp_type == IB_QPT_UD)
		roce_set_field(context->byte_24_mtu_tc, V2_QPC_BYTE_24_MTU_M,
			       V2_QPC_BYTE_24_MTU_S, IB_MTU_4096);
	else if (attr_mask & IB_QP_PATH_MTU)
		roce_set_field(context->byte_24_mtu_tc, V2_QPC_BYTE_24_MTU_M,
			       V2_QPC_BYTE_24_MTU_S, attr->path_mtu);

	roce_set_field(qpc_mask->byte_24_mtu_tc, V2_QPC_BYTE_24_MTU_M,
		       V2_QPC_BYTE_24_MTU_S, 0);

	roce_set_field(context->byte_84_rq_ci_pi,
		       V2_QPC_BYTE_84_RQ_PRODUCER_IDX_M,
		       V2_QPC_BYTE_84_RQ_PRODUCER_IDX_S, hr_qp->rq.head);
	roce_set_field(qpc_mask->byte_84_rq_ci_pi,
		       V2_QPC_BYTE_84_RQ_PRODUCER_IDX_M,
		       V2_QPC_BYTE_84_RQ_PRODUCER_IDX_S, 0);

	roce_set_field(qpc_mask->byte_84_rq_ci_pi,
		       V2_QPC_BYTE_84_RQ_CONSUMER_IDX_M,
		       V2_QPC_BYTE_84_RQ_CONSUMER_IDX_S, 0);
	roce_set_bit(qpc_mask->byte_108_rx_reqepsn,
		     V2_QPC_BYTE_108_RX_REQ_PSN_ERR_S, 0);
	roce_set_field(qpc_mask->byte_96_rx_reqmsn, V2_QPC_BYTE_96_RX_REQ_MSN_M,
		       V2_QPC_BYTE_96_RX_REQ_MSN_S, 0);
	roce_set_field(qpc_mask->byte_108_rx_reqepsn,
		       V2_QPC_BYTE_108_RX_REQ_LAST_OPTYPE_M,
		       V2_QPC_BYTE_108_RX_REQ_LAST_OPTYPE_S, 0);

	context->rq_rnr_timer = 0;
	qpc_mask->rq_rnr_timer = 0;

	roce_set_field(context->byte_152_raq, V2_QPC_BYTE_152_RAQ_PSN_M,
		       V2_QPC_BYTE_152_RAQ_PSN_S, attr->rq_psn - 1);
	roce_set_field(qpc_mask->byte_152_raq, V2_QPC_BYTE_152_RAQ_PSN_M,
		       V2_QPC_BYTE_152_RAQ_PSN_S, 0);

	roce_set_field(qpc_mask->byte_132_trrl, V2_QPC_BYTE_132_TRRL_HEAD_MAX_M,
		       V2_QPC_BYTE_132_TRRL_HEAD_MAX_S, 0);
	roce_set_field(qpc_mask->byte_132_trrl, V2_QPC_BYTE_132_TRRL_TAIL_MAX_M,
		       V2_QPC_BYTE_132_TRRL_TAIL_MAX_S, 0);

	roce_set_field(context->byte_168_irrl_idx,
		       V2_QPC_BYTE_168_LP_SGEN_INI_M,
		       V2_QPC_BYTE_168_LP_SGEN_INI_S, 3);
	roce_set_field(qpc_mask->byte_168_irrl_idx,
		       V2_QPC_BYTE_168_LP_SGEN_INI_M,
		       V2_QPC_BYTE_168_LP_SGEN_INI_S, 0);

	return 0;
}