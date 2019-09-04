#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  size_t u32 ;
struct ib_qp_attr {int retry_cnt; int sq_psn; int rnr_retry; int timeout; scalar_t__ max_rd_atomic; } ;
struct ib_qp {scalar_t__ qp_type; int /*<<< orphan*/  device; } ;
struct hns_roce_v2_qp_context {size_t sq_cur_blk_addr; size_t sq_cur_sge_blk_addr; size_t rx_sq_cur_blk_addr; int /*<<< orphan*/  byte_208_irrl; int /*<<< orphan*/  byte_196_sq_psn; int /*<<< orphan*/  byte_172_sq_psn; int /*<<< orphan*/  byte_28_at_fl; int /*<<< orphan*/  byte_212_lsn; int /*<<< orphan*/  byte_244_rnr_rxack; int /*<<< orphan*/  byte_248_ack_psn; int /*<<< orphan*/  byte_220_retry_psn_msn; int /*<<< orphan*/  byte_224_retry_msg; int /*<<< orphan*/  byte_240_irrl_tail; int /*<<< orphan*/  byte_232_irrl_sge; int /*<<< orphan*/  byte_184_irrl_idx; int /*<<< orphan*/  byte_168_irrl_idx; int /*<<< orphan*/  byte_60_qpst_mapid; } ;
struct TYPE_10__ {size_t offset; } ;
struct TYPE_9__ {int max_gs; } ;
struct TYPE_7__ {int /*<<< orphan*/  first_seg; } ;
struct hns_roce_qp {TYPE_5__ sge; TYPE_4__ sq; TYPE_2__ mtt; } ;
struct TYPE_8__ {int mtt_buf_pg_sz; } ;
struct TYPE_6__ {int /*<<< orphan*/  mtt_table; } ;
struct hns_roce_dev {TYPE_3__ caps; TYPE_1__ mr_table; struct device* dev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IB_QPT_GSI ; 
 int IB_QP_ALT_PATH ; 
 int IB_QP_MAX_QP_RD_ATOMIC ; 
 int IB_QP_PATH_MIG_STATE ; 
 int IB_QP_TIMEOUT ; 
 int PAGE_ADDR_SHIFT ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  V2_QPC_BYTE_168_SQ_CUR_BLK_ADDR_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_168_SQ_CUR_BLK_ADDR_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_172_SQ_CUR_PSN_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_172_SQ_CUR_PSN_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_184_SQ_CUR_SGE_BLK_ADDR_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_184_SQ_CUR_SGE_BLK_ADDR_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_196_IRRL_HEAD_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_196_IRRL_HEAD_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_196_SQ_MAX_PSN_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_196_SQ_MAX_PSN_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_208_SR_MAX_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_208_SR_MAX_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_212_CHECK_FLG_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_212_CHECK_FLG_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_212_LSN_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_212_LSN_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_212_RETRY_CNT_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_212_RETRY_CNT_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_212_RETRY_NUM_INIT_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_212_RETRY_NUM_INIT_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_220_RETRY_MSG_MSN_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_220_RETRY_MSG_MSN_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_220_RETRY_MSG_PSN_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_220_RETRY_MSG_PSN_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_224_RETRY_MSG_FPKT_PSN_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_224_RETRY_MSG_FPKT_PSN_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_224_RETRY_MSG_PSN_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_224_RETRY_MSG_PSN_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_232_IRRL_SGE_IDX_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_232_IRRL_SGE_IDX_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_232_RX_SQ_CUR_BLK_ADDR_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_232_RX_SQ_CUR_BLK_ADDR_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_240_IRRL_TAIL_REAL_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_240_IRRL_TAIL_REAL_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_240_RX_ACK_MSN_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_240_RX_ACK_MSN_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_244_RNR_CNT_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_244_RNR_CNT_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_244_RNR_NUM_INIT_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_244_RNR_NUM_INIT_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_244_RX_ACK_EPSN_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_244_RX_ACK_EPSN_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_248_ACK_LAST_OPTYPE_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_248_ACK_LAST_OPTYPE_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_248_IRRL_PSN_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_248_IRRL_PSN_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_248_IRRL_PSN_VLD_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_248_RNR_RETRY_FLAG_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_28_AT_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_28_AT_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_60_RTY_NUM_INI_BAK_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_60_RTY_NUM_INI_BAK_S ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int fls (scalar_t__) ; 
 int* hns_roce_table_find (struct hns_roce_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  roce_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  roce_set_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct hns_roce_dev* to_hr_dev (int /*<<< orphan*/ ) ; 
 struct hns_roce_qp* to_hr_qp (struct ib_qp*) ; 

__attribute__((used)) static int modify_qp_rtr_to_rts(struct ib_qp *ibqp,
				const struct ib_qp_attr *attr, int attr_mask,
				struct hns_roce_v2_qp_context *context,
				struct hns_roce_v2_qp_context *qpc_mask)
{
	struct hns_roce_dev *hr_dev = to_hr_dev(ibqp->device);
	struct hns_roce_qp *hr_qp = to_hr_qp(ibqp);
	struct device *dev = hr_dev->dev;
	dma_addr_t dma_handle;
	u32 page_size;
	u64 *mtts;

	/* Search qp buf's mtts */
	mtts = hns_roce_table_find(hr_dev, &hr_dev->mr_table.mtt_table,
				   hr_qp->mtt.first_seg, &dma_handle);
	if (!mtts) {
		dev_err(dev, "qp buf pa find failed\n");
		return -EINVAL;
	}

	/* Not support alternate path and path migration */
	if ((attr_mask & IB_QP_ALT_PATH) ||
	    (attr_mask & IB_QP_PATH_MIG_STATE)) {
		dev_err(dev, "RTR2RTS attr_mask (0x%x)error\n", attr_mask);
		return -EINVAL;
	}

	/*
	 * In v2 engine, software pass context and context mask to hardware
	 * when modifying qp. If software need modify some fields in context,
	 * we should set all bits of the relevant fields in context mask to
	 * 0 at the same time, else set them to 0x1.
	 */
	roce_set_field(context->byte_60_qpst_mapid,
		       V2_QPC_BYTE_60_RTY_NUM_INI_BAK_M,
		       V2_QPC_BYTE_60_RTY_NUM_INI_BAK_S, attr->retry_cnt);
	roce_set_field(qpc_mask->byte_60_qpst_mapid,
		       V2_QPC_BYTE_60_RTY_NUM_INI_BAK_M,
		       V2_QPC_BYTE_60_RTY_NUM_INI_BAK_S, 0);

	context->sq_cur_blk_addr = (u32)(mtts[0] >> PAGE_ADDR_SHIFT);
	roce_set_field(context->byte_168_irrl_idx,
		       V2_QPC_BYTE_168_SQ_CUR_BLK_ADDR_M,
		       V2_QPC_BYTE_168_SQ_CUR_BLK_ADDR_S,
		       mtts[0] >> (32 + PAGE_ADDR_SHIFT));
	qpc_mask->sq_cur_blk_addr = 0;
	roce_set_field(qpc_mask->byte_168_irrl_idx,
		       V2_QPC_BYTE_168_SQ_CUR_BLK_ADDR_M,
		       V2_QPC_BYTE_168_SQ_CUR_BLK_ADDR_S, 0);

	page_size = 1 << (hr_dev->caps.mtt_buf_pg_sz + PAGE_SHIFT);
	context->sq_cur_sge_blk_addr =
		       ((ibqp->qp_type == IB_QPT_GSI) || hr_qp->sq.max_gs > 2) ?
				      ((u32)(mtts[hr_qp->sge.offset / page_size]
				      >> PAGE_ADDR_SHIFT)) : 0;
	roce_set_field(context->byte_184_irrl_idx,
		       V2_QPC_BYTE_184_SQ_CUR_SGE_BLK_ADDR_M,
		       V2_QPC_BYTE_184_SQ_CUR_SGE_BLK_ADDR_S,
		       ((ibqp->qp_type == IB_QPT_GSI) || hr_qp->sq.max_gs > 2) ?
		       (mtts[hr_qp->sge.offset / page_size] >>
		       (32 + PAGE_ADDR_SHIFT)) : 0);
	qpc_mask->sq_cur_sge_blk_addr = 0;
	roce_set_field(qpc_mask->byte_184_irrl_idx,
		       V2_QPC_BYTE_184_SQ_CUR_SGE_BLK_ADDR_M,
		       V2_QPC_BYTE_184_SQ_CUR_SGE_BLK_ADDR_S, 0);

	context->rx_sq_cur_blk_addr = (u32)(mtts[0] >> PAGE_ADDR_SHIFT);
	roce_set_field(context->byte_232_irrl_sge,
		       V2_QPC_BYTE_232_RX_SQ_CUR_BLK_ADDR_M,
		       V2_QPC_BYTE_232_RX_SQ_CUR_BLK_ADDR_S,
		       mtts[0] >> (32 + PAGE_ADDR_SHIFT));
	qpc_mask->rx_sq_cur_blk_addr = 0;
	roce_set_field(qpc_mask->byte_232_irrl_sge,
		       V2_QPC_BYTE_232_RX_SQ_CUR_BLK_ADDR_M,
		       V2_QPC_BYTE_232_RX_SQ_CUR_BLK_ADDR_S, 0);

	/*
	 * Set some fields in context to zero, Because the default values
	 * of all fields in context are zero, we need not set them to 0 again.
	 * but we should set the relevant fields of context mask to 0.
	 */
	roce_set_field(qpc_mask->byte_232_irrl_sge,
		       V2_QPC_BYTE_232_IRRL_SGE_IDX_M,
		       V2_QPC_BYTE_232_IRRL_SGE_IDX_S, 0);

	roce_set_field(qpc_mask->byte_240_irrl_tail,
		       V2_QPC_BYTE_240_RX_ACK_MSN_M,
		       V2_QPC_BYTE_240_RX_ACK_MSN_S, 0);

	roce_set_field(context->byte_244_rnr_rxack,
		       V2_QPC_BYTE_244_RX_ACK_EPSN_M,
		       V2_QPC_BYTE_244_RX_ACK_EPSN_S, attr->sq_psn);
	roce_set_field(qpc_mask->byte_244_rnr_rxack,
		       V2_QPC_BYTE_244_RX_ACK_EPSN_M,
		       V2_QPC_BYTE_244_RX_ACK_EPSN_S, 0);

	roce_set_field(qpc_mask->byte_248_ack_psn,
		       V2_QPC_BYTE_248_ACK_LAST_OPTYPE_M,
		       V2_QPC_BYTE_248_ACK_LAST_OPTYPE_S, 0);
	roce_set_bit(qpc_mask->byte_248_ack_psn,
		     V2_QPC_BYTE_248_IRRL_PSN_VLD_S, 0);
	roce_set_field(qpc_mask->byte_248_ack_psn,
		       V2_QPC_BYTE_248_IRRL_PSN_M,
		       V2_QPC_BYTE_248_IRRL_PSN_S, 0);

	roce_set_field(qpc_mask->byte_240_irrl_tail,
		       V2_QPC_BYTE_240_IRRL_TAIL_REAL_M,
		       V2_QPC_BYTE_240_IRRL_TAIL_REAL_S, 0);

	roce_set_field(context->byte_220_retry_psn_msn,
		       V2_QPC_BYTE_220_RETRY_MSG_PSN_M,
		       V2_QPC_BYTE_220_RETRY_MSG_PSN_S, attr->sq_psn);
	roce_set_field(qpc_mask->byte_220_retry_psn_msn,
		       V2_QPC_BYTE_220_RETRY_MSG_PSN_M,
		       V2_QPC_BYTE_220_RETRY_MSG_PSN_S, 0);

	roce_set_field(context->byte_224_retry_msg,
		       V2_QPC_BYTE_224_RETRY_MSG_PSN_M,
		       V2_QPC_BYTE_224_RETRY_MSG_PSN_S, attr->sq_psn >> 16);
	roce_set_field(qpc_mask->byte_224_retry_msg,
		       V2_QPC_BYTE_224_RETRY_MSG_PSN_M,
		       V2_QPC_BYTE_224_RETRY_MSG_PSN_S, 0);

	roce_set_field(context->byte_224_retry_msg,
		       V2_QPC_BYTE_224_RETRY_MSG_FPKT_PSN_M,
		       V2_QPC_BYTE_224_RETRY_MSG_FPKT_PSN_S, attr->sq_psn);
	roce_set_field(qpc_mask->byte_224_retry_msg,
		       V2_QPC_BYTE_224_RETRY_MSG_FPKT_PSN_M,
		       V2_QPC_BYTE_224_RETRY_MSG_FPKT_PSN_S, 0);

	roce_set_field(qpc_mask->byte_220_retry_psn_msn,
		       V2_QPC_BYTE_220_RETRY_MSG_MSN_M,
		       V2_QPC_BYTE_220_RETRY_MSG_MSN_S, 0);

	roce_set_bit(qpc_mask->byte_248_ack_psn,
		     V2_QPC_BYTE_248_RNR_RETRY_FLAG_S, 0);

	roce_set_field(qpc_mask->byte_212_lsn, V2_QPC_BYTE_212_CHECK_FLG_M,
		       V2_QPC_BYTE_212_CHECK_FLG_S, 0);

	roce_set_field(context->byte_212_lsn, V2_QPC_BYTE_212_RETRY_CNT_M,
		       V2_QPC_BYTE_212_RETRY_CNT_S, attr->retry_cnt);
	roce_set_field(qpc_mask->byte_212_lsn, V2_QPC_BYTE_212_RETRY_CNT_M,
		       V2_QPC_BYTE_212_RETRY_CNT_S, 0);

	roce_set_field(context->byte_212_lsn, V2_QPC_BYTE_212_RETRY_NUM_INIT_M,
		       V2_QPC_BYTE_212_RETRY_NUM_INIT_S, attr->retry_cnt);
	roce_set_field(qpc_mask->byte_212_lsn, V2_QPC_BYTE_212_RETRY_NUM_INIT_M,
		       V2_QPC_BYTE_212_RETRY_NUM_INIT_S, 0);

	roce_set_field(context->byte_244_rnr_rxack,
		       V2_QPC_BYTE_244_RNR_NUM_INIT_M,
		       V2_QPC_BYTE_244_RNR_NUM_INIT_S, attr->rnr_retry);
	roce_set_field(qpc_mask->byte_244_rnr_rxack,
		       V2_QPC_BYTE_244_RNR_NUM_INIT_M,
		       V2_QPC_BYTE_244_RNR_NUM_INIT_S, 0);

	roce_set_field(context->byte_244_rnr_rxack, V2_QPC_BYTE_244_RNR_CNT_M,
		       V2_QPC_BYTE_244_RNR_CNT_S, attr->rnr_retry);
	roce_set_field(qpc_mask->byte_244_rnr_rxack, V2_QPC_BYTE_244_RNR_CNT_M,
		       V2_QPC_BYTE_244_RNR_CNT_S, 0);

	roce_set_field(context->byte_212_lsn, V2_QPC_BYTE_212_LSN_M,
		       V2_QPC_BYTE_212_LSN_S, 0x100);
	roce_set_field(qpc_mask->byte_212_lsn, V2_QPC_BYTE_212_LSN_M,
		       V2_QPC_BYTE_212_LSN_S, 0);

	if (attr_mask & IB_QP_TIMEOUT) {
		roce_set_field(context->byte_28_at_fl, V2_QPC_BYTE_28_AT_M,
			       V2_QPC_BYTE_28_AT_S, attr->timeout);
		roce_set_field(qpc_mask->byte_28_at_fl, V2_QPC_BYTE_28_AT_M,
			      V2_QPC_BYTE_28_AT_S, 0);
	}

	roce_set_field(context->byte_172_sq_psn, V2_QPC_BYTE_172_SQ_CUR_PSN_M,
		       V2_QPC_BYTE_172_SQ_CUR_PSN_S, attr->sq_psn);
	roce_set_field(qpc_mask->byte_172_sq_psn, V2_QPC_BYTE_172_SQ_CUR_PSN_M,
		       V2_QPC_BYTE_172_SQ_CUR_PSN_S, 0);

	roce_set_field(qpc_mask->byte_196_sq_psn, V2_QPC_BYTE_196_IRRL_HEAD_M,
		       V2_QPC_BYTE_196_IRRL_HEAD_S, 0);
	roce_set_field(context->byte_196_sq_psn, V2_QPC_BYTE_196_SQ_MAX_PSN_M,
		       V2_QPC_BYTE_196_SQ_MAX_PSN_S, attr->sq_psn);
	roce_set_field(qpc_mask->byte_196_sq_psn, V2_QPC_BYTE_196_SQ_MAX_PSN_M,
		       V2_QPC_BYTE_196_SQ_MAX_PSN_S, 0);

	if ((attr_mask & IB_QP_MAX_QP_RD_ATOMIC) && attr->max_rd_atomic) {
		roce_set_field(context->byte_208_irrl, V2_QPC_BYTE_208_SR_MAX_M,
			       V2_QPC_BYTE_208_SR_MAX_S,
			       fls(attr->max_rd_atomic - 1));
		roce_set_field(qpc_mask->byte_208_irrl,
			       V2_QPC_BYTE_208_SR_MAX_M,
			       V2_QPC_BYTE_208_SR_MAX_S, 0);
	}
	return 0;
}