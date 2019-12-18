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
struct qed_spq_entry {int dummy; } ;
struct qed_sp_init_data {int /*<<< orphan*/  comp_mode; int /*<<< orphan*/  opaque_fid; int /*<<< orphan*/  cid; } ;
struct qed_rdma_qp {int /*<<< orphan*/  icid; } ;
struct qed_iwarp_send_rtr_in {struct qed_iwarp_ep* ep_context; } ;
struct qed_iwarp_ep {int /*<<< orphan*/  tcp_cid; struct qed_rdma_qp* qp; } ;
struct TYPE_2__ {int /*<<< orphan*/  opaque_fid; } ;
struct qed_hwfn {TYPE_1__ hw_info; } ;
typedef  int /*<<< orphan*/  init_data ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct qed_hwfn*,char*) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,int,...) ; 
 int EINVAL ; 
 int /*<<< orphan*/  IWARP_RAMROD_CMD_ID_MPA_OFFLOAD_SEND_RTR ; 
 int /*<<< orphan*/  PROTOCOLID_IWARP ; 
 int /*<<< orphan*/  QED_MSG_RDMA ; 
 int /*<<< orphan*/  QED_SPQ_MODE_CB ; 
 int /*<<< orphan*/  memset (struct qed_sp_init_data*,int /*<<< orphan*/ ,int) ; 
 int qed_sp_init_request (struct qed_hwfn*,struct qed_spq_entry**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct qed_sp_init_data*) ; 
 int qed_spq_post (struct qed_hwfn*,struct qed_spq_entry*,int /*<<< orphan*/ *) ; 

int qed_iwarp_send_rtr(void *rdma_cxt, struct qed_iwarp_send_rtr_in *iparams)
{
	struct qed_hwfn *p_hwfn = rdma_cxt;
	struct qed_sp_init_data init_data;
	struct qed_spq_entry *p_ent;
	struct qed_iwarp_ep *ep;
	struct qed_rdma_qp *qp;
	int rc;

	ep = iparams->ep_context;
	if (!ep) {
		DP_ERR(p_hwfn, "Ep Context receive in send_rtr is NULL\n");
		return -EINVAL;
	}

	qp = ep->qp;

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "QP(0x%x) EP(0x%x)\n",
		   qp->icid, ep->tcp_cid);

	memset(&init_data, 0, sizeof(init_data));
	init_data.cid = qp->icid;
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_CB;

	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 IWARP_RAMROD_CMD_ID_MPA_OFFLOAD_SEND_RTR,
				 PROTOCOLID_IWARP, &init_data);

	if (rc)
		return rc;

	rc = qed_spq_post(p_hwfn, p_ent, NULL);

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "rc = 0x%x\n", rc);

	return rc;
}