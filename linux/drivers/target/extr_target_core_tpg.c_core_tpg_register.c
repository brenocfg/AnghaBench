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
struct se_wwn {TYPE_1__* wwn_tf; } ;
struct se_portal_group {int proto_id; TYPE_2__* se_tpg_tfo; int /*<<< orphan*/  se_tpg_node; int /*<<< orphan*/  tpg_virt_lun0; int /*<<< orphan*/  acl_node_mutex; int /*<<< orphan*/  tpg_lun_mutex; int /*<<< orphan*/  session_lock; int /*<<< orphan*/  tpg_sess_list; int /*<<< orphan*/  acl_node_list; int /*<<< orphan*/  tpg_pr_ref_count; struct se_wwn* se_tpg_wwn; int /*<<< orphan*/  tpg_lun_hlist; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* tpg_get_tag ) (struct se_portal_group*) ;int /*<<< orphan*/ * (* tpg_get_wwn ) (struct se_portal_group*) ;int /*<<< orphan*/  fabric_name; } ;
struct TYPE_3__ {TYPE_2__* tf_ops; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int core_tpg_add_lun (struct se_portal_group*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  core_tpg_alloc_lun (struct se_portal_group*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_lun0_dev ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub1 (struct se_portal_group*) ; 
 int /*<<< orphan*/ * stub2 (struct se_portal_group*) ; 
 int /*<<< orphan*/  stub3 (struct se_portal_group*) ; 
 int /*<<< orphan*/  tpg_list ; 
 int /*<<< orphan*/  tpg_lock ; 

int core_tpg_register(
	struct se_wwn *se_wwn,
	struct se_portal_group *se_tpg,
	int proto_id)
{
	int ret;

	if (!se_tpg)
		return -EINVAL;
	/*
	 * For the typical case where core_tpg_register() is called by a
	 * fabric driver from target_core_fabric_ops->fabric_make_tpg()
	 * configfs context, use the original tf_ops pointer already saved
	 * by target-core in target_fabric_make_wwn().
	 *
	 * Otherwise, for special cases like iscsi-target discovery TPGs
	 * the caller is responsible for setting ->se_tpg_tfo ahead of
	 * calling core_tpg_register().
	 */
	if (se_wwn)
		se_tpg->se_tpg_tfo = se_wwn->wwn_tf->tf_ops;

	if (!se_tpg->se_tpg_tfo) {
		pr_err("Unable to locate se_tpg->se_tpg_tfo pointer\n");
		return -EINVAL;
	}

	INIT_HLIST_HEAD(&se_tpg->tpg_lun_hlist);
	se_tpg->proto_id = proto_id;
	se_tpg->se_tpg_wwn = se_wwn;
	atomic_set(&se_tpg->tpg_pr_ref_count, 0);
	INIT_LIST_HEAD(&se_tpg->acl_node_list);
	INIT_LIST_HEAD(&se_tpg->se_tpg_node);
	INIT_LIST_HEAD(&se_tpg->tpg_sess_list);
	spin_lock_init(&se_tpg->session_lock);
	mutex_init(&se_tpg->tpg_lun_mutex);
	mutex_init(&se_tpg->acl_node_mutex);

	if (se_tpg->proto_id >= 0) {
		se_tpg->tpg_virt_lun0 = core_tpg_alloc_lun(se_tpg, 0);
		if (IS_ERR(se_tpg->tpg_virt_lun0))
			return PTR_ERR(se_tpg->tpg_virt_lun0);

		ret = core_tpg_add_lun(se_tpg, se_tpg->tpg_virt_lun0,
				true, g_lun0_dev);
		if (ret < 0) {
			kfree(se_tpg->tpg_virt_lun0);
			return ret;
		}
	}

	spin_lock_bh(&tpg_lock);
	list_add_tail(&se_tpg->se_tpg_node, &tpg_list);
	spin_unlock_bh(&tpg_lock);

	pr_debug("TARGET_CORE[%s]: Allocated portal_group for endpoint: %s, "
		 "Proto: %d, Portal Tag: %u\n", se_tpg->se_tpg_tfo->fabric_name,
		se_tpg->se_tpg_tfo->tpg_get_wwn(se_tpg) ?
		se_tpg->se_tpg_tfo->tpg_get_wwn(se_tpg) : NULL,
		se_tpg->proto_id, se_tpg->se_tpg_tfo->tpg_get_tag(se_tpg));

	return 0;
}