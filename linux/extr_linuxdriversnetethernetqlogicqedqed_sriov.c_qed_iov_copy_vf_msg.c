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
typedef  union vfpf_tlvs {int dummy; } vfpf_tlvs ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  req_phys; int /*<<< orphan*/  pending_req; } ;
struct qed_vf_info {TYPE_1__ vf_mbx; int /*<<< orphan*/  abs_vf_id; } ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int dummy; } ;
struct qed_dmae_params {int flags; int /*<<< orphan*/  src_vfid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,int) ; 
 int EINVAL ; 
 int EIO ; 
 int QED_DMAE_FLAG_COMPLETION_DST ; 
 int QED_DMAE_FLAG_VF_SRC ; 
 int /*<<< orphan*/  QED_MSG_IOV ; 
 int /*<<< orphan*/  memset (struct qed_dmae_params*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ qed_dmae_host2host (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct qed_dmae_params*) ; 
 struct qed_vf_info* qed_iov_get_vf_info (struct qed_hwfn*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int qed_iov_copy_vf_msg(struct qed_hwfn *p_hwfn, struct qed_ptt *ptt,
			       int vfid)
{
	struct qed_dmae_params params;
	struct qed_vf_info *vf_info;

	vf_info = qed_iov_get_vf_info(p_hwfn, (u16) vfid, true);
	if (!vf_info)
		return -EINVAL;

	memset(&params, 0, sizeof(struct qed_dmae_params));
	params.flags = QED_DMAE_FLAG_VF_SRC | QED_DMAE_FLAG_COMPLETION_DST;
	params.src_vfid = vf_info->abs_vf_id;

	if (qed_dmae_host2host(p_hwfn, ptt,
			       vf_info->vf_mbx.pending_req,
			       vf_info->vf_mbx.req_phys,
			       sizeof(union vfpf_tlvs) / 4, &params)) {
		DP_VERBOSE(p_hwfn, QED_MSG_IOV,
			   "Failed to copy message from VF 0x%02x\n", vfid);

		return -EIO;
	}

	return 0;
}