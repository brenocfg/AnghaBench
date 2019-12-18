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
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PROTOCOLID_IWARP ; 
 int /*<<< orphan*/  qed_iwarp_free_prealloc_ep (struct qed_hwfn*) ; 
 int qed_iwarp_ll2_stop (struct qed_hwfn*) ; 
 int qed_iwarp_wait_for_all_cids (struct qed_hwfn*) ; 
 int /*<<< orphan*/  qed_spq_unregister_async_cb (struct qed_hwfn*,int /*<<< orphan*/ ) ; 

int qed_iwarp_stop(struct qed_hwfn *p_hwfn)
{
	int rc;

	qed_iwarp_free_prealloc_ep(p_hwfn);
	rc = qed_iwarp_wait_for_all_cids(p_hwfn);
	if (rc)
		return rc;

	qed_spq_unregister_async_cb(p_hwfn, PROTOCOLID_IWARP);

	return qed_iwarp_ll2_stop(p_hwfn);
}