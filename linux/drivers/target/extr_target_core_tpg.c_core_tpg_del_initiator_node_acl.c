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
struct se_portal_group {TYPE_1__* se_tpg_tfo; int /*<<< orphan*/  acl_node_mutex; } ;
struct se_node_acl {int /*<<< orphan*/  initiatorname; int /*<<< orphan*/  queue_depth; int /*<<< orphan*/  acl_free_comp; int /*<<< orphan*/  acl_list; scalar_t__ dynamic_node_acl; struct se_portal_group* se_tpg; } ;
struct TYPE_2__ {int /*<<< orphan*/  fabric_name; int /*<<< orphan*/  (* tpg_get_tag ) (struct se_portal_group*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  core_free_device_list_for_node (struct se_node_acl*,struct se_portal_group*) ; 
 int /*<<< orphan*/  core_tpg_wait_for_nacl_pr_ref (struct se_node_acl*) ; 
 int /*<<< orphan*/  kfree (struct se_node_acl*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct se_portal_group*) ; 
 int /*<<< orphan*/  target_put_nacl (struct se_node_acl*) ; 
 int /*<<< orphan*/  target_shutdown_sessions (struct se_node_acl*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

void core_tpg_del_initiator_node_acl(struct se_node_acl *acl)
{
	struct se_portal_group *tpg = acl->se_tpg;

	mutex_lock(&tpg->acl_node_mutex);
	if (acl->dynamic_node_acl)
		acl->dynamic_node_acl = 0;
	list_del_init(&acl->acl_list);
	mutex_unlock(&tpg->acl_node_mutex);

	target_shutdown_sessions(acl);

	target_put_nacl(acl);
	/*
	 * Wait for last target_put_nacl() to complete in target_complete_nacl()
	 * for active fabric session transport_deregister_session() callbacks.
	 */
	wait_for_completion(&acl->acl_free_comp);

	core_tpg_wait_for_nacl_pr_ref(acl);
	core_free_device_list_for_node(acl, tpg);

	pr_debug("%s_TPG[%hu] - Deleted ACL with TCQ Depth: %d for %s"
		" Initiator Node: %s\n", tpg->se_tpg_tfo->fabric_name,
		tpg->se_tpg_tfo->tpg_get_tag(tpg), acl->queue_depth,
		tpg->se_tpg_tfo->fabric_name, acl->initiatorname);

	kfree(acl);
}