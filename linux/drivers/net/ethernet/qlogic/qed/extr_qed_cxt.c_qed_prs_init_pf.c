#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct qed_tid_seg {int /*<<< orphan*/  count; } ;
struct TYPE_3__ {scalar_t__ is_target; } ;
struct TYPE_4__ {TYPE_1__ fcoe_pf_params; } ;
struct qed_hwfn {TYPE_2__ pf_params; struct qed_cxt_mngr* p_cxt_mngr; } ;
struct qed_cxt_mngr {struct qed_conn_type_cfg* conn_cfg; } ;
struct qed_conn_type_cfg {struct qed_tid_seg* tid_seg; int /*<<< orphan*/  cid_count; } ;

/* Variables and functions */
 size_t PROTOCOLID_FCOE ; 
 int /*<<< orphan*/  PRS_REG_TASK_ID_MAX_INITIATOR_PF_RT_OFFSET ; 
 int /*<<< orphan*/  PRS_REG_TASK_ID_MAX_TARGET_PF_RT_OFFSET ; 
 size_t QED_CXT_FCOE_TID_SEG ; 
 int /*<<< orphan*/  STORE_RT_REG_AGG (struct qed_hwfn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qed_prs_init_pf(struct qed_hwfn *p_hwfn)
{
	struct qed_cxt_mngr *p_mngr = p_hwfn->p_cxt_mngr;
	struct qed_conn_type_cfg *p_fcoe;
	struct qed_tid_seg *p_tid;

	p_fcoe = &p_mngr->conn_cfg[PROTOCOLID_FCOE];

	/* If FCoE is active set the MAX OX_ID (tid) in the Parser */
	if (!p_fcoe->cid_count)
		return;

	p_tid = &p_fcoe->tid_seg[QED_CXT_FCOE_TID_SEG];
	if (p_hwfn->pf_params.fcoe_pf_params.is_target) {
		STORE_RT_REG_AGG(p_hwfn,
				 PRS_REG_TASK_ID_MAX_TARGET_PF_RT_OFFSET,
				 p_tid->count);
	} else {
		STORE_RT_REG_AGG(p_hwfn,
				 PRS_REG_TASK_ID_MAX_INITIATOR_PF_RT_OFFSET,
				 p_tid->count);
	}
}