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
struct be_phy_info {int /*<<< orphan*/  misc_params; int /*<<< orphan*/  fixed_speeds_supported; int /*<<< orphan*/  auto_speeds_supported; int /*<<< orphan*/  interface_type; int /*<<< orphan*/  phy_type; int /*<<< orphan*/  hdr; } ;
struct be_mcc_wrb {int dummy; } ;
struct be_dma_mem {int size; int /*<<< orphan*/  dma; struct be_phy_info* va; } ;
struct be_cmd_req_hdr {int dummy; } ;
struct be_cmd_req_get_phy_info {int /*<<< orphan*/  misc_params; int /*<<< orphan*/  fixed_speeds_supported; int /*<<< orphan*/  auto_speeds_supported; int /*<<< orphan*/  interface_type; int /*<<< orphan*/  phy_type; int /*<<< orphan*/  hdr; } ;
struct TYPE_3__ {int fixed_speeds_supported; int /*<<< orphan*/  misc_params; void* auto_speeds_supported; void* interface_type; void* phy_type; } ;
struct be_adapter {int /*<<< orphan*/  mcc_lock; TYPE_2__* pdev; TYPE_1__ phy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ BE2_chip (struct be_adapter*) ; 
 int BE_SUPPORTED_SPEED_10GBPS ; 
 int BE_SUPPORTED_SPEED_1GBPS ; 
 int /*<<< orphan*/  CMD_SUBSYSTEM_COMMON ; 
 int EBUSY ; 
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  OPCODE_COMMON_GET_PHY_DETAILS ; 
 int /*<<< orphan*/  be_cmd_allowed (struct be_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int be_mcc_notify_wait (struct be_adapter*) ; 
 int /*<<< orphan*/  be_wrb_cmd_hdr_prepare (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct be_mcc_wrb*,struct be_dma_mem*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct be_phy_info* dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,struct be_phy_info*,int /*<<< orphan*/ ) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct be_mcc_wrb* wrb_from_mccq (struct be_adapter*) ; 

int be_cmd_get_phy_info(struct be_adapter *adapter)
{
	struct be_mcc_wrb *wrb;
	struct be_cmd_req_get_phy_info *req;
	struct be_dma_mem cmd;
	int status;

	if (!be_cmd_allowed(adapter, OPCODE_COMMON_GET_PHY_DETAILS,
			    CMD_SUBSYSTEM_COMMON))
		return -EPERM;

	mutex_lock(&adapter->mcc_lock);

	wrb = wrb_from_mccq(adapter);
	if (!wrb) {
		status = -EBUSY;
		goto err;
	}
	cmd.size = sizeof(struct be_cmd_req_get_phy_info);
	cmd.va = dma_alloc_coherent(&adapter->pdev->dev, cmd.size, &cmd.dma,
				    GFP_ATOMIC);
	if (!cmd.va) {
		dev_err(&adapter->pdev->dev, "Memory alloc failure\n");
		status = -ENOMEM;
		goto err;
	}

	req = cmd.va;

	be_wrb_cmd_hdr_prepare(&req->hdr, CMD_SUBSYSTEM_COMMON,
			       OPCODE_COMMON_GET_PHY_DETAILS, sizeof(*req),
			       wrb, &cmd);

	status = be_mcc_notify_wait(adapter);
	if (!status) {
		struct be_phy_info *resp_phy_info =
				cmd.va + sizeof(struct be_cmd_req_hdr);

		adapter->phy.phy_type = le16_to_cpu(resp_phy_info->phy_type);
		adapter->phy.interface_type =
			le16_to_cpu(resp_phy_info->interface_type);
		adapter->phy.auto_speeds_supported =
			le16_to_cpu(resp_phy_info->auto_speeds_supported);
		adapter->phy.fixed_speeds_supported =
			le16_to_cpu(resp_phy_info->fixed_speeds_supported);
		adapter->phy.misc_params =
			le32_to_cpu(resp_phy_info->misc_params);

		if (BE2_chip(adapter)) {
			adapter->phy.fixed_speeds_supported =
				BE_SUPPORTED_SPEED_10GBPS |
				BE_SUPPORTED_SPEED_1GBPS;
		}
	}
	dma_free_coherent(&adapter->pdev->dev, cmd.size, cmd.va, cmd.dma);
err:
	mutex_unlock(&adapter->mcc_lock);
	return status;
}