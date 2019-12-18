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
typedef  size_t u32 ;
struct qed_tid_seg {scalar_t__ count; } ;
struct qed_qm_iids {size_t tids; size_t vf_cids; int /*<<< orphan*/  cids; } ;
struct qed_hwfn {struct qed_cxt_mngr* p_cxt_mngr; } ;
struct qed_cxt_mngr {size_t vf_count; TYPE_1__* conn_cfg; } ;
struct TYPE_2__ {struct qed_tid_seg* tid_seg; scalar_t__ cids_per_vf; scalar_t__ cid_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,size_t,size_t,size_t) ; 
 size_t MAX_CONN_TYPES ; 
 size_t NUM_TASK_PF_SEGMENTS ; 
 int /*<<< orphan*/  QED_MSG_ILT ; 

__attribute__((used)) static void qed_cxt_qm_iids(struct qed_hwfn *p_hwfn,
			    struct qed_qm_iids *iids)
{
	struct qed_cxt_mngr *p_mngr = p_hwfn->p_cxt_mngr;
	struct qed_tid_seg *segs;
	u32 vf_cids = 0, type, j;
	u32 vf_tids = 0;

	for (type = 0; type < MAX_CONN_TYPES; type++) {
		iids->cids += p_mngr->conn_cfg[type].cid_count;
		vf_cids += p_mngr->conn_cfg[type].cids_per_vf;

		segs = p_mngr->conn_cfg[type].tid_seg;
		/* for each segment there is at most one
		 * protocol for which count is not 0.
		 */
		for (j = 0; j < NUM_TASK_PF_SEGMENTS; j++)
			iids->tids += segs[j].count;

		/* The last array elelment is for the VFs. As for PF
		 * segments there can be only one protocol for
		 * which this value is not 0.
		 */
		vf_tids += segs[NUM_TASK_PF_SEGMENTS].count;
	}

	iids->vf_cids += vf_cids * p_mngr->vf_count;
	iids->tids += vf_tids * p_mngr->vf_count;

	DP_VERBOSE(p_hwfn, QED_MSG_ILT,
		   "iids: CIDS %08x vf_cids %08x tids %08x vf_tids %08x\n",
		   iids->cids, iids->vf_cids, iids->tids, vf_tids);
}