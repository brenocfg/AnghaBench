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
struct TYPE_4__ {int update_mf_vlan_flag; int /*<<< orphan*/  mf_vlan; } ;
struct TYPE_5__ {TYPE_1__ pf_update; } ;
struct qed_spq_entry {TYPE_2__ ramrod; } ;
struct qed_sp_init_data {int /*<<< orphan*/  comp_mode; int /*<<< orphan*/  opaque_fid; int /*<<< orphan*/  cid; } ;
struct TYPE_6__ {int /*<<< orphan*/  ovlan; int /*<<< orphan*/  opaque_fid; } ;
struct qed_hwfn {TYPE_3__ hw_info; } ;
typedef  int /*<<< orphan*/  init_data ;

/* Variables and functions */
 int /*<<< orphan*/  COMMON_RAMROD_PF_UPDATE ; 
 int EINVAL ; 
 int /*<<< orphan*/  PROTOCOLID_COMMON ; 
 int /*<<< orphan*/  QED_SPQ_MODE_CB ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct qed_sp_init_data*,int /*<<< orphan*/ ,int) ; 
 int qed_sp_init_request (struct qed_hwfn*,struct qed_spq_entry**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct qed_sp_init_data*) ; 
 int /*<<< orphan*/  qed_spq_get_cid (struct qed_hwfn*) ; 
 int qed_spq_post (struct qed_hwfn*,struct qed_spq_entry*,int /*<<< orphan*/ *) ; 

int qed_sp_pf_update_stag(struct qed_hwfn *p_hwfn)
{
	struct qed_spq_entry *p_ent = NULL;
	struct qed_sp_init_data init_data;
	int rc = -EINVAL;

	/* Get SPQ entry */
	memset(&init_data, 0, sizeof(init_data));
	init_data.cid = qed_spq_get_cid(p_hwfn);
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_CB;

	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 COMMON_RAMROD_PF_UPDATE, PROTOCOLID_COMMON,
				 &init_data);
	if (rc)
		return rc;

	p_ent->ramrod.pf_update.update_mf_vlan_flag = true;
	p_ent->ramrod.pf_update.mf_vlan = cpu_to_le16(p_hwfn->hw_info.ovlan);

	return qed_spq_post(p_hwfn, p_ent, NULL);
}