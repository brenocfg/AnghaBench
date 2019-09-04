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
struct qed_pf_iov {int dummy; } ;
struct qed_hwfn {struct qed_pf_iov* pf_iov_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_PF_SRIOV (struct qed_hwfn*) ; 
 int /*<<< orphan*/  PROTOCOLID_COMMON ; 
 int /*<<< orphan*/  QED_MSG_IOV ; 
 struct qed_pf_iov* kzalloc (int,int /*<<< orphan*/ ) ; 
 int qed_iov_allocate_vfdb (struct qed_hwfn*) ; 
 int /*<<< orphan*/  qed_spq_register_async_cb (struct qed_hwfn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_sriov_eqe_event ; 

int qed_iov_alloc(struct qed_hwfn *p_hwfn)
{
	struct qed_pf_iov *p_sriov;

	if (!IS_PF_SRIOV(p_hwfn)) {
		DP_VERBOSE(p_hwfn, QED_MSG_IOV,
			   "No SR-IOV - no need for IOV db\n");
		return 0;
	}

	p_sriov = kzalloc(sizeof(*p_sriov), GFP_KERNEL);
	if (!p_sriov)
		return -ENOMEM;

	p_hwfn->pf_iov_info = p_sriov;

	qed_spq_register_async_cb(p_hwfn, PROTOCOLID_COMMON,
				  qed_sriov_eqe_event);

	return qed_iov_allocate_vfdb(p_hwfn);
}