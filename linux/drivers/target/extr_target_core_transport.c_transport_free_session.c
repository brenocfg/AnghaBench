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
struct target_core_fabric_ops {int /*<<< orphan*/  (* tpg_check_demo_mode_cache ) (struct se_portal_group*) ;} ;
struct se_session {int /*<<< orphan*/  cmd_count; scalar_t__ sess_cmd_map; int /*<<< orphan*/  sess_tag_pool; struct se_node_acl* se_node_acl; } ;
struct se_portal_group {int /*<<< orphan*/  acl_node_mutex; struct target_core_fabric_ops* se_tpg_tfo; } ;
struct se_node_acl {int dynamic_stop; int /*<<< orphan*/  acl_list; int /*<<< orphan*/  nacl_sess_lock; int /*<<< orphan*/  acl_sess_list; scalar_t__ dynamic_node_acl; struct se_portal_group* se_tpg; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct se_session*) ; 
 int /*<<< orphan*/  kvfree (scalar_t__) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_ref_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sbitmap_queue_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  se_sess_cache ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct se_portal_group*) ; 
 int /*<<< orphan*/  target_put_nacl (struct se_node_acl*) ; 

void transport_free_session(struct se_session *se_sess)
{
	struct se_node_acl *se_nacl = se_sess->se_node_acl;

	/*
	 * Drop the se_node_acl->nacl_kref obtained from within
	 * core_tpg_get_initiator_node_acl().
	 */
	if (se_nacl) {
		struct se_portal_group *se_tpg = se_nacl->se_tpg;
		const struct target_core_fabric_ops *se_tfo = se_tpg->se_tpg_tfo;
		unsigned long flags;

		se_sess->se_node_acl = NULL;

		/*
		 * Also determine if we need to drop the extra ->cmd_kref if
		 * it had been previously dynamically generated, and
		 * the endpoint is not caching dynamic ACLs.
		 */
		mutex_lock(&se_tpg->acl_node_mutex);
		if (se_nacl->dynamic_node_acl &&
		    !se_tfo->tpg_check_demo_mode_cache(se_tpg)) {
			spin_lock_irqsave(&se_nacl->nacl_sess_lock, flags);
			if (list_empty(&se_nacl->acl_sess_list))
				se_nacl->dynamic_stop = true;
			spin_unlock_irqrestore(&se_nacl->nacl_sess_lock, flags);

			if (se_nacl->dynamic_stop)
				list_del_init(&se_nacl->acl_list);
		}
		mutex_unlock(&se_tpg->acl_node_mutex);

		if (se_nacl->dynamic_stop)
			target_put_nacl(se_nacl);

		target_put_nacl(se_nacl);
	}
	if (se_sess->sess_cmd_map) {
		sbitmap_queue_free(&se_sess->sess_tag_pool);
		kvfree(se_sess->sess_cmd_map);
	}
	percpu_ref_exit(&se_sess->cmd_count);
	kmem_cache_free(se_sess_cache, se_sess);
}