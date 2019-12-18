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
typedef  int /*<<< orphan*/  u8 ;
struct iscsi_tiqn {int /*<<< orphan*/  tiqn; int /*<<< orphan*/  tiqn_tpg_lock; int /*<<< orphan*/  tiqn_ntpgs; } ;
struct iscsi_portal_group {int /*<<< orphan*/  tpgt; int /*<<< orphan*/  tpg_list; int /*<<< orphan*/  tpg_state_lock; int /*<<< orphan*/  tpg_state; int /*<<< orphan*/  tpg_se_tpg; int /*<<< orphan*/ * param_list; } ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  TPG_STATE_FREE ; 
 int /*<<< orphan*/  TPG_STATE_INACTIVE ; 
 int /*<<< orphan*/  core_tpg_deregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iscsi_release_param_list (int /*<<< orphan*/ *) ; 
 scalar_t__ iscsit_release_sessions_for_tpg (struct iscsi_portal_group*,int) ; 
 int /*<<< orphan*/  kfree (struct iscsi_portal_group*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int iscsit_tpg_del_portal_group(
	struct iscsi_tiqn *tiqn,
	struct iscsi_portal_group *tpg,
	int force)
{
	u8 old_state = tpg->tpg_state;

	spin_lock(&tpg->tpg_state_lock);
	tpg->tpg_state = TPG_STATE_INACTIVE;
	spin_unlock(&tpg->tpg_state_lock);

	if (iscsit_release_sessions_for_tpg(tpg, force) < 0) {
		pr_err("Unable to delete iSCSI Target Portal Group:"
			" %hu while active sessions exist, and force=0\n",
			tpg->tpgt);
		tpg->tpg_state = old_state;
		return -EPERM;
	}

	if (tpg->param_list) {
		iscsi_release_param_list(tpg->param_list);
		tpg->param_list = NULL;
	}

	core_tpg_deregister(&tpg->tpg_se_tpg);

	spin_lock(&tpg->tpg_state_lock);
	tpg->tpg_state = TPG_STATE_FREE;
	spin_unlock(&tpg->tpg_state_lock);

	spin_lock(&tiqn->tiqn_tpg_lock);
	tiqn->tiqn_ntpgs--;
	list_del(&tpg->tpg_list);
	spin_unlock(&tiqn->tiqn_tpg_lock);

	pr_debug("CORE[%s]_TPG[%hu] - Deleted iSCSI Target Portal Group\n",
			tiqn->tiqn, tpg->tpgt);

	kfree(tpg);
	return 0;
}