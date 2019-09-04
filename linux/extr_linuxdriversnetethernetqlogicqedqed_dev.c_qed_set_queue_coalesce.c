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
typedef  void* u16 ;
struct qed_queue_cid {struct qed_hwfn* p_owner; } ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {TYPE_1__* cdev; } ;
struct TYPE_2__ {void* tx_coalesce_usecs; void* rx_coalesce_usecs; } ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ IS_VF (TYPE_1__*) ; 
 struct qed_ptt* qed_ptt_acquire (struct qed_hwfn*) ; 
 int /*<<< orphan*/  qed_ptt_release (struct qed_hwfn*,struct qed_ptt*) ; 
 int qed_set_rxq_coalesce (struct qed_hwfn*,struct qed_ptt*,void*,struct qed_queue_cid*) ; 
 int qed_set_txq_coalesce (struct qed_hwfn*,struct qed_ptt*,void*,struct qed_queue_cid*) ; 
 int qed_vf_pf_set_coalesce (struct qed_hwfn*,void*,void*,struct qed_queue_cid*) ; 

int qed_set_queue_coalesce(u16 rx_coal, u16 tx_coal, void *p_handle)
{
	struct qed_queue_cid *p_cid = p_handle;
	struct qed_hwfn *p_hwfn;
	struct qed_ptt *p_ptt;
	int rc = 0;

	p_hwfn = p_cid->p_owner;

	if (IS_VF(p_hwfn->cdev))
		return qed_vf_pf_set_coalesce(p_hwfn, rx_coal, tx_coal, p_cid);

	p_ptt = qed_ptt_acquire(p_hwfn);
	if (!p_ptt)
		return -EAGAIN;

	if (rx_coal) {
		rc = qed_set_rxq_coalesce(p_hwfn, p_ptt, rx_coal, p_cid);
		if (rc)
			goto out;
		p_hwfn->cdev->rx_coalesce_usecs = rx_coal;
	}

	if (tx_coal) {
		rc = qed_set_txq_coalesce(p_hwfn, p_ptt, tx_coal, p_cid);
		if (rc)
			goto out;
		p_hwfn->cdev->tx_coalesce_usecs = tx_coal;
	}
out:
	qed_ptt_release(p_hwfn, p_ptt);
	return rc;
}