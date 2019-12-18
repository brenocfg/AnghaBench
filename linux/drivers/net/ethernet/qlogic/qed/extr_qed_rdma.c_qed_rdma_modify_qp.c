#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct qed_rdma_qp {int cur_state; int /*<<< orphan*/  sqd_async; int /*<<< orphan*/  min_rnr_nak_timer; int /*<<< orphan*/  rnr_retry_cnt; int /*<<< orphan*/  retry_cnt; int /*<<< orphan*/  ack_timeout; int /*<<< orphan*/  max_rd_atomic_resp; int /*<<< orphan*/  max_rd_atomic_req; int /*<<< orphan*/  sq_psn; int /*<<< orphan*/  rq_psn; int /*<<< orphan*/ * local_mac_addr; int /*<<< orphan*/ * remote_mac_addr; int /*<<< orphan*/  lb_indication; int /*<<< orphan*/  mtu; int /*<<< orphan*/  vlan_id; scalar_t__ udp_src_port; int /*<<< orphan*/  dgid; int /*<<< orphan*/  sgid; int /*<<< orphan*/  hop_limit_ttl; int /*<<< orphan*/  flow_label; int /*<<< orphan*/  traffic_class_tos; int /*<<< orphan*/  dest_qp; int /*<<< orphan*/  e2e_flow_control_en; int /*<<< orphan*/  pkey; int /*<<< orphan*/  roce_mode; int /*<<< orphan*/  incoming_atomic_en; int /*<<< orphan*/  incoming_rdma_write_en; int /*<<< orphan*/  incoming_rdma_read_en; int /*<<< orphan*/  icid; } ;
struct qed_rdma_modify_qp_in_params {int new_state; int /*<<< orphan*/  modify_flags; int /*<<< orphan*/  sqd_async; int /*<<< orphan*/  min_rnr_nak_timer; int /*<<< orphan*/  rnr_retry_cnt; int /*<<< orphan*/  retry_cnt; int /*<<< orphan*/  ack_timeout; int /*<<< orphan*/  max_rd_atomic_resp; int /*<<< orphan*/  max_rd_atomic_req; int /*<<< orphan*/  sq_psn; int /*<<< orphan*/  rq_psn; int /*<<< orphan*/ * local_mac_addr; scalar_t__ use_local_mac; int /*<<< orphan*/ * remote_mac_addr; int /*<<< orphan*/  lb_indication; int /*<<< orphan*/  mtu; int /*<<< orphan*/  vlan_id; int /*<<< orphan*/  dgid; int /*<<< orphan*/  sgid; int /*<<< orphan*/  hop_limit_ttl; int /*<<< orphan*/  flow_label; int /*<<< orphan*/  traffic_class_tos; int /*<<< orphan*/  dest_qp; int /*<<< orphan*/  e2e_flow_control_en; int /*<<< orphan*/  pkey; int /*<<< orphan*/  roce_mode; int /*<<< orphan*/  incoming_atomic_en; int /*<<< orphan*/  incoming_rdma_write_en; int /*<<< orphan*/  incoming_rdma_read_en; } ;
struct TYPE_2__ {int /*<<< orphan*/  hw_mac_addr; } ;
struct qed_hwfn {TYPE_1__ hw_info; } ;
typedef  enum qed_roce_qp_state { ____Placeholder_qed_roce_qp_state } qed_roce_qp_state ;
typedef  enum qed_iwarp_qp_state { ____Placeholder_qed_iwarp_qp_state } qed_iwarp_qp_state ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ GET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ QED_IS_IWARP_PERSONALITY (struct qed_hwfn*) ; 
 int /*<<< orphan*/  QED_MSG_RDMA ; 
 int /*<<< orphan*/  QED_RDMA_MODIFY_QP_VALID_MAX_RD_ATOMIC_REQ ; 
 int /*<<< orphan*/  QED_RDMA_MODIFY_QP_VALID_MAX_RD_ATOMIC_RESP ; 
 int /*<<< orphan*/  QED_RDMA_MODIFY_QP_VALID_NEW_STATE ; 
 int /*<<< orphan*/  QED_RDMA_MODIFY_QP_VALID_RDMA_OPS_EN ; 
 int /*<<< orphan*/  QED_ROCE_MODIFY_QP_VALID_ACK_TIMEOUT ; 
 int /*<<< orphan*/  QED_ROCE_MODIFY_QP_VALID_ADDRESS_VECTOR ; 
 int /*<<< orphan*/  QED_ROCE_MODIFY_QP_VALID_DEST_QP ; 
 int /*<<< orphan*/  QED_ROCE_MODIFY_QP_VALID_E2E_FLOW_CONTROL_EN ; 
 int /*<<< orphan*/  QED_ROCE_MODIFY_QP_VALID_MIN_RNR_NAK_TIMER ; 
 int /*<<< orphan*/  QED_ROCE_MODIFY_QP_VALID_PKEY ; 
 int /*<<< orphan*/  QED_ROCE_MODIFY_QP_VALID_RETRY_CNT ; 
 int /*<<< orphan*/  QED_ROCE_MODIFY_QP_VALID_RNR_RETRY_CNT ; 
 int /*<<< orphan*/  QED_ROCE_MODIFY_QP_VALID_ROCE_MODE ; 
 int /*<<< orphan*/  QED_ROCE_MODIFY_QP_VALID_RQ_PSN ; 
 int /*<<< orphan*/  QED_ROCE_MODIFY_QP_VALID_SQ_PSN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int qed_iwarp_modify_qp (struct qed_hwfn*,struct qed_rdma_qp*,int,int /*<<< orphan*/ ) ; 
 int qed_roce2iwarp_state (int) ; 
 int qed_roce_modify_qp (struct qed_hwfn*,struct qed_rdma_qp*,int,struct qed_rdma_modify_qp_in_params*) ; 

__attribute__((used)) static int qed_rdma_modify_qp(void *rdma_cxt,
			      struct qed_rdma_qp *qp,
			      struct qed_rdma_modify_qp_in_params *params)
{
	struct qed_hwfn *p_hwfn = (struct qed_hwfn *)rdma_cxt;
	enum qed_roce_qp_state prev_state;
	int rc = 0;

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "icid = %08x params->new_state=%d\n",
		   qp->icid, params->new_state);

	if (rc) {
		DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "rc = %d\n", rc);
		return rc;
	}

	if (GET_FIELD(params->modify_flags,
		      QED_RDMA_MODIFY_QP_VALID_RDMA_OPS_EN)) {
		qp->incoming_rdma_read_en = params->incoming_rdma_read_en;
		qp->incoming_rdma_write_en = params->incoming_rdma_write_en;
		qp->incoming_atomic_en = params->incoming_atomic_en;
	}

	/* Update QP structure with the updated values */
	if (GET_FIELD(params->modify_flags, QED_ROCE_MODIFY_QP_VALID_ROCE_MODE))
		qp->roce_mode = params->roce_mode;
	if (GET_FIELD(params->modify_flags, QED_ROCE_MODIFY_QP_VALID_PKEY))
		qp->pkey = params->pkey;
	if (GET_FIELD(params->modify_flags,
		      QED_ROCE_MODIFY_QP_VALID_E2E_FLOW_CONTROL_EN))
		qp->e2e_flow_control_en = params->e2e_flow_control_en;
	if (GET_FIELD(params->modify_flags, QED_ROCE_MODIFY_QP_VALID_DEST_QP))
		qp->dest_qp = params->dest_qp;
	if (GET_FIELD(params->modify_flags,
		      QED_ROCE_MODIFY_QP_VALID_ADDRESS_VECTOR)) {
		/* Indicates that the following parameters have changed:
		 * Traffic class, flow label, hop limit, source GID,
		 * destination GID, loopback indicator
		 */
		qp->traffic_class_tos = params->traffic_class_tos;
		qp->flow_label = params->flow_label;
		qp->hop_limit_ttl = params->hop_limit_ttl;

		qp->sgid = params->sgid;
		qp->dgid = params->dgid;
		qp->udp_src_port = 0;
		qp->vlan_id = params->vlan_id;
		qp->mtu = params->mtu;
		qp->lb_indication = params->lb_indication;
		memcpy((u8 *)&qp->remote_mac_addr[0],
		       (u8 *)&params->remote_mac_addr[0], ETH_ALEN);
		if (params->use_local_mac) {
			memcpy((u8 *)&qp->local_mac_addr[0],
			       (u8 *)&params->local_mac_addr[0], ETH_ALEN);
		} else {
			memcpy((u8 *)&qp->local_mac_addr[0],
			       (u8 *)&p_hwfn->hw_info.hw_mac_addr, ETH_ALEN);
		}
	}
	if (GET_FIELD(params->modify_flags, QED_ROCE_MODIFY_QP_VALID_RQ_PSN))
		qp->rq_psn = params->rq_psn;
	if (GET_FIELD(params->modify_flags, QED_ROCE_MODIFY_QP_VALID_SQ_PSN))
		qp->sq_psn = params->sq_psn;
	if (GET_FIELD(params->modify_flags,
		      QED_RDMA_MODIFY_QP_VALID_MAX_RD_ATOMIC_REQ))
		qp->max_rd_atomic_req = params->max_rd_atomic_req;
	if (GET_FIELD(params->modify_flags,
		      QED_RDMA_MODIFY_QP_VALID_MAX_RD_ATOMIC_RESP))
		qp->max_rd_atomic_resp = params->max_rd_atomic_resp;
	if (GET_FIELD(params->modify_flags,
		      QED_ROCE_MODIFY_QP_VALID_ACK_TIMEOUT))
		qp->ack_timeout = params->ack_timeout;
	if (GET_FIELD(params->modify_flags, QED_ROCE_MODIFY_QP_VALID_RETRY_CNT))
		qp->retry_cnt = params->retry_cnt;
	if (GET_FIELD(params->modify_flags,
		      QED_ROCE_MODIFY_QP_VALID_RNR_RETRY_CNT))
		qp->rnr_retry_cnt = params->rnr_retry_cnt;
	if (GET_FIELD(params->modify_flags,
		      QED_ROCE_MODIFY_QP_VALID_MIN_RNR_NAK_TIMER))
		qp->min_rnr_nak_timer = params->min_rnr_nak_timer;

	qp->sqd_async = params->sqd_async;

	prev_state = qp->cur_state;
	if (GET_FIELD(params->modify_flags,
		      QED_RDMA_MODIFY_QP_VALID_NEW_STATE)) {
		qp->cur_state = params->new_state;
		DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "qp->cur_state=%d\n",
			   qp->cur_state);
	}

	if (QED_IS_IWARP_PERSONALITY(p_hwfn)) {
		enum qed_iwarp_qp_state new_state =
		    qed_roce2iwarp_state(qp->cur_state);

		rc = qed_iwarp_modify_qp(p_hwfn, qp, new_state, 0);
	} else {
		rc = qed_roce_modify_qp(p_hwfn, qp, prev_state, params);
	}

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "Modify QP, rc = %d\n", rc);
	return rc;
}