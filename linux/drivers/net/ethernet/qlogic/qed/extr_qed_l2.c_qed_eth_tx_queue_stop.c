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
struct qed_queue_cid {int dummy; } ;
struct qed_hwfn {int /*<<< orphan*/  cdev; } ;

/* Variables and functions */
 scalar_t__ IS_PF (int /*<<< orphan*/ ) ; 
 int qed_eth_pf_tx_queue_stop (struct qed_hwfn*,struct qed_queue_cid*) ; 
 int /*<<< orphan*/  qed_eth_queue_cid_release (struct qed_hwfn*,struct qed_queue_cid*) ; 
 int qed_vf_pf_txq_stop (struct qed_hwfn*,struct qed_queue_cid*) ; 

int qed_eth_tx_queue_stop(struct qed_hwfn *p_hwfn, void *p_handle)
{
	struct qed_queue_cid *p_cid = (struct qed_queue_cid *)p_handle;
	int rc;

	if (IS_PF(p_hwfn->cdev))
		rc = qed_eth_pf_tx_queue_stop(p_hwfn, p_cid);
	else
		rc = qed_vf_pf_txq_stop(p_hwfn, p_cid);

	if (!rc)
		qed_eth_queue_cid_release(p_hwfn, p_cid);
	return rc;
}