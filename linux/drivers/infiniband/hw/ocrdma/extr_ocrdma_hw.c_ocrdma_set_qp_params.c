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
struct TYPE_5__ {int /*<<< orphan*/  device; } ;
struct ocrdma_qp {scalar_t__ qp_type; scalar_t__ max_ord; scalar_t__ max_ird; int /*<<< orphan*/  qkey; TYPE_1__ ibqp; } ;
struct TYPE_8__ {int path_mtu_pkey_indx; int dmac_b0_to_b3; int vlan_dmac_b4_to_b5; int ack_to_rnr_rtc_dest_qpn; int rnt_rc_sl_fl; int tclass_sq_psn; int hop_lmt_rq_psn; int max_ord_ird; int /*<<< orphan*/  max_sge_recv_flags; int /*<<< orphan*/  qkey; } ;
struct ocrdma_modify_qp {TYPE_4__ params; int /*<<< orphan*/  flags; } ;
struct TYPE_7__ {scalar_t__ max_ord_per_qp; scalar_t__ max_ird_per_qp; } ;
struct TYPE_6__ {int* mac_addr; } ;
struct ocrdma_dev {TYPE_3__ attr; int /*<<< orphan*/  id; TYPE_2__ nic_info; } ;
struct ib_qp_attr {int pkey_index; int dest_qp_num; scalar_t__ path_mtu; int timeout; int retry_cnt; int min_rnr_timer; int rnr_retry; int sq_psn; int rq_psn; scalar_t__ max_rd_atomic; scalar_t__ max_dest_rd_atomic; scalar_t__ en_sqd_async_notify; int /*<<< orphan*/  qkey; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IB_MTU_4096 ; 
 scalar_t__ IB_MTU_512 ; 
 scalar_t__ IB_QPT_GSI ; 
 scalar_t__ IB_QPT_UD ; 
 int IB_QP_AV ; 
 int IB_QP_DEST_QPN ; 
 int IB_QP_EN_SQD_ASYNC_NOTIFY ; 
 int IB_QP_MAX_DEST_RD_ATOMIC ; 
 int IB_QP_MAX_QP_RD_ATOMIC ; 
 int IB_QP_MIN_RNR_TIMER ; 
 int IB_QP_PATH_MTU ; 
 int IB_QP_PKEY_INDEX ; 
 int IB_QP_QKEY ; 
 int IB_QP_RETRY_CNT ; 
 int IB_QP_RNR_RETRY ; 
 int IB_QP_RQ_PSN ; 
 int IB_QP_SQ_PSN ; 
 int IB_QP_TIMEOUT ; 
 int OCRDMA_QP_PARAMS_ACK_TIMEOUT_SHIFT ; 
 int OCRDMA_QP_PARAMS_DEST_QPN_MASK ; 
 int /*<<< orphan*/  OCRDMA_QP_PARAMS_FLAGS_SQD_ASYNC ; 
 int OCRDMA_QP_PARAMS_MAX_IRD_MASK ; 
 int OCRDMA_QP_PARAMS_MAX_ORD_SHIFT ; 
 int OCRDMA_QP_PARAMS_PATH_MTU_MASK ; 
 int OCRDMA_QP_PARAMS_PATH_MTU_SHIFT ; 
 int OCRDMA_QP_PARAMS_PKEY_INDEX_MASK ; 
 int OCRDMA_QP_PARAMS_RETRY_CNT_MASK ; 
 int OCRDMA_QP_PARAMS_RETRY_CNT_SHIFT ; 
 int OCRDMA_QP_PARAMS_RNR_NAK_TIMER_MASK ; 
 int OCRDMA_QP_PARAMS_RNR_NAK_TIMER_SHIFT ; 
 int OCRDMA_QP_PARAMS_RNR_RETRY_CNT_MASK ; 
 int OCRDMA_QP_PARAMS_RNR_RETRY_CNT_SHIFT ; 
 int /*<<< orphan*/  OCRDMA_QP_PARA_ACK_TO_VALID ; 
 int /*<<< orphan*/  OCRDMA_QP_PARA_DST_QPN_VALID ; 
 int /*<<< orphan*/  OCRDMA_QP_PARA_MAX_IRD_VALID ; 
 int /*<<< orphan*/  OCRDMA_QP_PARA_MAX_ORD_VALID ; 
 int /*<<< orphan*/  OCRDMA_QP_PARA_PKEY_VALID ; 
 int /*<<< orphan*/  OCRDMA_QP_PARA_PMTU_VALID ; 
 int /*<<< orphan*/  OCRDMA_QP_PARA_QKEY_VALID ; 
 int /*<<< orphan*/  OCRDMA_QP_PARA_RETRY_CNT_VALID ; 
 int /*<<< orphan*/  OCRDMA_QP_PARA_RNT_VALID ; 
 int /*<<< orphan*/  OCRDMA_QP_PARA_RQPSN_VALID ; 
 int /*<<< orphan*/  OCRDMA_QP_PARA_RRC_VALID ; 
 int /*<<< orphan*/  OCRDMA_QP_PARA_SQPSN_VALID ; 
 struct ocrdma_dev* get_ocrdma_dev (int /*<<< orphan*/ ) ; 
 int ib_mtu_enum_to_int (scalar_t__) ; 
 int ocrdma_set_av_params (struct ocrdma_qp*,struct ocrdma_modify_qp*,struct ib_qp_attr*,int) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ocrdma_set_qp_params(struct ocrdma_qp *qp,
				struct ocrdma_modify_qp *cmd,
				struct ib_qp_attr *attrs, int attr_mask)
{
	int status = 0;
	struct ocrdma_dev *dev = get_ocrdma_dev(qp->ibqp.device);

	if (attr_mask & IB_QP_PKEY_INDEX) {
		cmd->params.path_mtu_pkey_indx |= (attrs->pkey_index &
					    OCRDMA_QP_PARAMS_PKEY_INDEX_MASK);
		cmd->flags |= OCRDMA_QP_PARA_PKEY_VALID;
	}
	if (attr_mask & IB_QP_QKEY) {
		qp->qkey = attrs->qkey;
		cmd->params.qkey = attrs->qkey;
		cmd->flags |= OCRDMA_QP_PARA_QKEY_VALID;
	}
	if (attr_mask & IB_QP_AV) {
		status = ocrdma_set_av_params(qp, cmd, attrs, attr_mask);
		if (status)
			return status;
	} else if (qp->qp_type == IB_QPT_GSI || qp->qp_type == IB_QPT_UD) {
		/* set the default mac address for UD, GSI QPs */
		cmd->params.dmac_b0_to_b3 = dev->nic_info.mac_addr[0] |
			(dev->nic_info.mac_addr[1] << 8) |
			(dev->nic_info.mac_addr[2] << 16) |
			(dev->nic_info.mac_addr[3] << 24);
		cmd->params.vlan_dmac_b4_to_b5 = dev->nic_info.mac_addr[4] |
					(dev->nic_info.mac_addr[5] << 8);
	}
	if ((attr_mask & IB_QP_EN_SQD_ASYNC_NOTIFY) &&
	    attrs->en_sqd_async_notify) {
		cmd->params.max_sge_recv_flags |=
			OCRDMA_QP_PARAMS_FLAGS_SQD_ASYNC;
		cmd->flags |= OCRDMA_QP_PARA_DST_QPN_VALID;
	}
	if (attr_mask & IB_QP_DEST_QPN) {
		cmd->params.ack_to_rnr_rtc_dest_qpn |= (attrs->dest_qp_num &
				OCRDMA_QP_PARAMS_DEST_QPN_MASK);
		cmd->flags |= OCRDMA_QP_PARA_DST_QPN_VALID;
	}
	if (attr_mask & IB_QP_PATH_MTU) {
		if (attrs->path_mtu < IB_MTU_512 ||
		    attrs->path_mtu > IB_MTU_4096) {
			pr_err("ocrdma%d: IB MTU %d is not supported\n",
			       dev->id, ib_mtu_enum_to_int(attrs->path_mtu));
			status = -EINVAL;
			goto pmtu_err;
		}
		cmd->params.path_mtu_pkey_indx |=
		    (ib_mtu_enum_to_int(attrs->path_mtu) <<
		     OCRDMA_QP_PARAMS_PATH_MTU_SHIFT) &
		    OCRDMA_QP_PARAMS_PATH_MTU_MASK;
		cmd->flags |= OCRDMA_QP_PARA_PMTU_VALID;
	}
	if (attr_mask & IB_QP_TIMEOUT) {
		cmd->params.ack_to_rnr_rtc_dest_qpn |= attrs->timeout <<
		    OCRDMA_QP_PARAMS_ACK_TIMEOUT_SHIFT;
		cmd->flags |= OCRDMA_QP_PARA_ACK_TO_VALID;
	}
	if (attr_mask & IB_QP_RETRY_CNT) {
		cmd->params.rnt_rc_sl_fl |= (attrs->retry_cnt <<
				      OCRDMA_QP_PARAMS_RETRY_CNT_SHIFT) &
		    OCRDMA_QP_PARAMS_RETRY_CNT_MASK;
		cmd->flags |= OCRDMA_QP_PARA_RETRY_CNT_VALID;
	}
	if (attr_mask & IB_QP_MIN_RNR_TIMER) {
		cmd->params.rnt_rc_sl_fl |= (attrs->min_rnr_timer <<
				      OCRDMA_QP_PARAMS_RNR_NAK_TIMER_SHIFT) &
		    OCRDMA_QP_PARAMS_RNR_NAK_TIMER_MASK;
		cmd->flags |= OCRDMA_QP_PARA_RNT_VALID;
	}
	if (attr_mask & IB_QP_RNR_RETRY) {
		cmd->params.ack_to_rnr_rtc_dest_qpn |= (attrs->rnr_retry <<
			OCRDMA_QP_PARAMS_RNR_RETRY_CNT_SHIFT)
			& OCRDMA_QP_PARAMS_RNR_RETRY_CNT_MASK;
		cmd->flags |= OCRDMA_QP_PARA_RRC_VALID;
	}
	if (attr_mask & IB_QP_SQ_PSN) {
		cmd->params.tclass_sq_psn |= (attrs->sq_psn & 0x00ffffff);
		cmd->flags |= OCRDMA_QP_PARA_SQPSN_VALID;
	}
	if (attr_mask & IB_QP_RQ_PSN) {
		cmd->params.hop_lmt_rq_psn |= (attrs->rq_psn & 0x00ffffff);
		cmd->flags |= OCRDMA_QP_PARA_RQPSN_VALID;
	}
	if (attr_mask & IB_QP_MAX_QP_RD_ATOMIC) {
		if (attrs->max_rd_atomic > dev->attr.max_ord_per_qp) {
			status = -EINVAL;
			goto pmtu_err;
		}
		qp->max_ord = attrs->max_rd_atomic;
		cmd->flags |= OCRDMA_QP_PARA_MAX_ORD_VALID;
	}
	if (attr_mask & IB_QP_MAX_DEST_RD_ATOMIC) {
		if (attrs->max_dest_rd_atomic > dev->attr.max_ird_per_qp) {
			status = -EINVAL;
			goto pmtu_err;
		}
		qp->max_ird = attrs->max_dest_rd_atomic;
		cmd->flags |= OCRDMA_QP_PARA_MAX_IRD_VALID;
	}
	cmd->params.max_ord_ird = (qp->max_ord <<
				OCRDMA_QP_PARAMS_MAX_ORD_SHIFT) |
				(qp->max_ird & OCRDMA_QP_PARAMS_MAX_IRD_MASK);
pmtu_err:
	return status;
}