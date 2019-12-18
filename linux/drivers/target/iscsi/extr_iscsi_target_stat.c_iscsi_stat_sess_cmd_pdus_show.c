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
struct se_session {struct iscsi_session* fabric_sess_ptr; } ;
struct se_node_acl {int /*<<< orphan*/  nacl_sess_lock; struct se_session* nacl_sess; } ;
struct iscsi_session {int /*<<< orphan*/  cmd_pdus; } ;
struct iscsi_node_acl {struct se_node_acl se_node_acl; } ;
struct config_item {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  atomic_long_read (int /*<<< orphan*/ *) ; 
 struct iscsi_node_acl* iscsi_stat_nacl (struct config_item*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t iscsi_stat_sess_cmd_pdus_show(struct config_item *item,
		char *page)
{
	struct iscsi_node_acl *acl = iscsi_stat_nacl(item);
	struct se_node_acl *se_nacl = &acl->se_node_acl;
	struct iscsi_session *sess;
	struct se_session *se_sess;
	ssize_t ret = 0;

	spin_lock_bh(&se_nacl->nacl_sess_lock);
	se_sess = se_nacl->nacl_sess;
	if (se_sess) {
		sess = se_sess->fabric_sess_ptr;
		if (sess)
			ret = snprintf(page, PAGE_SIZE, "%lu\n",
				       atomic_long_read(&sess->cmd_pdus));
	}
	spin_unlock_bh(&se_nacl->nacl_sess_lock);

	return ret;
}