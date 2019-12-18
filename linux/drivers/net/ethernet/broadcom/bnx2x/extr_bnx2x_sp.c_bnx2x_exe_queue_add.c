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
struct bnx2x_exeq_elem {int /*<<< orphan*/  link; } ;
struct bnx2x_exe_queue_obj {int (* optimize ) (struct bnx2x*,int /*<<< orphan*/ ,struct bnx2x_exeq_elem*) ;int (* validate ) (struct bnx2x*,int /*<<< orphan*/ ,struct bnx2x_exeq_elem*) ;int /*<<< orphan*/  lock; int /*<<< orphan*/  exe_queue; int /*<<< orphan*/  owner; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_MSG_SP ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  bnx2x_exe_queue_free_elem (struct bnx2x*,struct bnx2x_exeq_elem*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int stub1 (struct bnx2x*,int /*<<< orphan*/ ,struct bnx2x_exeq_elem*) ; 
 int stub2 (struct bnx2x*,int /*<<< orphan*/ ,struct bnx2x_exeq_elem*) ; 

__attribute__((used)) static inline int bnx2x_exe_queue_add(struct bnx2x *bp,
				      struct bnx2x_exe_queue_obj *o,
				      struct bnx2x_exeq_elem *elem,
				      bool restore)
{
	int rc;

	spin_lock_bh(&o->lock);

	if (!restore) {
		/* Try to cancel this element queue */
		rc = o->optimize(bp, o->owner, elem);
		if (rc)
			goto free_and_exit;

		/* Check if this request is ok */
		rc = o->validate(bp, o->owner, elem);
		if (rc) {
			DP(BNX2X_MSG_SP, "Preamble failed: %d\n", rc);
			goto free_and_exit;
		}
	}

	/* If so, add it to the execution queue */
	list_add_tail(&elem->link, &o->exe_queue);

	spin_unlock_bh(&o->lock);

	return 0;

free_and_exit:
	bnx2x_exe_queue_free_elem(bp, elem);

	spin_unlock_bh(&o->lock);

	return rc;
}