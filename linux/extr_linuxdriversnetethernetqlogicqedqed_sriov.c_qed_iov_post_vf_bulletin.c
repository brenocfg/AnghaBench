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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int size; int /*<<< orphan*/  phys; struct qed_bulletin_content* p_virt; } ;
struct qed_vf_info {TYPE_1__ bulletin; int /*<<< orphan*/  vf_bulletin; int /*<<< orphan*/  abs_vf_id; int /*<<< orphan*/  relative_vf_id; } ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int dummy; } ;
struct qed_dmae_params {int /*<<< orphan*/  dst_vfid; int /*<<< orphan*/  flags; } ;
struct qed_bulletin_content {int /*<<< orphan*/  crc; int /*<<< orphan*/  version; } ;
typedef  int /*<<< orphan*/  params ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  QED_DMAE_FLAG_VF_DST ; 
 int /*<<< orphan*/  QED_MSG_IOV ; 
 int /*<<< orphan*/  crc32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct qed_dmae_params*,int /*<<< orphan*/ ,int) ; 
 int qed_dmae_host2host (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct qed_dmae_params*) ; 
 struct qed_vf_info* qed_iov_get_vf_info (struct qed_hwfn*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int qed_iov_post_vf_bulletin(struct qed_hwfn *p_hwfn,
				    int vfid, struct qed_ptt *p_ptt)
{
	struct qed_bulletin_content *p_bulletin;
	int crc_size = sizeof(p_bulletin->crc);
	struct qed_dmae_params params;
	struct qed_vf_info *p_vf;

	p_vf = qed_iov_get_vf_info(p_hwfn, (u16) vfid, true);
	if (!p_vf)
		return -EINVAL;

	if (!p_vf->vf_bulletin)
		return -EINVAL;

	p_bulletin = p_vf->bulletin.p_virt;

	/* Increment bulletin board version and compute crc */
	p_bulletin->version++;
	p_bulletin->crc = crc32(0, (u8 *)p_bulletin + crc_size,
				p_vf->bulletin.size - crc_size);

	DP_VERBOSE(p_hwfn, QED_MSG_IOV,
		   "Posting Bulletin 0x%08x to VF[%d] (CRC 0x%08x)\n",
		   p_bulletin->version, p_vf->relative_vf_id, p_bulletin->crc);

	/* propagate bulletin board via dmae to vm memory */
	memset(&params, 0, sizeof(params));
	params.flags = QED_DMAE_FLAG_VF_DST;
	params.dst_vfid = p_vf->abs_vf_id;
	return qed_dmae_host2host(p_hwfn, p_ptt, p_vf->bulletin.phys,
				  p_vf->vf_bulletin, p_vf->bulletin.size / 4,
				  &params);
}