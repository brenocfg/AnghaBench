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
struct iscsi_tiqn {int /*<<< orphan*/  tiqn; int /*<<< orphan*/  tiqn_index; int /*<<< orphan*/  tiqn_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ iscsit_set_tiqn_shutdown (struct iscsi_tiqn*) ; 
 int /*<<< orphan*/  iscsit_wait_for_tiqn (struct iscsi_tiqn*) ; 
 int /*<<< orphan*/  kfree (struct iscsi_tiqn*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tiqn_idr ; 
 int /*<<< orphan*/  tiqn_lock ; 

void iscsit_del_tiqn(struct iscsi_tiqn *tiqn)
{
	/*
	 * iscsit_set_tiqn_shutdown sets tiqn->tiqn_state = TIQN_STATE_SHUTDOWN
	 * while holding tiqn->tiqn_state_lock.  This means that all subsequent
	 * attempts to access this struct iscsi_tiqn will fail from both transport
	 * fabric and control code paths.
	 */
	if (iscsit_set_tiqn_shutdown(tiqn) < 0) {
		pr_err("iscsit_set_tiqn_shutdown() failed\n");
		return;
	}

	iscsit_wait_for_tiqn(tiqn);

	spin_lock(&tiqn_lock);
	list_del(&tiqn->tiqn_list);
	idr_remove(&tiqn_idr, tiqn->tiqn_index);
	spin_unlock(&tiqn_lock);

	pr_debug("CORE[0] - Deleted iSCSI Target IQN: %s\n",
			tiqn->tiqn);
	kfree(tiqn);
}