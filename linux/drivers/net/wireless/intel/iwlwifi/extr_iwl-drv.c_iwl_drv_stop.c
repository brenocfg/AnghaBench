#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct iwl_drv {TYPE_2__* trans; int /*<<< orphan*/  dbgfs_drv; int /*<<< orphan*/  list; int /*<<< orphan*/  request_firmware_complete; } ;
struct TYPE_5__ {TYPE_1__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* debugfs_cleanup ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  _iwl_op_mode_stop (struct iwl_drv*) ; 
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_dbg_tlv_free (TYPE_2__*) ; 
 int /*<<< orphan*/  iwl_dealloc_ucode (struct iwl_drv*) ; 
 int /*<<< orphan*/  iwlwifi_opmode_table_mtx ; 
 int /*<<< orphan*/  kfree (struct iwl_drv*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

void iwl_drv_stop(struct iwl_drv *drv)
{
	wait_for_completion(&drv->request_firmware_complete);

	_iwl_op_mode_stop(drv);

	iwl_dealloc_ucode(drv);

	mutex_lock(&iwlwifi_opmode_table_mtx);
	/*
	 * List is empty (this item wasn't added)
	 * when firmware loading failed -- in that
	 * case we can't remove it from any list.
	 */
	if (!list_empty(&drv->list))
		list_del(&drv->list);
	mutex_unlock(&iwlwifi_opmode_table_mtx);

#ifdef CONFIG_IWLWIFI_DEBUGFS
	drv->trans->ops->debugfs_cleanup(drv->trans);

	debugfs_remove_recursive(drv->dbgfs_drv);
#endif

	iwl_dbg_tlv_free(drv->trans);

	kfree(drv);
}