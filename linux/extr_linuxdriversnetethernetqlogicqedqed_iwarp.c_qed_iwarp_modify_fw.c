#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct iwarp_modify_qp_ramrod_data {int /*<<< orphan*/  transition_to_state; int /*<<< orphan*/  flags; } ;
struct TYPE_6__ {struct iwarp_modify_qp_ramrod_data iwarp_modify_qp; } ;
struct qed_spq_entry {TYPE_3__ ramrod; } ;
struct qed_sp_init_data {int /*<<< orphan*/  comp_mode; int /*<<< orphan*/  opaque_fid; int /*<<< orphan*/  cid; } ;
struct qed_rdma_qp {scalar_t__ iwarp_state; int /*<<< orphan*/  icid; } ;
struct TYPE_4__ {int /*<<< orphan*/  opaque_fid; } ;
struct qed_hwfn {TYPE_2__* p_rdma_info; TYPE_1__ hw_info; } ;
typedef  int /*<<< orphan*/  init_data ;
struct TYPE_5__ {int /*<<< orphan*/  proto; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IWARP_MODIFY_QP_RAMROD_DATA_STATE_TRANS_EN ; 
 int /*<<< orphan*/  IWARP_MODIFY_QP_STATE_CLOSING ; 
 int /*<<< orphan*/  IWARP_MODIFY_QP_STATE_ERROR ; 
 int /*<<< orphan*/  IWARP_RAMROD_CMD_ID_MODIFY_QP ; 
 scalar_t__ QED_IWARP_QP_STATE_CLOSING ; 
 int /*<<< orphan*/  QED_MSG_RDMA ; 
 int /*<<< orphan*/  QED_SPQ_MODE_EBLOCK ; 
 int /*<<< orphan*/  SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct qed_sp_init_data*,int /*<<< orphan*/ ,int) ; 
 int qed_sp_init_request (struct qed_hwfn*,struct qed_spq_entry**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct qed_sp_init_data*) ; 
 int qed_spq_post (struct qed_hwfn*,struct qed_spq_entry*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qed_iwarp_modify_fw(struct qed_hwfn *p_hwfn, struct qed_rdma_qp *qp)
{
	struct iwarp_modify_qp_ramrod_data *p_ramrod;
	struct qed_sp_init_data init_data;
	struct qed_spq_entry *p_ent;
	int rc;

	/* Get SPQ entry */
	memset(&init_data, 0, sizeof(init_data));
	init_data.cid = qp->icid;
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBLOCK;

	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 IWARP_RAMROD_CMD_ID_MODIFY_QP,
				 p_hwfn->p_rdma_info->proto, &init_data);
	if (rc)
		return rc;

	p_ramrod = &p_ent->ramrod.iwarp_modify_qp;
	SET_FIELD(p_ramrod->flags, IWARP_MODIFY_QP_RAMROD_DATA_STATE_TRANS_EN,
		  0x1);
	if (qp->iwarp_state == QED_IWARP_QP_STATE_CLOSING)
		p_ramrod->transition_to_state = IWARP_MODIFY_QP_STATE_CLOSING;
	else
		p_ramrod->transition_to_state = IWARP_MODIFY_QP_STATE_ERROR;

	rc = qed_spq_post(p_hwfn, p_ent, NULL);

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "QP(0x%x)rc=%d\n", qp->icid, rc);

	return rc;
}