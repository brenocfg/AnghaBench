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
struct qed_rdma_query_qp_out_params {int /*<<< orphan*/  sqd_async; int /*<<< orphan*/  max_dest_rd_atomic; int /*<<< orphan*/  max_rd_atomic; scalar_t__ pkey_index; int /*<<< orphan*/  min_rnr_nak_timer; int /*<<< orphan*/  retry_cnt; int /*<<< orphan*/  rnr_retry; int /*<<< orphan*/  timeout; int /*<<< orphan*/  traffic_class_tos; int /*<<< orphan*/  hop_limit_ttl; int /*<<< orphan*/  flow_label; int /*<<< orphan*/  dgid; int /*<<< orphan*/  incoming_rdma_write_en; int /*<<< orphan*/  incoming_rdma_read_en; int /*<<< orphan*/  e2e_flow_control_en; int /*<<< orphan*/  incoming_atomic_en; int /*<<< orphan*/  dest_qp; int /*<<< orphan*/  mtu; } ;
struct qed_rdma_qp {int icid; int /*<<< orphan*/  sqd_async; int /*<<< orphan*/  max_rd_atomic_resp; int /*<<< orphan*/  max_rd_atomic_req; int /*<<< orphan*/  min_rnr_nak_timer; int /*<<< orphan*/  retry_cnt; int /*<<< orphan*/  rnr_retry_cnt; int /*<<< orphan*/  ack_timeout; int /*<<< orphan*/  traffic_class_tos; int /*<<< orphan*/  hop_limit_ttl; int /*<<< orphan*/  flow_label; int /*<<< orphan*/  dgid; int /*<<< orphan*/  incoming_rdma_write_en; int /*<<< orphan*/  incoming_rdma_read_en; int /*<<< orphan*/  e2e_flow_control_en; int /*<<< orphan*/  incoming_atomic_en; int /*<<< orphan*/  dest_qp; int /*<<< orphan*/  mtu; } ;
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ QED_IS_IWARP_PERSONALITY (struct qed_hwfn*) ; 
 int /*<<< orphan*/  QED_MSG_RDMA ; 
 int /*<<< orphan*/  qed_iwarp_query_qp (struct qed_rdma_qp*,struct qed_rdma_query_qp_out_params*) ; 
 int qed_roce_query_qp (struct qed_hwfn*,struct qed_rdma_qp*,struct qed_rdma_query_qp_out_params*) ; 

__attribute__((used)) static int qed_rdma_query_qp(void *rdma_cxt,
			     struct qed_rdma_qp *qp,
			     struct qed_rdma_query_qp_out_params *out_params)
{
	struct qed_hwfn *p_hwfn = (struct qed_hwfn *)rdma_cxt;
	int rc = 0;

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "icid = %08x\n", qp->icid);

	/* The following fields are filled in from qp and not FW as they can't
	 * be modified by FW
	 */
	out_params->mtu = qp->mtu;
	out_params->dest_qp = qp->dest_qp;
	out_params->incoming_atomic_en = qp->incoming_atomic_en;
	out_params->e2e_flow_control_en = qp->e2e_flow_control_en;
	out_params->incoming_rdma_read_en = qp->incoming_rdma_read_en;
	out_params->incoming_rdma_write_en = qp->incoming_rdma_write_en;
	out_params->dgid = qp->dgid;
	out_params->flow_label = qp->flow_label;
	out_params->hop_limit_ttl = qp->hop_limit_ttl;
	out_params->traffic_class_tos = qp->traffic_class_tos;
	out_params->timeout = qp->ack_timeout;
	out_params->rnr_retry = qp->rnr_retry_cnt;
	out_params->retry_cnt = qp->retry_cnt;
	out_params->min_rnr_nak_timer = qp->min_rnr_nak_timer;
	out_params->pkey_index = 0;
	out_params->max_rd_atomic = qp->max_rd_atomic_req;
	out_params->max_dest_rd_atomic = qp->max_rd_atomic_resp;
	out_params->sqd_async = qp->sqd_async;

	if (QED_IS_IWARP_PERSONALITY(p_hwfn))
		qed_iwarp_query_qp(qp, out_params);
	else
		rc = qed_roce_query_qp(p_hwfn, qp, out_params);

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "Query QP, rc = %d\n", rc);
	return rc;
}