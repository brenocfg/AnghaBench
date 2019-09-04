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
struct be_mcc_wrb {int dummy; } ;
struct be_cmd_resp_query_fw_cfg {int /*<<< orphan*/  asic_revision; int /*<<< orphan*/  function_caps; int /*<<< orphan*/  function_mode; int /*<<< orphan*/  phys_port; } ;
struct be_cmd_req_query_fw_cfg {int /*<<< orphan*/  hdr; } ;
struct be_adapter {int port_num; int function_mode; int function_caps; int asic_rev; int /*<<< orphan*/  mbox_lock; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SUBSYSTEM_COMMON ; 
 int /*<<< orphan*/  OPCODE_COMMON_QUERY_FIRMWARE_CONFIG ; 
 int be_mbox_notify_wait (struct be_adapter*) ; 
 int /*<<< orphan*/  be_wrb_cmd_hdr_prepare (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct be_mcc_wrb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,int) ; 
 void* embedded_payload (struct be_mcc_wrb*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct be_mcc_wrb* wrb_from_mbox (struct be_adapter*) ; 

int be_cmd_query_fw_cfg(struct be_adapter *adapter)
{
	struct be_mcc_wrb *wrb;
	struct be_cmd_req_query_fw_cfg *req;
	int status;

	if (mutex_lock_interruptible(&adapter->mbox_lock))
		return -1;

	wrb = wrb_from_mbox(adapter);
	req = embedded_payload(wrb);

	be_wrb_cmd_hdr_prepare(&req->hdr, CMD_SUBSYSTEM_COMMON,
			       OPCODE_COMMON_QUERY_FIRMWARE_CONFIG,
			       sizeof(*req), wrb, NULL);

	status = be_mbox_notify_wait(adapter);
	if (!status) {
		struct be_cmd_resp_query_fw_cfg *resp = embedded_payload(wrb);

		adapter->port_num = le32_to_cpu(resp->phys_port);
		adapter->function_mode = le32_to_cpu(resp->function_mode);
		adapter->function_caps = le32_to_cpu(resp->function_caps);
		adapter->asic_rev = le32_to_cpu(resp->asic_revision) & 0xFF;
		dev_info(&adapter->pdev->dev,
			 "FW config: function_mode=0x%x, function_caps=0x%x\n",
			 adapter->function_mode, adapter->function_caps);
	}

	mutex_unlock(&adapter->mbox_lock);
	return status;
}