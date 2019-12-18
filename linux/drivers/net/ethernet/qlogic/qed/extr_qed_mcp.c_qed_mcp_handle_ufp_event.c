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
struct qed_ptt {int dummy; } ;
struct TYPE_4__ {scalar_t__ mode; int /*<<< orphan*/  tc; } ;
struct TYPE_3__ {int /*<<< orphan*/  ooo_tc; } ;
struct qed_hwfn {TYPE_2__ ufp_info; int /*<<< orphan*/  hw_info; TYPE_1__ qm_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct qed_hwfn*,char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  QED_DCBX_OPERATIONAL_MIB ; 
 scalar_t__ QED_UFP_MODE_ETS ; 
 scalar_t__ QED_UFP_MODE_VNIC_BW ; 
 int /*<<< orphan*/  qed_dcbx_mib_update_event (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_hw_info_set_offload_tc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_mcp_read_ufp_config (struct qed_hwfn*,struct qed_ptt*) ; 
 int /*<<< orphan*/  qed_qm_reconf (struct qed_hwfn*,struct qed_ptt*) ; 
 int /*<<< orphan*/  qed_sp_pf_update_stag (struct qed_hwfn*) ; 
 int /*<<< orphan*/  qed_sp_pf_update_ufp (struct qed_hwfn*) ; 

__attribute__((used)) static int
qed_mcp_handle_ufp_event(struct qed_hwfn *p_hwfn, struct qed_ptt *p_ptt)
{
	qed_mcp_read_ufp_config(p_hwfn, p_ptt);

	if (p_hwfn->ufp_info.mode == QED_UFP_MODE_VNIC_BW) {
		p_hwfn->qm_info.ooo_tc = p_hwfn->ufp_info.tc;
		qed_hw_info_set_offload_tc(&p_hwfn->hw_info,
					   p_hwfn->ufp_info.tc);

		qed_qm_reconf(p_hwfn, p_ptt);
	} else if (p_hwfn->ufp_info.mode == QED_UFP_MODE_ETS) {
		/* Merge UFP TC with the dcbx TC data */
		qed_dcbx_mib_update_event(p_hwfn, p_ptt,
					  QED_DCBX_OPERATIONAL_MIB);
	} else {
		DP_ERR(p_hwfn, "Invalid sched type, discard the UFP config\n");
		return -EINVAL;
	}

	/* update storm FW with negotiation results */
	qed_sp_pf_update_ufp(p_hwfn);

	/* update stag pcp value */
	qed_sp_pf_update_stag(p_hwfn);

	return 0;
}