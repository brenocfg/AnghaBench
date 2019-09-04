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
typedef  void* u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct qed_ptt {int dummy; } ;
struct TYPE_7__ {void* ooo_tc; } ;
struct qed_hw_info {void* num_active_tc; } ;
struct qed_hwfn {TYPE_4__* p_dcbx_info; int /*<<< orphan*/  rel_pf_id; TYPE_3__ qm_info; struct qed_hw_info hw_info; } ;
struct qed_dcbx_results {int dcbx_enabled; int /*<<< orphan*/  pf_id; int /*<<< orphan*/  member_0; } ;
struct dcbx_ets_feature {int /*<<< orphan*/  flags; int /*<<< orphan*/ * pri_tc_tbl; } ;
struct dcbx_app_priority_feature {int /*<<< orphan*/  flags; struct dcbx_app_priority_entry* app_pri_tbl; } ;
struct dcbx_app_priority_entry {int dummy; } ;
struct TYPE_5__ {struct dcbx_ets_feature ets; struct dcbx_app_priority_feature app; } ;
struct TYPE_6__ {TYPE_1__ features; int /*<<< orphan*/  flags; } ;
struct TYPE_8__ {int /*<<< orphan*/  results; TYPE_2__ operational; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCBX_APP_NUM_ENTRIES ; 
 int /*<<< orphan*/  DCBX_CONFIG_VERSION ; 
 int /*<<< orphan*/  DCBX_ETS_MAX_TCS ; 
 int /*<<< orphan*/  DCBX_OOO_TC ; 
 void* QED_MFW_GET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct qed_dcbx_results*,int) ; 
 int /*<<< orphan*/  qed_dcbx_dp_protocol (struct qed_hwfn*,struct qed_dcbx_results*) ; 
 int qed_dcbx_process_tlv (struct qed_hwfn*,struct qed_ptt*,struct qed_dcbx_results*,struct dcbx_app_priority_entry*,int /*<<< orphan*/ ,int,void*) ; 

__attribute__((used)) static int
qed_dcbx_process_mib_info(struct qed_hwfn *p_hwfn, struct qed_ptt *p_ptt)
{
	struct dcbx_app_priority_feature *p_app;
	struct dcbx_app_priority_entry *p_tbl;
	struct qed_dcbx_results data = { 0 };
	struct dcbx_ets_feature *p_ets;
	struct qed_hw_info *p_info;
	u32 pri_tc_tbl, flags;
	u8 dcbx_version;
	int num_entries;
	int rc = 0;

	flags = p_hwfn->p_dcbx_info->operational.flags;
	dcbx_version = QED_MFW_GET_FIELD(flags, DCBX_CONFIG_VERSION);

	p_app = &p_hwfn->p_dcbx_info->operational.features.app;
	p_tbl = p_app->app_pri_tbl;

	p_ets = &p_hwfn->p_dcbx_info->operational.features.ets;
	pri_tc_tbl = p_ets->pri_tc_tbl[0];

	p_info = &p_hwfn->hw_info;
	num_entries = QED_MFW_GET_FIELD(p_app->flags, DCBX_APP_NUM_ENTRIES);

	rc = qed_dcbx_process_tlv(p_hwfn, p_ptt, &data, p_tbl, pri_tc_tbl,
				  num_entries, dcbx_version);
	if (rc)
		return rc;

	p_info->num_active_tc = QED_MFW_GET_FIELD(p_ets->flags,
						  DCBX_ETS_MAX_TCS);
	p_hwfn->qm_info.ooo_tc = QED_MFW_GET_FIELD(p_ets->flags, DCBX_OOO_TC);
	data.pf_id = p_hwfn->rel_pf_id;
	data.dcbx_enabled = !!dcbx_version;

	qed_dcbx_dp_protocol(p_hwfn, &data);

	memcpy(&p_hwfn->p_dcbx_info->results, &data,
	       sizeof(struct qed_dcbx_results));

	return 0;
}