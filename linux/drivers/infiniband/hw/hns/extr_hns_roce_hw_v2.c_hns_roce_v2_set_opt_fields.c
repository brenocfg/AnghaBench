#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ib_qp_attr {int timeout; int retry_cnt; int rnr_retry; int sq_psn; int min_rnr_timer; int rq_psn; int /*<<< orphan*/  qkey; scalar_t__ max_rd_atomic; scalar_t__ max_dest_rd_atomic; } ;
struct ib_qp {int /*<<< orphan*/  device; } ;
struct hns_roce_v2_qp_context {scalar_t__ qkey_xrcd; int /*<<< orphan*/  byte_152_raq; int /*<<< orphan*/  byte_108_rx_reqepsn; int /*<<< orphan*/  byte_80_rnr_rx_cqn; int /*<<< orphan*/  byte_208_irrl; int /*<<< orphan*/  byte_140_raq; int /*<<< orphan*/  byte_244_rnr_rxack; int /*<<< orphan*/  byte_224_retry_msg; int /*<<< orphan*/  byte_220_retry_psn_msn; int /*<<< orphan*/  byte_196_sq_psn; int /*<<< orphan*/  byte_172_sq_psn; int /*<<< orphan*/  byte_212_lsn; int /*<<< orphan*/  byte_28_at_fl; } ;
struct hns_roce_qp {int /*<<< orphan*/  qkey; } ;
struct hns_roce_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int IB_QP_ACCESS_FLAGS ; 
 int IB_QP_AV ; 
 int IB_QP_MAX_DEST_RD_ATOMIC ; 
 int IB_QP_MAX_QP_RD_ATOMIC ; 
 int IB_QP_MIN_RNR_TIMER ; 
 int IB_QP_QKEY ; 
 int IB_QP_RETRY_CNT ; 
 int IB_QP_RNR_RETRY ; 
 int IB_QP_RQ_PSN ; 
 int IB_QP_SQ_PSN ; 
 int IB_QP_TIMEOUT ; 
 int /*<<< orphan*/  V2_QPC_BYTE_108_RX_REQ_EPSN_M ; 
 int V2_QPC_BYTE_108_RX_REQ_EPSN_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_140_RR_MAX_M ; 
 int V2_QPC_BYTE_140_RR_MAX_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_152_RAQ_PSN_M ; 
 int V2_QPC_BYTE_152_RAQ_PSN_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_172_SQ_CUR_PSN_M ; 
 int V2_QPC_BYTE_172_SQ_CUR_PSN_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_196_SQ_MAX_PSN_M ; 
 int V2_QPC_BYTE_196_SQ_MAX_PSN_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_208_SR_MAX_M ; 
 int V2_QPC_BYTE_208_SR_MAX_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_212_RETRY_CNT_M ; 
 int V2_QPC_BYTE_212_RETRY_CNT_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_212_RETRY_NUM_INIT_M ; 
 int V2_QPC_BYTE_212_RETRY_NUM_INIT_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_220_RETRY_MSG_PSN_M ; 
 int V2_QPC_BYTE_220_RETRY_MSG_PSN_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_224_RETRY_MSG_FPKT_PSN_M ; 
 int V2_QPC_BYTE_224_RETRY_MSG_FPKT_PSN_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_224_RETRY_MSG_PSN_M ; 
 int V2_QPC_BYTE_224_RETRY_MSG_PSN_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_244_RNR_CNT_M ; 
 int V2_QPC_BYTE_244_RNR_CNT_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_244_RNR_NUM_INIT_M ; 
 int V2_QPC_BYTE_244_RNR_NUM_INIT_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_244_RX_ACK_EPSN_M ; 
 int V2_QPC_BYTE_244_RX_ACK_EPSN_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_28_AT_M ; 
 int V2_QPC_BYTE_28_AT_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_80_MIN_RNR_TIME_M ; 
 int V2_QPC_BYTE_80_MIN_RNR_TIME_S ; 
 scalar_t__ cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int fls (scalar_t__) ; 
 int hns_roce_v2_set_path (struct ib_qp*,struct ib_qp_attr const*,int,struct hns_roce_v2_qp_context*,struct hns_roce_v2_qp_context*) ; 
 int /*<<< orphan*/  roce_set_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  set_access_flags (struct hns_roce_qp*,struct hns_roce_v2_qp_context*,struct hns_roce_v2_qp_context*,struct ib_qp_attr const*,int) ; 
 struct hns_roce_dev* to_hr_dev (int /*<<< orphan*/ ) ; 
 struct hns_roce_qp* to_hr_qp (struct ib_qp*) ; 

__attribute__((used)) static int hns_roce_v2_set_opt_fields(struct ib_qp *ibqp,
				      const struct ib_qp_attr *attr,
				      int attr_mask,
				      struct hns_roce_v2_qp_context *context,
				      struct hns_roce_v2_qp_context *qpc_mask)
{
	struct hns_roce_dev *hr_dev = to_hr_dev(ibqp->device);
	struct hns_roce_qp *hr_qp = to_hr_qp(ibqp);
	int ret = 0;

	if (attr_mask & IB_QP_AV) {
		ret = hns_roce_v2_set_path(ibqp, attr, attr_mask, context,
					   qpc_mask);
		if (ret)
			return ret;
	}

	if (attr_mask & IB_QP_TIMEOUT) {
		if (attr->timeout < 31) {
			roce_set_field(context->byte_28_at_fl,
				       V2_QPC_BYTE_28_AT_M, V2_QPC_BYTE_28_AT_S,
				       attr->timeout);
			roce_set_field(qpc_mask->byte_28_at_fl,
				       V2_QPC_BYTE_28_AT_M, V2_QPC_BYTE_28_AT_S,
				       0);
		} else {
			dev_warn(hr_dev->dev,
				 "Local ACK timeout shall be 0 to 30.\n");
		}
	}

	if (attr_mask & IB_QP_RETRY_CNT) {
		roce_set_field(context->byte_212_lsn,
			       V2_QPC_BYTE_212_RETRY_NUM_INIT_M,
			       V2_QPC_BYTE_212_RETRY_NUM_INIT_S,
			       attr->retry_cnt);
		roce_set_field(qpc_mask->byte_212_lsn,
			       V2_QPC_BYTE_212_RETRY_NUM_INIT_M,
			       V2_QPC_BYTE_212_RETRY_NUM_INIT_S, 0);

		roce_set_field(context->byte_212_lsn,
			       V2_QPC_BYTE_212_RETRY_CNT_M,
			       V2_QPC_BYTE_212_RETRY_CNT_S,
			       attr->retry_cnt);
		roce_set_field(qpc_mask->byte_212_lsn,
			       V2_QPC_BYTE_212_RETRY_CNT_M,
			       V2_QPC_BYTE_212_RETRY_CNT_S, 0);
	}

	if (attr_mask & IB_QP_RNR_RETRY) {
		roce_set_field(context->byte_244_rnr_rxack,
			       V2_QPC_BYTE_244_RNR_NUM_INIT_M,
			       V2_QPC_BYTE_244_RNR_NUM_INIT_S, attr->rnr_retry);
		roce_set_field(qpc_mask->byte_244_rnr_rxack,
			       V2_QPC_BYTE_244_RNR_NUM_INIT_M,
			       V2_QPC_BYTE_244_RNR_NUM_INIT_S, 0);

		roce_set_field(context->byte_244_rnr_rxack,
			       V2_QPC_BYTE_244_RNR_CNT_M,
			       V2_QPC_BYTE_244_RNR_CNT_S, attr->rnr_retry);
		roce_set_field(qpc_mask->byte_244_rnr_rxack,
			       V2_QPC_BYTE_244_RNR_CNT_M,
			       V2_QPC_BYTE_244_RNR_CNT_S, 0);
	}

	/* RC&UC&UD required attr */
	if (attr_mask & IB_QP_SQ_PSN) {
		roce_set_field(context->byte_172_sq_psn,
			       V2_QPC_BYTE_172_SQ_CUR_PSN_M,
			       V2_QPC_BYTE_172_SQ_CUR_PSN_S, attr->sq_psn);
		roce_set_field(qpc_mask->byte_172_sq_psn,
			       V2_QPC_BYTE_172_SQ_CUR_PSN_M,
			       V2_QPC_BYTE_172_SQ_CUR_PSN_S, 0);

		roce_set_field(context->byte_196_sq_psn,
			       V2_QPC_BYTE_196_SQ_MAX_PSN_M,
			       V2_QPC_BYTE_196_SQ_MAX_PSN_S, attr->sq_psn);
		roce_set_field(qpc_mask->byte_196_sq_psn,
			       V2_QPC_BYTE_196_SQ_MAX_PSN_M,
			       V2_QPC_BYTE_196_SQ_MAX_PSN_S, 0);

		roce_set_field(context->byte_220_retry_psn_msn,
			       V2_QPC_BYTE_220_RETRY_MSG_PSN_M,
			       V2_QPC_BYTE_220_RETRY_MSG_PSN_S, attr->sq_psn);
		roce_set_field(qpc_mask->byte_220_retry_psn_msn,
			       V2_QPC_BYTE_220_RETRY_MSG_PSN_M,
			       V2_QPC_BYTE_220_RETRY_MSG_PSN_S, 0);

		roce_set_field(context->byte_224_retry_msg,
			       V2_QPC_BYTE_224_RETRY_MSG_PSN_M,
			       V2_QPC_BYTE_224_RETRY_MSG_PSN_S,
			       attr->sq_psn >> V2_QPC_BYTE_220_RETRY_MSG_PSN_S);
		roce_set_field(qpc_mask->byte_224_retry_msg,
			       V2_QPC_BYTE_224_RETRY_MSG_PSN_M,
			       V2_QPC_BYTE_224_RETRY_MSG_PSN_S, 0);

		roce_set_field(context->byte_224_retry_msg,
			       V2_QPC_BYTE_224_RETRY_MSG_FPKT_PSN_M,
			       V2_QPC_BYTE_224_RETRY_MSG_FPKT_PSN_S,
			       attr->sq_psn);
		roce_set_field(qpc_mask->byte_224_retry_msg,
			       V2_QPC_BYTE_224_RETRY_MSG_FPKT_PSN_M,
			       V2_QPC_BYTE_224_RETRY_MSG_FPKT_PSN_S, 0);

		roce_set_field(context->byte_244_rnr_rxack,
			       V2_QPC_BYTE_244_RX_ACK_EPSN_M,
			       V2_QPC_BYTE_244_RX_ACK_EPSN_S, attr->sq_psn);
		roce_set_field(qpc_mask->byte_244_rnr_rxack,
			       V2_QPC_BYTE_244_RX_ACK_EPSN_M,
			       V2_QPC_BYTE_244_RX_ACK_EPSN_S, 0);
	}

	if ((attr_mask & IB_QP_MAX_DEST_RD_ATOMIC) &&
	     attr->max_dest_rd_atomic) {
		roce_set_field(context->byte_140_raq, V2_QPC_BYTE_140_RR_MAX_M,
			       V2_QPC_BYTE_140_RR_MAX_S,
			       fls(attr->max_dest_rd_atomic - 1));
		roce_set_field(qpc_mask->byte_140_raq, V2_QPC_BYTE_140_RR_MAX_M,
			       V2_QPC_BYTE_140_RR_MAX_S, 0);
	}

	if ((attr_mask & IB_QP_MAX_QP_RD_ATOMIC) && attr->max_rd_atomic) {
		roce_set_field(context->byte_208_irrl, V2_QPC_BYTE_208_SR_MAX_M,
			       V2_QPC_BYTE_208_SR_MAX_S,
			       fls(attr->max_rd_atomic - 1));
		roce_set_field(qpc_mask->byte_208_irrl,
			       V2_QPC_BYTE_208_SR_MAX_M,
			       V2_QPC_BYTE_208_SR_MAX_S, 0);
	}

	if (attr_mask & (IB_QP_ACCESS_FLAGS | IB_QP_MAX_DEST_RD_ATOMIC))
		set_access_flags(hr_qp, context, qpc_mask, attr, attr_mask);

	if (attr_mask & IB_QP_MIN_RNR_TIMER) {
		roce_set_field(context->byte_80_rnr_rx_cqn,
			       V2_QPC_BYTE_80_MIN_RNR_TIME_M,
			       V2_QPC_BYTE_80_MIN_RNR_TIME_S,
			       attr->min_rnr_timer);
		roce_set_field(qpc_mask->byte_80_rnr_rx_cqn,
			       V2_QPC_BYTE_80_MIN_RNR_TIME_M,
			       V2_QPC_BYTE_80_MIN_RNR_TIME_S, 0);
	}

	/* RC&UC required attr */
	if (attr_mask & IB_QP_RQ_PSN) {
		roce_set_field(context->byte_108_rx_reqepsn,
			       V2_QPC_BYTE_108_RX_REQ_EPSN_M,
			       V2_QPC_BYTE_108_RX_REQ_EPSN_S, attr->rq_psn);
		roce_set_field(qpc_mask->byte_108_rx_reqepsn,
			       V2_QPC_BYTE_108_RX_REQ_EPSN_M,
			       V2_QPC_BYTE_108_RX_REQ_EPSN_S, 0);

		roce_set_field(context->byte_152_raq, V2_QPC_BYTE_152_RAQ_PSN_M,
			       V2_QPC_BYTE_152_RAQ_PSN_S, attr->rq_psn - 1);
		roce_set_field(qpc_mask->byte_152_raq,
			       V2_QPC_BYTE_152_RAQ_PSN_M,
			       V2_QPC_BYTE_152_RAQ_PSN_S, 0);
	}

	if (attr_mask & IB_QP_QKEY) {
		context->qkey_xrcd = cpu_to_le32(attr->qkey);
		qpc_mask->qkey_xrcd = 0;
		hr_qp->qkey = attr->qkey;
	}

	return ret;
}