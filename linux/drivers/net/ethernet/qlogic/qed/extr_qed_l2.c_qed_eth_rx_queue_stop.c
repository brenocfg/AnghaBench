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
 int EINVAL ; 
 scalar_t__ IS_PF (int /*<<< orphan*/ ) ; 
 int qed_eth_pf_rx_queue_stop (struct qed_hwfn*,struct qed_queue_cid*,int,int) ; 
 int /*<<< orphan*/  qed_eth_queue_cid_release (struct qed_hwfn*,struct qed_queue_cid*) ; 
 int qed_vf_pf_rxq_stop (struct qed_hwfn*,struct qed_queue_cid*,int) ; 

int qed_eth_rx_queue_stop(struct qed_hwfn *p_hwfn,
			  void *p_rxq,
			  bool eq_completion_only, bool cqe_completion)
{
	struct qed_queue_cid *p_cid = (struct qed_queue_cid *)p_rxq;
	int rc = -EINVAL;

	if (IS_PF(p_hwfn->cdev))
		rc = qed_eth_pf_rx_queue_stop(p_hwfn, p_cid,
					      eq_completion_only,
					      cqe_completion);
	else
		rc = qed_vf_pf_rxq_stop(p_hwfn, p_cid, cqe_completion);

	if (!rc)
		qed_eth_queue_cid_release(p_hwfn, p_cid);
	return rc;
}