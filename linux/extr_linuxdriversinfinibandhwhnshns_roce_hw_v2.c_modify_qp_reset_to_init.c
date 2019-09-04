#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct ib_qp_attr {int /*<<< orphan*/  pkey_index; int /*<<< orphan*/  qp_access_flags; scalar_t__ qkey; } ;
struct ib_qp {scalar_t__ qp_type; int /*<<< orphan*/  send_cq; scalar_t__ srq; int /*<<< orphan*/  recv_cq; int /*<<< orphan*/  pd; int /*<<< orphan*/  device; } ;
struct hns_roce_v2_qp_context {int rq_db_record_addr; int /*<<< orphan*/  byte_256_sqflush_rqcqe; int /*<<< orphan*/  byte_252_err_txcqn; int /*<<< orphan*/  byte_248_ack_psn; int /*<<< orphan*/  byte_240_irrl_tail; scalar_t__ irrl_cur_sge_offset; int /*<<< orphan*/  byte_232_irrl_sge; int /*<<< orphan*/  byte_220_retry_psn_msn; scalar_t__ sq_timer; int /*<<< orphan*/  byte_212_lsn; int /*<<< orphan*/  byte_208_irrl; int /*<<< orphan*/  byte_200_sq_max; int /*<<< orphan*/  byte_196_sq_psn; int /*<<< orphan*/  byte_192_ext_sge; scalar_t__ cur_sge_offset; int /*<<< orphan*/  byte_184_irrl_idx; int /*<<< orphan*/  byte_176_msg_pktn; int /*<<< orphan*/  byte_172_sq_psn; int /*<<< orphan*/  byte_168_irrl_idx; int /*<<< orphan*/  byte_160_sq_ci_pi; int /*<<< orphan*/  byte_156_raq; int /*<<< orphan*/  byte_152_raq; int /*<<< orphan*/  byte_148_raq; int /*<<< orphan*/  byte_144_raq; int /*<<< orphan*/  byte_140_raq; int /*<<< orphan*/  byte_132_trrl; scalar_t__ rx_va; scalar_t__ rx_rkey_pkt_info; scalar_t__ rx_msg_len; scalar_t__ rq_rnr_timer; int /*<<< orphan*/  byte_108_rx_reqepsn; int /*<<< orphan*/  byte_104_rq_sge; int /*<<< orphan*/  byte_96_rx_reqmsn; int /*<<< orphan*/  byte_92_srq_info; int /*<<< orphan*/  byte_84_rq_ci_pi; int /*<<< orphan*/  byte_76_srqn_op_en; int /*<<< orphan*/  byte_80_rnr_rx_cqn; int /*<<< orphan*/  byte_68_rq_db; scalar_t__ qkey_xrcd; int /*<<< orphan*/  byte_28_at_fl; int /*<<< orphan*/  byte_60_qpst_mapid; int /*<<< orphan*/  byte_56_dqpn_err; int /*<<< orphan*/  byte_24_mtu_tc; int /*<<< orphan*/  byte_20_smac_sgid_idx; int /*<<< orphan*/  byte_16_buf_ba_pg_sz; int /*<<< orphan*/  byte_4_sqpn_tst; } ;
struct TYPE_15__ {int max_gs; scalar_t__ wqe_cnt; } ;
struct TYPE_13__ {int dma; } ;
struct TYPE_12__ {unsigned int max_gs; scalar_t__ wqe_cnt; } ;
struct TYPE_11__ {scalar_t__ sge_cnt; } ;
struct TYPE_10__ {int /*<<< orphan*/  qp_type; } ;
struct hns_roce_qp {int qpn; int /*<<< orphan*/  pkey_index; int /*<<< orphan*/  access_flags; TYPE_6__ sq; TYPE_4__ rdb; scalar_t__ rdb_en; scalar_t__ qkey; TYPE_3__ rq; TYPE_2__ sge; TYPE_1__ ibqp; } ;
struct TYPE_14__ {int flags; } ;
struct hns_roce_dev {TYPE_5__ caps; } ;
struct TYPE_18__ {int cqn; } ;
struct TYPE_17__ {int pdn; } ;
struct TYPE_16__ {int srqn; } ;

/* Variables and functions */
 int HNS_ROCE_CAP_FLAG_RQ_INLINE ; 
 scalar_t__ IB_QPT_GSI ; 
 int IB_QP_QKEY ; 
 int /*<<< orphan*/  V2_QPC_BYTE_104_RQ_CUR_WQE_SGE_NUM_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_104_RQ_CUR_WQE_SGE_NUM_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_108_RX_REQ_LAST_OPTYPE_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_108_RX_REQ_LAST_OPTYPE_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_108_RX_REQ_PSN_ERR_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_108_RX_REQ_RNR_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_132_TRRL_HEAD_MAX_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_132_TRRL_HEAD_MAX_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_132_TRRL_TAIL_MAX_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_132_TRRL_TAIL_MAX_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_140_RAQ_TRRL_HEAD_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_140_RAQ_TRRL_HEAD_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_140_RAQ_TRRL_TAIL_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_140_RAQ_TRRL_TAIL_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_140_RSVD_RAQ_MAP_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_144_RAQ_CREDIT_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_144_RAQ_CREDIT_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_144_RAQ_RTY_INI_IND_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_144_RAQ_RTY_INI_PSN_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_144_RAQ_RTY_INI_PSN_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_144_RESP_RTY_FLG_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_148_RAQ_SYNDROME_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_148_RAQ_SYNDROME_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_148_RQ_MSN_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_148_RQ_MSN_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_152_RAQ_PSN_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_152_RAQ_PSN_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_152_RAQ_TRRL_RTY_HEAD_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_152_RAQ_TRRL_RTY_HEAD_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_156_RAQ_USE_PKTN_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_156_RAQ_USE_PKTN_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_160_SQ_CONSUMER_IDX_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_160_SQ_CONSUMER_IDX_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_160_SQ_PRODUCER_IDX_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_160_SQ_PRODUCER_IDX_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_168_IRRL_IDX_LSB_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_168_IRRL_IDX_LSB_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_168_MSG_RTY_LP_FLG_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_168_SQ_INVLD_FLG_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_168_SQ_SHIFT_BAK_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_168_SQ_SHIFT_BAK_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_16_PD_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_16_PD_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_172_ACK_REQ_FREQ_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_172_ACK_REQ_FREQ_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_172_MSG_RNR_FLG_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_176_IRRL_HEAD_PRE_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_176_IRRL_HEAD_PRE_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_176_MSG_USE_PKTN_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_176_MSG_USE_PKTN_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_184_IRRL_IDX_MSB_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_184_IRRL_IDX_MSB_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_192_CUR_SGE_IDX_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_192_CUR_SGE_IDX_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_192_EXT_SGE_NUM_LEFT_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_192_EXT_SGE_NUM_LEFT_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_196_IRRL_HEAD_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_196_IRRL_HEAD_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_200_LCL_OPERATED_CNT_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_200_LCL_OPERATED_CNT_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_200_SQ_MAX_IDX_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_200_SQ_MAX_IDX_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_208_PKT_RNR_FLG_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_208_PKT_RTY_FLG_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_20_RQWS_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_20_RQWS_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_20_RQ_SHIFT_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_20_RQ_SHIFT_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_20_SQ_SHIFT_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_20_SQ_SHIFT_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_212_CHECK_FLG_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_212_CHECK_FLG_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_220_RETRY_MSG_MSN_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_220_RETRY_MSG_MSN_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_232_IRRL_SGE_IDX_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_232_IRRL_SGE_IDX_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_240_IRRL_TAIL_RD_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_240_IRRL_TAIL_RD_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_240_IRRL_TAIL_REAL_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_240_IRRL_TAIL_REAL_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_240_RX_ACK_MSN_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_240_RX_ACK_MSN_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_248_ACK_LAST_OPTYPE_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_248_ACK_LAST_OPTYPE_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_248_ACK_PSN_ERR_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_248_CQ_ERR_IND_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_248_IRRL_PSN_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_248_IRRL_PSN_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_248_IRRL_PSN_VLD_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_248_RNR_RETRY_FLAG_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_24_VLAN_ID_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_24_VLAN_ID_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_252_ERR_TYPE_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_252_ERR_TYPE_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_252_TX_CQN_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_252_TX_CQN_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_256_RQ_CQE_IDX_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_256_RQ_CQE_IDX_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_256_SQ_FLUSH_IDX_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_256_SQ_FLUSH_IDX_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_28_CE_FLAG_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_28_CNP_TX_FLAG_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_4_SGE_SHIFT_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_4_SGE_SHIFT_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_4_SQPN_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_4_SQPN_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_4_TST_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_4_TST_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_56_RQ_RX_ERR_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_56_RQ_TX_ERR_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_56_SQ_RX_ERR_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_56_SQ_TX_ERR_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_60_EXT_MAP_IND_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_60_INNER_MAP_IND_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_60_MAPID_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_60_MAPID_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_60_RQ_MAP_IND_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_60_SQ_EXT_IND_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_60_SQ_MAP_IND_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_60_SQ_RLS_IND_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_68_RQ_DB_RECORD_ADDR_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_68_RQ_DB_RECORD_ADDR_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_68_RQ_RECORD_EN_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_76_RQIE_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_76_SRQN_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_76_SRQN_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_76_SRQ_EN_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_80_RX_CQN_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_80_RX_CQN_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_84_RQ_CONSUMER_IDX_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_84_RQ_CONSUMER_IDX_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_84_RQ_PRODUCER_IDX_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_84_RQ_PRODUCER_IDX_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_92_SRQ_INFO_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_92_SRQ_INFO_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_96_RX_REQ_MSN_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_96_RX_REQ_MSN_S ; 
 int ilog2 (unsigned int) ; 
 int /*<<< orphan*/  roce_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  roce_set_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_9__* to_hr_cq (int /*<<< orphan*/ ) ; 
 struct hns_roce_dev* to_hr_dev (int /*<<< orphan*/ ) ; 
 TYPE_8__* to_hr_pd (int /*<<< orphan*/ ) ; 
 struct hns_roce_qp* to_hr_qp (struct ib_qp*) ; 
 int to_hr_qp_type (int /*<<< orphan*/ ) ; 
 TYPE_7__* to_hr_srq (scalar_t__) ; 

__attribute__((used)) static void modify_qp_reset_to_init(struct ib_qp *ibqp,
				    const struct ib_qp_attr *attr,
				    int attr_mask,
				    struct hns_roce_v2_qp_context *context,
				    struct hns_roce_v2_qp_context *qpc_mask)
{
	struct hns_roce_dev *hr_dev = to_hr_dev(ibqp->device);
	struct hns_roce_qp *hr_qp = to_hr_qp(ibqp);

	/*
	 * In v2 engine, software pass context and context mask to hardware
	 * when modifying qp. If software need modify some fields in context,
	 * we should set all bits of the relevant fields in context mask to
	 * 0 at the same time, else set them to 0x1.
	 */
	roce_set_field(context->byte_4_sqpn_tst, V2_QPC_BYTE_4_TST_M,
		       V2_QPC_BYTE_4_TST_S, to_hr_qp_type(hr_qp->ibqp.qp_type));
	roce_set_field(qpc_mask->byte_4_sqpn_tst, V2_QPC_BYTE_4_TST_M,
		       V2_QPC_BYTE_4_TST_S, 0);

	if (ibqp->qp_type == IB_QPT_GSI)
		roce_set_field(context->byte_4_sqpn_tst,
			       V2_QPC_BYTE_4_SGE_SHIFT_M,
			       V2_QPC_BYTE_4_SGE_SHIFT_S,
			       ilog2((unsigned int)hr_qp->sge.sge_cnt));
	else
		roce_set_field(context->byte_4_sqpn_tst,
			       V2_QPC_BYTE_4_SGE_SHIFT_M,
			       V2_QPC_BYTE_4_SGE_SHIFT_S,
			       hr_qp->sq.max_gs > 2 ?
			       ilog2((unsigned int)hr_qp->sge.sge_cnt) : 0);

	roce_set_field(qpc_mask->byte_4_sqpn_tst, V2_QPC_BYTE_4_SGE_SHIFT_M,
		       V2_QPC_BYTE_4_SGE_SHIFT_S, 0);

	roce_set_field(context->byte_4_sqpn_tst, V2_QPC_BYTE_4_SQPN_M,
		       V2_QPC_BYTE_4_SQPN_S, hr_qp->qpn);
	roce_set_field(qpc_mask->byte_4_sqpn_tst, V2_QPC_BYTE_4_SQPN_M,
		       V2_QPC_BYTE_4_SQPN_S, 0);

	roce_set_field(context->byte_16_buf_ba_pg_sz, V2_QPC_BYTE_16_PD_M,
		       V2_QPC_BYTE_16_PD_S, to_hr_pd(ibqp->pd)->pdn);
	roce_set_field(qpc_mask->byte_16_buf_ba_pg_sz, V2_QPC_BYTE_16_PD_M,
		       V2_QPC_BYTE_16_PD_S, 0);

	roce_set_field(context->byte_20_smac_sgid_idx, V2_QPC_BYTE_20_RQWS_M,
		       V2_QPC_BYTE_20_RQWS_S, ilog2(hr_qp->rq.max_gs));
	roce_set_field(qpc_mask->byte_20_smac_sgid_idx, V2_QPC_BYTE_20_RQWS_M,
		       V2_QPC_BYTE_20_RQWS_S, 0);

	roce_set_field(context->byte_20_smac_sgid_idx,
		       V2_QPC_BYTE_20_SQ_SHIFT_M, V2_QPC_BYTE_20_SQ_SHIFT_S,
		       ilog2((unsigned int)hr_qp->sq.wqe_cnt));
	roce_set_field(qpc_mask->byte_20_smac_sgid_idx,
		       V2_QPC_BYTE_20_SQ_SHIFT_M, V2_QPC_BYTE_20_SQ_SHIFT_S, 0);

	roce_set_field(context->byte_20_smac_sgid_idx,
		       V2_QPC_BYTE_20_RQ_SHIFT_M, V2_QPC_BYTE_20_RQ_SHIFT_S,
		       ilog2((unsigned int)hr_qp->rq.wqe_cnt));
	roce_set_field(qpc_mask->byte_20_smac_sgid_idx,
		       V2_QPC_BYTE_20_RQ_SHIFT_M, V2_QPC_BYTE_20_RQ_SHIFT_S, 0);

	/* No VLAN need to set 0xFFF */
	roce_set_field(context->byte_24_mtu_tc, V2_QPC_BYTE_24_VLAN_ID_M,
		       V2_QPC_BYTE_24_VLAN_ID_S, 0xfff);
	roce_set_field(qpc_mask->byte_24_mtu_tc, V2_QPC_BYTE_24_VLAN_ID_M,
		       V2_QPC_BYTE_24_VLAN_ID_S, 0);

	/*
	 * Set some fields in context to zero, Because the default values
	 * of all fields in context are zero, we need not set them to 0 again.
	 * but we should set the relevant fields of context mask to 0.
	 */
	roce_set_bit(qpc_mask->byte_56_dqpn_err, V2_QPC_BYTE_56_SQ_TX_ERR_S, 0);
	roce_set_bit(qpc_mask->byte_56_dqpn_err, V2_QPC_BYTE_56_SQ_RX_ERR_S, 0);
	roce_set_bit(qpc_mask->byte_56_dqpn_err, V2_QPC_BYTE_56_RQ_TX_ERR_S, 0);
	roce_set_bit(qpc_mask->byte_56_dqpn_err, V2_QPC_BYTE_56_RQ_RX_ERR_S, 0);

	roce_set_field(qpc_mask->byte_60_qpst_mapid, V2_QPC_BYTE_60_MAPID_M,
		       V2_QPC_BYTE_60_MAPID_S, 0);

	roce_set_bit(qpc_mask->byte_60_qpst_mapid,
		     V2_QPC_BYTE_60_INNER_MAP_IND_S, 0);
	roce_set_bit(qpc_mask->byte_60_qpst_mapid, V2_QPC_BYTE_60_SQ_MAP_IND_S,
		     0);
	roce_set_bit(qpc_mask->byte_60_qpst_mapid, V2_QPC_BYTE_60_RQ_MAP_IND_S,
		     0);
	roce_set_bit(qpc_mask->byte_60_qpst_mapid, V2_QPC_BYTE_60_EXT_MAP_IND_S,
		     0);
	roce_set_bit(qpc_mask->byte_60_qpst_mapid, V2_QPC_BYTE_60_SQ_RLS_IND_S,
		     0);
	roce_set_bit(qpc_mask->byte_60_qpst_mapid, V2_QPC_BYTE_60_SQ_EXT_IND_S,
		     0);
	roce_set_bit(qpc_mask->byte_28_at_fl, V2_QPC_BYTE_28_CNP_TX_FLAG_S, 0);
	roce_set_bit(qpc_mask->byte_28_at_fl, V2_QPC_BYTE_28_CE_FLAG_S, 0);

	if (attr_mask & IB_QP_QKEY) {
		context->qkey_xrcd = attr->qkey;
		qpc_mask->qkey_xrcd = 0;
		hr_qp->qkey = attr->qkey;
	}

	if (hr_qp->rdb_en) {
		roce_set_bit(context->byte_68_rq_db,
			     V2_QPC_BYTE_68_RQ_RECORD_EN_S, 1);
		roce_set_bit(qpc_mask->byte_68_rq_db,
			     V2_QPC_BYTE_68_RQ_RECORD_EN_S, 0);
	}

	roce_set_field(context->byte_68_rq_db,
		       V2_QPC_BYTE_68_RQ_DB_RECORD_ADDR_M,
		       V2_QPC_BYTE_68_RQ_DB_RECORD_ADDR_S,
		       ((u32)hr_qp->rdb.dma) >> 1);
	roce_set_field(qpc_mask->byte_68_rq_db,
		       V2_QPC_BYTE_68_RQ_DB_RECORD_ADDR_M,
		       V2_QPC_BYTE_68_RQ_DB_RECORD_ADDR_S, 0);
	context->rq_db_record_addr = hr_qp->rdb.dma >> 32;
	qpc_mask->rq_db_record_addr = 0;

	roce_set_bit(context->byte_76_srqn_op_en, V2_QPC_BYTE_76_RQIE_S,
		    (hr_dev->caps.flags & HNS_ROCE_CAP_FLAG_RQ_INLINE) ? 1 : 0);
	roce_set_bit(qpc_mask->byte_76_srqn_op_en, V2_QPC_BYTE_76_RQIE_S, 0);

	roce_set_field(context->byte_80_rnr_rx_cqn, V2_QPC_BYTE_80_RX_CQN_M,
		       V2_QPC_BYTE_80_RX_CQN_S, to_hr_cq(ibqp->recv_cq)->cqn);
	roce_set_field(qpc_mask->byte_80_rnr_rx_cqn, V2_QPC_BYTE_80_RX_CQN_M,
		       V2_QPC_BYTE_80_RX_CQN_S, 0);
	if (ibqp->srq) {
		roce_set_field(context->byte_76_srqn_op_en,
			       V2_QPC_BYTE_76_SRQN_M, V2_QPC_BYTE_76_SRQN_S,
			       to_hr_srq(ibqp->srq)->srqn);
		roce_set_field(qpc_mask->byte_76_srqn_op_en,
			       V2_QPC_BYTE_76_SRQN_M, V2_QPC_BYTE_76_SRQN_S, 0);
		roce_set_bit(context->byte_76_srqn_op_en,
			     V2_QPC_BYTE_76_SRQ_EN_S, 1);
		roce_set_bit(qpc_mask->byte_76_srqn_op_en,
			     V2_QPC_BYTE_76_SRQ_EN_S, 0);
	}

	roce_set_field(qpc_mask->byte_84_rq_ci_pi,
		       V2_QPC_BYTE_84_RQ_PRODUCER_IDX_M,
		       V2_QPC_BYTE_84_RQ_PRODUCER_IDX_S, 0);
	roce_set_field(qpc_mask->byte_84_rq_ci_pi,
		       V2_QPC_BYTE_84_RQ_CONSUMER_IDX_M,
		       V2_QPC_BYTE_84_RQ_CONSUMER_IDX_S, 0);

	roce_set_field(qpc_mask->byte_92_srq_info, V2_QPC_BYTE_92_SRQ_INFO_M,
		       V2_QPC_BYTE_92_SRQ_INFO_S, 0);

	roce_set_field(qpc_mask->byte_96_rx_reqmsn, V2_QPC_BYTE_96_RX_REQ_MSN_M,
		       V2_QPC_BYTE_96_RX_REQ_MSN_S, 0);

	roce_set_field(qpc_mask->byte_104_rq_sge,
		       V2_QPC_BYTE_104_RQ_CUR_WQE_SGE_NUM_M,
		       V2_QPC_BYTE_104_RQ_CUR_WQE_SGE_NUM_S, 0);

	roce_set_bit(qpc_mask->byte_108_rx_reqepsn,
		     V2_QPC_BYTE_108_RX_REQ_PSN_ERR_S, 0);
	roce_set_field(qpc_mask->byte_108_rx_reqepsn,
		       V2_QPC_BYTE_108_RX_REQ_LAST_OPTYPE_M,
		       V2_QPC_BYTE_108_RX_REQ_LAST_OPTYPE_S, 0);
	roce_set_bit(qpc_mask->byte_108_rx_reqepsn,
		     V2_QPC_BYTE_108_RX_REQ_RNR_S, 0);

	qpc_mask->rq_rnr_timer = 0;
	qpc_mask->rx_msg_len = 0;
	qpc_mask->rx_rkey_pkt_info = 0;
	qpc_mask->rx_va = 0;

	roce_set_field(qpc_mask->byte_132_trrl, V2_QPC_BYTE_132_TRRL_HEAD_MAX_M,
		       V2_QPC_BYTE_132_TRRL_HEAD_MAX_S, 0);
	roce_set_field(qpc_mask->byte_132_trrl, V2_QPC_BYTE_132_TRRL_TAIL_MAX_M,
		       V2_QPC_BYTE_132_TRRL_TAIL_MAX_S, 0);

	roce_set_bit(qpc_mask->byte_140_raq, V2_QPC_BYTE_140_RSVD_RAQ_MAP_S, 0);
	roce_set_field(qpc_mask->byte_140_raq, V2_QPC_BYTE_140_RAQ_TRRL_HEAD_M,
		       V2_QPC_BYTE_140_RAQ_TRRL_HEAD_S, 0);
	roce_set_field(qpc_mask->byte_140_raq, V2_QPC_BYTE_140_RAQ_TRRL_TAIL_M,
		       V2_QPC_BYTE_140_RAQ_TRRL_TAIL_S, 0);

	roce_set_field(qpc_mask->byte_144_raq,
		       V2_QPC_BYTE_144_RAQ_RTY_INI_PSN_M,
		       V2_QPC_BYTE_144_RAQ_RTY_INI_PSN_S, 0);
	roce_set_bit(qpc_mask->byte_144_raq, V2_QPC_BYTE_144_RAQ_RTY_INI_IND_S,
		     0);
	roce_set_field(qpc_mask->byte_144_raq, V2_QPC_BYTE_144_RAQ_CREDIT_M,
		       V2_QPC_BYTE_144_RAQ_CREDIT_S, 0);
	roce_set_bit(qpc_mask->byte_144_raq, V2_QPC_BYTE_144_RESP_RTY_FLG_S, 0);

	roce_set_field(qpc_mask->byte_148_raq, V2_QPC_BYTE_148_RQ_MSN_M,
		       V2_QPC_BYTE_148_RQ_MSN_S, 0);
	roce_set_field(qpc_mask->byte_148_raq, V2_QPC_BYTE_148_RAQ_SYNDROME_M,
		       V2_QPC_BYTE_148_RAQ_SYNDROME_S, 0);

	roce_set_field(qpc_mask->byte_152_raq, V2_QPC_BYTE_152_RAQ_PSN_M,
		       V2_QPC_BYTE_152_RAQ_PSN_S, 0);
	roce_set_field(qpc_mask->byte_152_raq,
		       V2_QPC_BYTE_152_RAQ_TRRL_RTY_HEAD_M,
		       V2_QPC_BYTE_152_RAQ_TRRL_RTY_HEAD_S, 0);

	roce_set_field(qpc_mask->byte_156_raq, V2_QPC_BYTE_156_RAQ_USE_PKTN_M,
		       V2_QPC_BYTE_156_RAQ_USE_PKTN_S, 0);

	roce_set_field(qpc_mask->byte_160_sq_ci_pi,
		       V2_QPC_BYTE_160_SQ_PRODUCER_IDX_M,
		       V2_QPC_BYTE_160_SQ_PRODUCER_IDX_S, 0);
	roce_set_field(qpc_mask->byte_160_sq_ci_pi,
		       V2_QPC_BYTE_160_SQ_CONSUMER_IDX_M,
		       V2_QPC_BYTE_160_SQ_CONSUMER_IDX_S, 0);

	roce_set_field(context->byte_168_irrl_idx,
		       V2_QPC_BYTE_168_SQ_SHIFT_BAK_M,
		       V2_QPC_BYTE_168_SQ_SHIFT_BAK_S,
		       ilog2((unsigned int)hr_qp->sq.wqe_cnt));
	roce_set_field(qpc_mask->byte_168_irrl_idx,
		       V2_QPC_BYTE_168_SQ_SHIFT_BAK_M,
		       V2_QPC_BYTE_168_SQ_SHIFT_BAK_S, 0);

	roce_set_bit(qpc_mask->byte_168_irrl_idx,
		     V2_QPC_BYTE_168_MSG_RTY_LP_FLG_S, 0);
	roce_set_bit(qpc_mask->byte_168_irrl_idx,
		     V2_QPC_BYTE_168_SQ_INVLD_FLG_S, 0);
	roce_set_field(qpc_mask->byte_168_irrl_idx,
		       V2_QPC_BYTE_168_IRRL_IDX_LSB_M,
		       V2_QPC_BYTE_168_IRRL_IDX_LSB_S, 0);

	roce_set_field(context->byte_172_sq_psn, V2_QPC_BYTE_172_ACK_REQ_FREQ_M,
		       V2_QPC_BYTE_172_ACK_REQ_FREQ_S, 4);
	roce_set_field(qpc_mask->byte_172_sq_psn,
		       V2_QPC_BYTE_172_ACK_REQ_FREQ_M,
		       V2_QPC_BYTE_172_ACK_REQ_FREQ_S, 0);

	roce_set_bit(qpc_mask->byte_172_sq_psn, V2_QPC_BYTE_172_MSG_RNR_FLG_S,
		     0);

	roce_set_field(qpc_mask->byte_176_msg_pktn,
		       V2_QPC_BYTE_176_MSG_USE_PKTN_M,
		       V2_QPC_BYTE_176_MSG_USE_PKTN_S, 0);
	roce_set_field(qpc_mask->byte_176_msg_pktn,
		       V2_QPC_BYTE_176_IRRL_HEAD_PRE_M,
		       V2_QPC_BYTE_176_IRRL_HEAD_PRE_S, 0);

	roce_set_field(qpc_mask->byte_184_irrl_idx,
		       V2_QPC_BYTE_184_IRRL_IDX_MSB_M,
		       V2_QPC_BYTE_184_IRRL_IDX_MSB_S, 0);

	qpc_mask->cur_sge_offset = 0;

	roce_set_field(qpc_mask->byte_192_ext_sge,
		       V2_QPC_BYTE_192_CUR_SGE_IDX_M,
		       V2_QPC_BYTE_192_CUR_SGE_IDX_S, 0);
	roce_set_field(qpc_mask->byte_192_ext_sge,
		       V2_QPC_BYTE_192_EXT_SGE_NUM_LEFT_M,
		       V2_QPC_BYTE_192_EXT_SGE_NUM_LEFT_S, 0);

	roce_set_field(qpc_mask->byte_196_sq_psn, V2_QPC_BYTE_196_IRRL_HEAD_M,
		       V2_QPC_BYTE_196_IRRL_HEAD_S, 0);

	roce_set_field(qpc_mask->byte_200_sq_max, V2_QPC_BYTE_200_SQ_MAX_IDX_M,
		       V2_QPC_BYTE_200_SQ_MAX_IDX_S, 0);
	roce_set_field(qpc_mask->byte_200_sq_max,
		       V2_QPC_BYTE_200_LCL_OPERATED_CNT_M,
		       V2_QPC_BYTE_200_LCL_OPERATED_CNT_S, 0);

	roce_set_bit(qpc_mask->byte_208_irrl, V2_QPC_BYTE_208_PKT_RNR_FLG_S, 0);
	roce_set_bit(qpc_mask->byte_208_irrl, V2_QPC_BYTE_208_PKT_RTY_FLG_S, 0);

	roce_set_field(qpc_mask->byte_212_lsn, V2_QPC_BYTE_212_CHECK_FLG_M,
		       V2_QPC_BYTE_212_CHECK_FLG_S, 0);

	qpc_mask->sq_timer = 0;

	roce_set_field(qpc_mask->byte_220_retry_psn_msn,
		       V2_QPC_BYTE_220_RETRY_MSG_MSN_M,
		       V2_QPC_BYTE_220_RETRY_MSG_MSN_S, 0);
	roce_set_field(qpc_mask->byte_232_irrl_sge,
		       V2_QPC_BYTE_232_IRRL_SGE_IDX_M,
		       V2_QPC_BYTE_232_IRRL_SGE_IDX_S, 0);

	qpc_mask->irrl_cur_sge_offset = 0;

	roce_set_field(qpc_mask->byte_240_irrl_tail,
		       V2_QPC_BYTE_240_IRRL_TAIL_REAL_M,
		       V2_QPC_BYTE_240_IRRL_TAIL_REAL_S, 0);
	roce_set_field(qpc_mask->byte_240_irrl_tail,
		       V2_QPC_BYTE_240_IRRL_TAIL_RD_M,
		       V2_QPC_BYTE_240_IRRL_TAIL_RD_S, 0);
	roce_set_field(qpc_mask->byte_240_irrl_tail,
		       V2_QPC_BYTE_240_RX_ACK_MSN_M,
		       V2_QPC_BYTE_240_RX_ACK_MSN_S, 0);

	roce_set_field(qpc_mask->byte_248_ack_psn, V2_QPC_BYTE_248_IRRL_PSN_M,
		       V2_QPC_BYTE_248_IRRL_PSN_S, 0);
	roce_set_bit(qpc_mask->byte_248_ack_psn, V2_QPC_BYTE_248_ACK_PSN_ERR_S,
		     0);
	roce_set_field(qpc_mask->byte_248_ack_psn,
		       V2_QPC_BYTE_248_ACK_LAST_OPTYPE_M,
		       V2_QPC_BYTE_248_ACK_LAST_OPTYPE_S, 0);
	roce_set_bit(qpc_mask->byte_248_ack_psn, V2_QPC_BYTE_248_IRRL_PSN_VLD_S,
		     0);
	roce_set_bit(qpc_mask->byte_248_ack_psn,
		     V2_QPC_BYTE_248_RNR_RETRY_FLAG_S, 0);
	roce_set_bit(qpc_mask->byte_248_ack_psn, V2_QPC_BYTE_248_CQ_ERR_IND_S,
		     0);

	hr_qp->access_flags = attr->qp_access_flags;
	hr_qp->pkey_index = attr->pkey_index;
	roce_set_field(context->byte_252_err_txcqn, V2_QPC_BYTE_252_TX_CQN_M,
		       V2_QPC_BYTE_252_TX_CQN_S, to_hr_cq(ibqp->send_cq)->cqn);
	roce_set_field(qpc_mask->byte_252_err_txcqn, V2_QPC_BYTE_252_TX_CQN_M,
		       V2_QPC_BYTE_252_TX_CQN_S, 0);

	roce_set_field(qpc_mask->byte_252_err_txcqn, V2_QPC_BYTE_252_ERR_TYPE_M,
		       V2_QPC_BYTE_252_ERR_TYPE_S, 0);

	roce_set_field(qpc_mask->byte_256_sqflush_rqcqe,
		       V2_QPC_BYTE_256_RQ_CQE_IDX_M,
		       V2_QPC_BYTE_256_RQ_CQE_IDX_S, 0);
	roce_set_field(qpc_mask->byte_256_sqflush_rqcqe,
		       V2_QPC_BYTE_256_SQ_FLUSH_IDX_M,
		       V2_QPC_BYTE_256_SQ_FLUSH_IDX_S, 0);
}