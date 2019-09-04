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
struct qed_hwfn {int /*<<< orphan*/  pf_iov_info; } ;

/* Variables and functions */
 scalar_t__ IS_PF_SRIOV_ALLOC (struct qed_hwfn*) ; 
 int /*<<< orphan*/  PROTOCOLID_COMMON ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_iov_free_vfdb (struct qed_hwfn*) ; 
 int /*<<< orphan*/  qed_spq_unregister_async_cb (struct qed_hwfn*,int /*<<< orphan*/ ) ; 

void qed_iov_free(struct qed_hwfn *p_hwfn)
{
	qed_spq_unregister_async_cb(p_hwfn, PROTOCOLID_COMMON);

	if (IS_PF_SRIOV_ALLOC(p_hwfn)) {
		qed_iov_free_vfdb(p_hwfn);
		kfree(p_hwfn->pf_iov_info);
	}
}