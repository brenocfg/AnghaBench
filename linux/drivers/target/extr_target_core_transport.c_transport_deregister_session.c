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
struct se_session {int /*<<< orphan*/ * fabric_sess_ptr; struct se_portal_group* se_tpg; int /*<<< orphan*/  sess_list; } ;
struct se_portal_group {TYPE_1__* se_tpg_tfo; int /*<<< orphan*/  session_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  fabric_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  transport_free_session (struct se_session*) ; 

void transport_deregister_session(struct se_session *se_sess)
{
	struct se_portal_group *se_tpg = se_sess->se_tpg;
	unsigned long flags;

	if (!se_tpg) {
		transport_free_session(se_sess);
		return;
	}

	spin_lock_irqsave(&se_tpg->session_lock, flags);
	list_del(&se_sess->sess_list);
	se_sess->se_tpg = NULL;
	se_sess->fabric_sess_ptr = NULL;
	spin_unlock_irqrestore(&se_tpg->session_lock, flags);

	pr_debug("TARGET_CORE[%s]: Deregistered fabric_sess\n",
		se_tpg->se_tpg_tfo->fabric_name);
	/*
	 * If last kref is dropping now for an explicit NodeACL, awake sleeping
	 * ->acl_free_comp caller to wakeup configfs se_node_acl->acl_group
	 * removal context from within transport_free_session() code.
	 *
	 * For dynamic ACL, target_put_nacl() uses target_complete_nacl()
	 * to release all remaining generate_node_acl=1 created ACL resources.
	 */

	transport_free_session(se_sess);
}