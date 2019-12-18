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
struct se_portal_group {int dummy; } ;
struct se_node_acl {int /*<<< orphan*/  lun_entry_mutex; } ;
struct se_lun {int /*<<< orphan*/  lun_deve_lock; int /*<<< orphan*/  lun_se_dev; } ;
struct se_device {int dummy; } ;
struct se_dev_entry {int lun_access_ro; int /*<<< orphan*/  se_lun_acl; int /*<<< orphan*/  se_lun; int /*<<< orphan*/  pr_comp; int /*<<< orphan*/  pr_kref; int /*<<< orphan*/  attach_count; scalar_t__ creation_time; int /*<<< orphan*/  deve_flags; int /*<<< orphan*/  link; int /*<<< orphan*/  lun_link; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEF_PR_REG_ACTIVE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  core_scsi3_free_pr_reg_from_nacl (struct se_device*,struct se_node_acl*) ; 
 int /*<<< orphan*/  core_scsi3_ua_release_all (struct se_dev_entry*) ; 
 int /*<<< orphan*/  hlist_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_rcu (struct se_dev_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct se_device* rcu_dereference_raw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_head ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  target_luns_data_has_changed (struct se_node_acl*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  target_pr_kref_release ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

void core_disable_device_list_for_node(
	struct se_lun *lun,
	struct se_dev_entry *orig,
	struct se_node_acl *nacl,
	struct se_portal_group *tpg)
{
	/*
	 * rcu_dereference_raw protected by se_lun->lun_group symlink
	 * reference to se_device->dev_group.
	 */
	struct se_device *dev = rcu_dereference_raw(lun->lun_se_dev);

	lockdep_assert_held(&nacl->lun_entry_mutex);

	/*
	 * If the MappedLUN entry is being disabled, the entry in
	 * lun->lun_deve_list must be removed now before clearing the
	 * struct se_dev_entry pointers below as logic in
	 * core_alua_do_transition_tg_pt() depends on these being present.
	 *
	 * deve->se_lun_acl will be NULL for demo-mode created LUNs
	 * that have not been explicitly converted to MappedLUNs ->
	 * struct se_lun_acl, but we remove deve->lun_link from
	 * lun->lun_deve_list. This also means that active UAs and
	 * NodeACL context specific PR metadata for demo-mode
	 * MappedLUN *deve will be released below..
	 */
	spin_lock(&lun->lun_deve_lock);
	list_del(&orig->lun_link);
	spin_unlock(&lun->lun_deve_lock);
	/*
	 * Disable struct se_dev_entry LUN ACL mapping
	 */
	core_scsi3_ua_release_all(orig);

	hlist_del_rcu(&orig->link);
	clear_bit(DEF_PR_REG_ACTIVE, &orig->deve_flags);
	orig->lun_access_ro = false;
	orig->creation_time = 0;
	orig->attach_count--;
	/*
	 * Before firing off RCU callback, wait for any in process SPEC_I_PT=1
	 * or REGISTER_AND_MOVE PR operation to complete.
	 */
	kref_put(&orig->pr_kref, target_pr_kref_release);
	wait_for_completion(&orig->pr_comp);

	rcu_assign_pointer(orig->se_lun, NULL);
	rcu_assign_pointer(orig->se_lun_acl, NULL);

	kfree_rcu(orig, rcu_head);

	core_scsi3_free_pr_reg_from_nacl(dev, nacl);
	target_luns_data_has_changed(nacl, NULL, false);
}