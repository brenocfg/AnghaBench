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
struct qed_vf_info {int dummy; } ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
 int qed_iov_vf_flr_poll_dorq (struct qed_hwfn*,struct qed_vf_info*,struct qed_ptt*) ; 
 int qed_iov_vf_flr_poll_pbf (struct qed_hwfn*,struct qed_vf_info*,struct qed_ptt*) ; 

__attribute__((used)) static int qed_iov_vf_flr_poll(struct qed_hwfn *p_hwfn,
			       struct qed_vf_info *p_vf, struct qed_ptt *p_ptt)
{
	int rc;

	rc = qed_iov_vf_flr_poll_dorq(p_hwfn, p_vf, p_ptt);
	if (rc)
		return rc;

	rc = qed_iov_vf_flr_poll_pbf(p_hwfn, p_vf, p_ptt);
	if (rc)
		return rc;

	return 0;
}