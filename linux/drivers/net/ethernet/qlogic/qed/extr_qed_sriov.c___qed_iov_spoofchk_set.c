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
struct qed_vf_info {int spoof_chk; int req_spoofchk_val; int /*<<< orphan*/  relative_vf_id; int /*<<< orphan*/  vport_id; int /*<<< orphan*/  opaque_fid; } ;
struct qed_sp_vport_update_params {int update_anti_spoofing_en_flg; int anti_spoofing_en; int /*<<< orphan*/  vport_id; int /*<<< orphan*/  opaque_fid; } ;
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  QED_MSG_IOV ; 
 int /*<<< orphan*/  QED_SPQ_MODE_EBLOCK ; 
 int /*<<< orphan*/  memset (struct qed_sp_vport_update_params*,int /*<<< orphan*/ ,int) ; 
 int qed_sp_vport_update (struct qed_hwfn*,struct qed_sp_vport_update_params*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __qed_iov_spoofchk_set(struct qed_hwfn *p_hwfn,
				  struct qed_vf_info *p_vf, bool val)
{
	struct qed_sp_vport_update_params params;
	int rc;

	if (val == p_vf->spoof_chk) {
		DP_VERBOSE(p_hwfn, QED_MSG_IOV,
			   "Spoofchk value[%d] is already configured\n", val);
		return 0;
	}

	memset(&params, 0, sizeof(struct qed_sp_vport_update_params));
	params.opaque_fid = p_vf->opaque_fid;
	params.vport_id = p_vf->vport_id;
	params.update_anti_spoofing_en_flg = 1;
	params.anti_spoofing_en = val;

	rc = qed_sp_vport_update(p_hwfn, &params, QED_SPQ_MODE_EBLOCK, NULL);
	if (!rc) {
		p_vf->spoof_chk = val;
		p_vf->req_spoofchk_val = p_vf->spoof_chk;
		DP_VERBOSE(p_hwfn, QED_MSG_IOV,
			   "Spoofchk val[%d] configured\n", val);
	} else {
		DP_VERBOSE(p_hwfn, QED_MSG_IOV,
			   "Spoofchk configuration[val:%d] failed for VF[%d]\n",
			   val, p_vf->relative_vf_id);
	}

	return rc;
}