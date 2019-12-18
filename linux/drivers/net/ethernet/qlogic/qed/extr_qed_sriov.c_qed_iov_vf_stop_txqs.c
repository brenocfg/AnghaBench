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
typedef  size_t u8 ;
typedef  size_t u16 ;
struct qed_vf_queue {TYPE_1__* cids; } ;
struct qed_vf_info {struct qed_vf_queue* vf_queues; } ;
struct qed_hwfn {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * p_cid; int /*<<< orphan*/  b_is_tx; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  QED_IOV_VALIDATE_Q_NA ; 
 int qed_eth_tx_queue_stop (struct qed_hwfn*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qed_iov_validate_txq (struct qed_hwfn*,struct qed_vf_info*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qed_iov_vf_stop_txqs(struct qed_hwfn *p_hwfn,
				struct qed_vf_info *vf,
				u16 txq_id, u8 qid_usage_idx)
{
	struct qed_vf_queue *p_queue;
	int rc = 0;

	if (!qed_iov_validate_txq(p_hwfn, vf, txq_id, QED_IOV_VALIDATE_Q_NA))
		return -EINVAL;

	p_queue = &vf->vf_queues[txq_id];
	if (!p_queue->cids[qid_usage_idx].p_cid ||
	    !p_queue->cids[qid_usage_idx].b_is_tx)
		return -EINVAL;

	rc = qed_eth_tx_queue_stop(p_hwfn, p_queue->cids[qid_usage_idx].p_cid);
	if (rc)
		return rc;

	p_queue->cids[qid_usage_idx].p_cid = NULL;
	return 0;
}