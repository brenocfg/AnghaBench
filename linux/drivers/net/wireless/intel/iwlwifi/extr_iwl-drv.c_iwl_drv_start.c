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
struct iwl_trans {void* dbgfs_dir; int /*<<< orphan*/  dev; } ;
struct iwl_drv {struct iwl_trans* trans; void* dbgfs_drv; int /*<<< orphan*/  list; int /*<<< orphan*/  request_firmware_complete; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct iwl_drv* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_trans*,char*) ; 
 void* debugfs_create_dir (char*,void*) ; 
 int /*<<< orphan*/  debugfs_remove_recursive (void*) ; 
 char* dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_dbg_tlv_free (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_dbg_tlv_load_bin (int /*<<< orphan*/ ,struct iwl_trans*) ; 
 void* iwl_dbgfs_root ; 
 int iwl_request_firmware (struct iwl_drv*,int) ; 
 int /*<<< orphan*/  kfree (struct iwl_drv*) ; 
 struct iwl_drv* kzalloc (int,int /*<<< orphan*/ ) ; 

struct iwl_drv *iwl_drv_start(struct iwl_trans *trans)
{
	struct iwl_drv *drv;
	int ret;

	drv = kzalloc(sizeof(*drv), GFP_KERNEL);
	if (!drv) {
		ret = -ENOMEM;
		goto err;
	}

	drv->trans = trans;
	drv->dev = trans->dev;

	init_completion(&drv->request_firmware_complete);
	INIT_LIST_HEAD(&drv->list);

	iwl_dbg_tlv_load_bin(drv->trans->dev, drv->trans);

#ifdef CONFIG_IWLWIFI_DEBUGFS
	/* Create the device debugfs entries. */
	drv->dbgfs_drv = debugfs_create_dir(dev_name(trans->dev),
					    iwl_dbgfs_root);

	/* Create transport layer debugfs dir */
	drv->trans->dbgfs_dir = debugfs_create_dir("trans", drv->dbgfs_drv);
#endif

	ret = iwl_request_firmware(drv, true);
	if (ret) {
		IWL_ERR(trans, "Couldn't request the fw\n");
		goto err_fw;
	}

	return drv;

err_fw:
#ifdef CONFIG_IWLWIFI_DEBUGFS
	debugfs_remove_recursive(drv->dbgfs_drv);
	iwl_dbg_tlv_free(drv->trans);
#endif
	kfree(drv);
err:
	return ERR_PTR(ret);
}