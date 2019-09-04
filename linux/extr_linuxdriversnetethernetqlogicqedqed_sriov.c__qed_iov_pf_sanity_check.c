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
struct qed_hwfn {int /*<<< orphan*/  cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_PF_SRIOV_ALLOC (struct qed_hwfn*) ; 
 int /*<<< orphan*/  IS_QED_SRIOV (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_VF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_iov_is_valid_vfid (struct qed_hwfn*,int,int,int) ; 

__attribute__((used)) static bool _qed_iov_pf_sanity_check(struct qed_hwfn *p_hwfn,
				     int vfid, bool b_fail_malicious)
{
	/* Check PF supports sriov */
	if (IS_VF(p_hwfn->cdev) || !IS_QED_SRIOV(p_hwfn->cdev) ||
	    !IS_PF_SRIOV_ALLOC(p_hwfn))
		return false;

	/* Check VF validity */
	if (!qed_iov_is_valid_vfid(p_hwfn, vfid, true, b_fail_malicious))
		return false;

	return true;
}