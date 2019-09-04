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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct TYPE_4__ {int b_pending_msg; } ;
struct qed_vf_info {int abs_vf_id; scalar_t__ state; TYPE_2__ vf_mbx; int /*<<< orphan*/  b_init; } ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {TYPE_1__* pf_iov_info; } ;
struct TYPE_3__ {unsigned long long* pending_flr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  DP_ERR (struct qed_hwfn*,char*,int) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ GTT_BAR0_MAP_REG_USDM_RAM ; 
 int /*<<< orphan*/  QED_MSG_IOV ; 
 int /*<<< orphan*/  REG_WR (struct qed_hwfn*,scalar_t__,int) ; 
 scalar_t__ USTORM_VF_PF_CHANNEL_READY_OFFSET (int) ; 
 scalar_t__ VF_RESET ; 
 void* VF_STOPPED ; 
 int qed_final_cleanup (struct qed_hwfn*,struct qed_ptt*,int,int) ; 
 int qed_iov_enable_vf_access (struct qed_hwfn*,struct qed_ptt*,struct qed_vf_info*) ; 
 struct qed_vf_info* qed_iov_get_vf_info (struct qed_hwfn*,int,int) ; 
 int /*<<< orphan*/  qed_iov_vf_cleanup (struct qed_hwfn*,struct qed_vf_info*) ; 
 int qed_iov_vf_flr_poll (struct qed_hwfn*,struct qed_vf_info*,struct qed_ptt*) ; 

__attribute__((used)) static int
qed_iov_execute_vf_flr_cleanup(struct qed_hwfn *p_hwfn,
			       struct qed_ptt *p_ptt,
			       u16 rel_vf_id, u32 *ack_vfs)
{
	struct qed_vf_info *p_vf;
	int rc = 0;

	p_vf = qed_iov_get_vf_info(p_hwfn, rel_vf_id, false);
	if (!p_vf)
		return 0;

	if (p_hwfn->pf_iov_info->pending_flr[rel_vf_id / 64] &
	    (1ULL << (rel_vf_id % 64))) {
		u16 vfid = p_vf->abs_vf_id;

		DP_VERBOSE(p_hwfn, QED_MSG_IOV,
			   "VF[%d] - Handling FLR\n", vfid);

		qed_iov_vf_cleanup(p_hwfn, p_vf);

		/* If VF isn't active, no need for anything but SW */
		if (!p_vf->b_init)
			goto cleanup;

		rc = qed_iov_vf_flr_poll(p_hwfn, p_vf, p_ptt);
		if (rc)
			goto cleanup;

		rc = qed_final_cleanup(p_hwfn, p_ptt, vfid, true);
		if (rc) {
			DP_ERR(p_hwfn, "Failed handle FLR of VF[%d]\n", vfid);
			return rc;
		}

		/* Workaround to make VF-PF channel ready, as FW
		 * doesn't do that as a part of FLR.
		 */
		REG_WR(p_hwfn,
		       GTT_BAR0_MAP_REG_USDM_RAM +
		       USTORM_VF_PF_CHANNEL_READY_OFFSET(vfid), 1);

		/* VF_STOPPED has to be set only after final cleanup
		 * but prior to re-enabling the VF.
		 */
		p_vf->state = VF_STOPPED;

		rc = qed_iov_enable_vf_access(p_hwfn, p_ptt, p_vf);
		if (rc) {
			DP_ERR(p_hwfn, "Failed to re-enable VF[%d] acces\n",
			       vfid);
			return rc;
		}
cleanup:
		/* Mark VF for ack and clean pending state */
		if (p_vf->state == VF_RESET)
			p_vf->state = VF_STOPPED;
		ack_vfs[vfid / 32] |= BIT((vfid % 32));
		p_hwfn->pf_iov_info->pending_flr[rel_vf_id / 64] &=
		    ~(1ULL << (rel_vf_id % 64));
		p_vf->vf_mbx.b_pending_msg = false;
	}

	return rc;
}