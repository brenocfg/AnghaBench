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
typedef  scalar_t__ u64 ;
struct se_session {TYPE_2__* se_tpg; struct se_node_acl* se_node_acl; } ;
struct se_node_acl {int dummy; } ;
struct se_lun {int /*<<< orphan*/  lun_se_dev; int /*<<< orphan*/  lun_ref; } ;
struct se_dev_entry {scalar_t__ lun_access_ro; int /*<<< orphan*/  pr_res_key; int /*<<< orphan*/  se_lun; int /*<<< orphan*/  read_bytes; int /*<<< orphan*/  write_bytes; int /*<<< orphan*/  total_cmds; } ;
struct se_cmd {scalar_t__ data_direction; int lun_ref_active; TYPE_3__* se_dev; int /*<<< orphan*/  data_length; int /*<<< orphan*/  se_cmd_flags; scalar_t__ orig_fe_lun; struct se_lun* se_lun; TYPE_1__* se_tfo; int /*<<< orphan*/  pr_res_key; struct se_session* se_sess; } ;
typedef  int /*<<< orphan*/  sense_reason_t ;
struct TYPE_6__ {int /*<<< orphan*/  read_bytes; int /*<<< orphan*/  write_bytes; int /*<<< orphan*/  num_cmds; } ;
struct TYPE_5__ {struct se_lun* tpg_virt_lun0; } ;
struct TYPE_4__ {int /*<<< orphan*/  fabric_name; } ;

/* Variables and functions */
 scalar_t__ DMA_FROM_DEVICE ; 
 scalar_t__ DMA_NONE ; 
 scalar_t__ DMA_TO_DEVICE ; 
 int /*<<< orphan*/  SCF_SE_LUN_CMD ; 
 int /*<<< orphan*/  TCM_NON_EXISTENT_LUN ; 
 int /*<<< orphan*/  TCM_NO_SENSE ; 
 int /*<<< orphan*/  TCM_WRITE_PROTECTED ; 
 int /*<<< orphan*/  atomic_long_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_long_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_ref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_ref_tryget_live (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct se_lun* rcu_dereference (int /*<<< orphan*/ ) ; 
 TYPE_3__* rcu_dereference_raw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct se_dev_entry* target_nacl_find_deve (struct se_node_acl*,scalar_t__) ; 

sense_reason_t
transport_lookup_cmd_lun(struct se_cmd *se_cmd, u64 unpacked_lun)
{
	struct se_lun *se_lun = NULL;
	struct se_session *se_sess = se_cmd->se_sess;
	struct se_node_acl *nacl = se_sess->se_node_acl;
	struct se_dev_entry *deve;
	sense_reason_t ret = TCM_NO_SENSE;

	rcu_read_lock();
	deve = target_nacl_find_deve(nacl, unpacked_lun);
	if (deve) {
		atomic_long_inc(&deve->total_cmds);

		if (se_cmd->data_direction == DMA_TO_DEVICE)
			atomic_long_add(se_cmd->data_length,
					&deve->write_bytes);
		else if (se_cmd->data_direction == DMA_FROM_DEVICE)
			atomic_long_add(se_cmd->data_length,
					&deve->read_bytes);

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

		if ((se_cmd->data_direction == DMA_TO_DEVICE) &&
		    deve->lun_access_ro) {
			pr_err("TARGET_CORE[%s]: Detected WRITE_PROTECTED LUN"
				" Access for 0x%08llx\n",
				se_cmd->se_tfo->fabric_name,
				unpacked_lun);
			rcu_read_unlock();
			ret = TCM_WRITE_PROTECTED;
			goto ref_dev;
		}
	}
out_unlock:
	rcu_read_unlock();

	if (!se_lun) {
		/*
		 * Use the se_portal_group->tpg_virt_lun0 to allow for
		 * REPORT_LUNS, et al to be returned when no active
		 * MappedLUN=0 exists for this Initiator Port.
		 */
		if (unpacked_lun != 0) {
			pr_err("TARGET_CORE[%s]: Detected NON_EXISTENT_LUN"
				" Access for 0x%08llx\n",
				se_cmd->se_tfo->fabric_name,
				unpacked_lun);
			return TCM_NON_EXISTENT_LUN;
		}

		se_lun = se_sess->se_tpg->tpg_virt_lun0;
		se_cmd->se_lun = se_sess->se_tpg->tpg_virt_lun0;
		se_cmd->orig_fe_lun = 0;
		se_cmd->se_cmd_flags |= SCF_SE_LUN_CMD;

		percpu_ref_get(&se_lun->lun_ref);
		se_cmd->lun_ref_active = true;

		/*
		 * Force WRITE PROTECT for virtual LUN 0
		 */
		if ((se_cmd->data_direction != DMA_FROM_DEVICE) &&
		    (se_cmd->data_direction != DMA_NONE)) {
			ret = TCM_WRITE_PROTECTED;
			goto ref_dev;
		}
	}
	/*
	 * RCU reference protected by percpu se_lun->lun_ref taken above that
	 * must drop to zero (including initial reference) before this se_lun
	 * pointer can be kfree_rcu() by the final se_lun->lun_group put via
	 * target_core_fabric_configfs.c:target_fabric_port_release
	 */
ref_dev:
	se_cmd->se_dev = rcu_dereference_raw(se_lun->lun_se_dev);
	atomic_long_inc(&se_cmd->se_dev->num_cmds);

	if (se_cmd->data_direction == DMA_TO_DEVICE)
		atomic_long_add(se_cmd->data_length,
				&se_cmd->se_dev->write_bytes);
	else if (se_cmd->data_direction == DMA_FROM_DEVICE)
		atomic_long_add(se_cmd->data_length,
				&se_cmd->se_dev->read_bytes);

	return ret;
}