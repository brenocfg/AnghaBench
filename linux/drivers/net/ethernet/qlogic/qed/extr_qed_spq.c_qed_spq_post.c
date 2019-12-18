#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_5__ {int /*<<< orphan*/  echo; int /*<<< orphan*/  protocol_id; int /*<<< orphan*/  cmd_id; } ;
struct TYPE_6__ {TYPE_2__ hdr; } ;
struct qed_spq_entry {scalar_t__ comp_mode; TYPE_3__ elem; int /*<<< orphan*/  list; struct qed_spq_entry* post_ent; int /*<<< orphan*/ * queue; int /*<<< orphan*/  priority; } ;
struct qed_spq {int /*<<< orphan*/  lock; int /*<<< orphan*/  unlimited_pending; } ;
struct qed_hwfn {TYPE_1__* cdev; struct qed_spq* p_spq; } ;
struct TYPE_4__ {scalar_t__ recov_in_prog; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  QED_MSG_SPQ ; 
 scalar_t__ QED_SPQ_MODE_EBLOCK ; 
 int /*<<< orphan*/  __qed_spq_return_entry (struct qed_hwfn*,struct qed_spq_entry*) ; 
 int /*<<< orphan*/  kfree (struct qed_spq_entry*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int qed_spq_add_entry (struct qed_hwfn*,struct qed_spq_entry*,int /*<<< orphan*/ ) ; 
 int qed_spq_block (struct qed_hwfn*,struct qed_spq_entry*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  qed_spq_comp_bmap_update (struct qed_hwfn*,int /*<<< orphan*/ ) ; 
 int qed_spq_fill_entry (struct qed_hwfn*,struct qed_spq_entry*) ; 
 int qed_spq_pend_post (struct qed_hwfn*) ; 
 int /*<<< orphan*/  qed_spq_recov_set_ret_code (struct qed_spq_entry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qed_spq_return_entry (struct qed_hwfn*,struct qed_spq_entry*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int qed_spq_post(struct qed_hwfn *p_hwfn,
		 struct qed_spq_entry *p_ent, u8 *fw_return_code)
{
	int rc = 0;
	struct qed_spq *p_spq = p_hwfn ? p_hwfn->p_spq : NULL;
	bool b_ret_ent = true;
	bool eblock;

	if (!p_hwfn)
		return -EINVAL;

	if (!p_ent) {
		DP_NOTICE(p_hwfn, "Got a NULL pointer\n");
		return -EINVAL;
	}

	if (p_hwfn->cdev->recov_in_prog) {
		DP_VERBOSE(p_hwfn,
			   QED_MSG_SPQ,
			   "Recovery is in progress. Skip spq post [cmd %02x protocol %02x]\n",
			   p_ent->elem.hdr.cmd_id, p_ent->elem.hdr.protocol_id);

		/* Let the flow complete w/o any error handling */
		qed_spq_recov_set_ret_code(p_ent, fw_return_code);
		return 0;
	}

	/* Complete the entry */
	rc = qed_spq_fill_entry(p_hwfn, p_ent);

	spin_lock_bh(&p_spq->lock);

	/* Check return value after LOCK is taken for cleaner error flow */
	if (rc)
		goto spq_post_fail;

	/* Check if entry is in block mode before qed_spq_add_entry,
	 * which might kfree p_ent.
	 */
	eblock = (p_ent->comp_mode == QED_SPQ_MODE_EBLOCK);

	/* Add the request to the pending queue */
	rc = qed_spq_add_entry(p_hwfn, p_ent, p_ent->priority);
	if (rc)
		goto spq_post_fail;

	rc = qed_spq_pend_post(p_hwfn);
	if (rc) {
		/* Since it's possible that pending failed for a different
		 * entry [although unlikely], the failed entry was already
		 * dealt with; No need to return it here.
		 */
		b_ret_ent = false;
		goto spq_post_fail;
	}

	spin_unlock_bh(&p_spq->lock);

	if (eblock) {
		/* For entries in QED BLOCK mode, the completion code cannot
		 * perform the necessary cleanup - if it did, we couldn't
		 * access p_ent here to see whether it's successful or not.
		 * Thus, after gaining the answer perform the cleanup here.
		 */
		rc = qed_spq_block(p_hwfn, p_ent, fw_return_code,
				   p_ent->queue == &p_spq->unlimited_pending);

		if (p_ent->queue == &p_spq->unlimited_pending) {
			struct qed_spq_entry *p_post_ent = p_ent->post_ent;

			kfree(p_ent);

			/* Return the entry which was actually posted */
			p_ent = p_post_ent;
		}

		if (rc)
			goto spq_post_fail2;

		/* return to pool */
		qed_spq_return_entry(p_hwfn, p_ent);
	}
	return rc;

spq_post_fail2:
	spin_lock_bh(&p_spq->lock);
	list_del(&p_ent->list);
	qed_spq_comp_bmap_update(p_hwfn, p_ent->elem.hdr.echo);

spq_post_fail:
	/* return to the free pool */
	if (b_ret_ent)
		__qed_spq_return_entry(p_hwfn, p_ent);
	spin_unlock_bh(&p_spq->lock);

	return rc;
}