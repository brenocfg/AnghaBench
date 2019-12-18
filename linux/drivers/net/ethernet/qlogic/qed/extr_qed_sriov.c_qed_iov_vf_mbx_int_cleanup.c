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
struct qed_vf_info {int num_sbs; int /*<<< orphan*/  opaque_fid; int /*<<< orphan*/ * igu_sbs; } ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int dummy; } ;
struct pfvf_def_resp_tlv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHANNEL_TLV_INT_CLEANUP ; 
 int /*<<< orphan*/  PFVF_STATUS_SUCCESS ; 
 int /*<<< orphan*/  qed_int_igu_init_pure_rt_single (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qed_iov_prepare_resp (struct qed_hwfn*,struct qed_ptt*,struct qed_vf_info*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qed_iov_vf_mbx_int_cleanup(struct qed_hwfn *p_hwfn,
				       struct qed_ptt *p_ptt,
				       struct qed_vf_info *vf)
{
	int i;

	/* Reset the SBs */
	for (i = 0; i < vf->num_sbs; i++)
		qed_int_igu_init_pure_rt_single(p_hwfn, p_ptt,
						vf->igu_sbs[i],
						vf->opaque_fid, false);

	qed_iov_prepare_resp(p_hwfn, p_ptt, vf, CHANNEL_TLV_INT_CLEANUP,
			     sizeof(struct pfvf_def_resp_tlv),
			     PFVF_STATUS_SUCCESS);
}