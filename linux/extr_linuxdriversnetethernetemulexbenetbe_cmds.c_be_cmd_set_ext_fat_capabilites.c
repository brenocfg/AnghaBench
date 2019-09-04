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
struct be_mcc_wrb {int dummy; } ;
struct be_fat_conf_params {int dummy; } ;
struct be_dma_mem {int /*<<< orphan*/  size; struct be_cmd_req_set_ext_fat_caps* va; } ;
struct be_cmd_req_set_ext_fat_caps {int /*<<< orphan*/  hdr; int /*<<< orphan*/  set_params; } ;
struct be_adapter {int /*<<< orphan*/  mcc_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SUBSYSTEM_COMMON ; 
 int EBUSY ; 
 int /*<<< orphan*/  OPCODE_COMMON_SET_EXT_FAT_CAPABILITIES ; 
 int be_mcc_notify_wait (struct be_adapter*) ; 
 int /*<<< orphan*/  be_wrb_cmd_hdr_prepare (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct be_mcc_wrb*,struct be_dma_mem*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct be_fat_conf_params*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct be_mcc_wrb* wrb_from_mccq (struct be_adapter*) ; 

int be_cmd_set_ext_fat_capabilites(struct be_adapter *adapter,
				   struct be_dma_mem *cmd,
				   struct be_fat_conf_params *configs)
{
	struct be_mcc_wrb *wrb;
	struct be_cmd_req_set_ext_fat_caps *req;
	int status;

	mutex_lock(&adapter->mcc_lock);

	wrb = wrb_from_mccq(adapter);
	if (!wrb) {
		status = -EBUSY;
		goto err;
	}

	req = cmd->va;
	memcpy(&req->set_params, configs, sizeof(struct be_fat_conf_params));
	be_wrb_cmd_hdr_prepare(&req->hdr, CMD_SUBSYSTEM_COMMON,
			       OPCODE_COMMON_SET_EXT_FAT_CAPABILITIES,
			       cmd->size, wrb, cmd);

	status = be_mcc_notify_wait(adapter);
err:
	mutex_unlock(&adapter->mcc_lock);
	return status;
}