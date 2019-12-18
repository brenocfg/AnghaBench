#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct se_tmr_req {TYPE_2__* tmr_dev; int /*<<< orphan*/  tmr_list; } ;
struct se_session {struct se_node_acl* se_node_acl; } ;
struct se_node_acl {int dummy; } ;
struct se_lun {int /*<<< orphan*/  lun_se_dev; int /*<<< orphan*/  lun_ref; } ;
struct se_dev_entry {int /*<<< orphan*/  pr_res_key; int /*<<< orphan*/  se_lun; } ;
struct se_cmd {int lun_ref_active; void* se_dev; TYPE_1__* se_tfo; int /*<<< orphan*/  se_cmd_flags; int /*<<< orphan*/  orig_fe_lun; int /*<<< orphan*/  pr_res_key; struct se_lun* se_lun; struct se_tmr_req* se_tmr_req; struct se_session* se_sess; } ;
struct TYPE_4__ {int /*<<< orphan*/  se_tmr_lock; int /*<<< orphan*/  dev_tmr_list; } ;
struct TYPE_3__ {int /*<<< orphan*/  fabric_name; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  SCF_SE_LUN_CMD ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_ref_tryget_live (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct se_lun* rcu_dereference (int /*<<< orphan*/ ) ; 
 void* rcu_dereference_raw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct se_dev_entry* target_nacl_find_deve (struct se_node_acl*,int /*<<< orphan*/ ) ; 

int transport_lookup_tmr_lun(struct se_cmd *se_cmd, u64 unpacked_lun)
{
	struct se_dev_entry *deve;
	struct se_lun *se_lun = NULL;
	struct se_session *se_sess = se_cmd->se_sess;
	struct se_node_acl *nacl = se_sess->se_node_acl;
	struct se_tmr_req *se_tmr = se_cmd->se_tmr_req;
	unsigned long flags;

	rcu_read_lock();
	deve = target_nacl_find_deve(nacl, unpacked_lun);
	if (deve) {
		se_lun = rcu_dereference(deve->se_lun);

		if (!percpu_ref_tryget_live(&se_lun->lun_ref)) {
			se_lun = NULL;
			goto out_unlock;
		}

		se_cmd->se_lun = se_lun;
		se_cmd->pr_res_key = deve->pr_res_key;
		se_cmd->orig_fe_lun = unpacked_lun;
		se_cmd->se_cmd_flags |= SCF_SE_LUN_CMD;
		se_cmd->lun_ref_active = true;
	}
out_unlock:
	rcu_read_unlock();

	if (!se_lun) {
		pr_debug("TARGET_CORE[%s]: Detected NON_EXISTENT_LUN"
			" Access for 0x%08llx\n",
			se_cmd->se_tfo->fabric_name,
			unpacked_lun);
		return -ENODEV;
	}
	se_cmd->se_dev = rcu_dereference_raw(se_lun->lun_se_dev);
	se_tmr->tmr_dev = rcu_dereference_raw(se_lun->lun_se_dev);

	spin_lock_irqsave(&se_tmr->tmr_dev->se_tmr_lock, flags);
	list_add_tail(&se_tmr->tmr_list, &se_tmr->tmr_dev->dev_tmr_list);
	spin_unlock_irqrestore(&se_tmr->tmr_dev->se_tmr_lock, flags);

	return 0;
}