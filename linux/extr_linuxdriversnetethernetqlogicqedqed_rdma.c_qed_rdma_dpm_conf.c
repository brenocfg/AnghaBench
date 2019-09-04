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
typedef  int u32 ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int /*<<< orphan*/  db_bar_no_edpm; int /*<<< orphan*/  dcbx_no_edpm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DORQ_REG_PF_DPM_ENABLE ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int QED_MSG_DCB ; 
 int QED_MSG_RDMA ; 
 int /*<<< orphan*/  qed_wr (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ,int) ; 

void qed_rdma_dpm_conf(struct qed_hwfn *p_hwfn, struct qed_ptt *p_ptt)
{
	u32 val;

	val = (p_hwfn->dcbx_no_edpm || p_hwfn->db_bar_no_edpm) ? 0 : 1;

	qed_wr(p_hwfn, p_ptt, DORQ_REG_PF_DPM_ENABLE, val);
	DP_VERBOSE(p_hwfn, (QED_MSG_DCB | QED_MSG_RDMA),
		   "Changing DPM_EN state to %d (DCBX=%d, DB_BAR=%d)\n",
		   val, p_hwfn->dcbx_no_edpm, p_hwfn->db_bar_no_edpm);
}