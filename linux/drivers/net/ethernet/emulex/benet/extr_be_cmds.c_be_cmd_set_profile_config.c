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
typedef  void* u8 ;
struct be_mcc_wrb {int /*<<< orphan*/  member_0; } ;
struct be_dma_mem {int size; int /*<<< orphan*/  dma; struct be_cmd_req_set_profile_config* va; } ;
struct TYPE_4__ {void* domain; void* version; } ;
struct be_cmd_req_set_profile_config {int /*<<< orphan*/  desc; int /*<<< orphan*/  desc_count; TYPE_2__ hdr; } ;
struct be_adapter {TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SUBSYSTEM_COMMON ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  OPCODE_COMMON_SET_PROFILE_CONFIG ; 
 int be_cmd_notify_wait (struct be_adapter*,struct be_mcc_wrb*) ; 
 int /*<<< orphan*/  be_wrb_cmd_hdr_prepare (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct be_mcc_wrb*,struct be_dma_mem*) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 struct be_cmd_req_set_profile_config* dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,struct be_cmd_req_set_profile_config*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  memset (struct be_dma_mem*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int be_cmd_set_profile_config(struct be_adapter *adapter, void *desc,
				     int size, int count, u8 version, u8 domain)
{
	struct be_cmd_req_set_profile_config *req;
	struct be_mcc_wrb wrb = {0};
	struct be_dma_mem cmd;
	int status;

	memset(&cmd, 0, sizeof(struct be_dma_mem));
	cmd.size = sizeof(struct be_cmd_req_set_profile_config);
	cmd.va = dma_alloc_coherent(&adapter->pdev->dev, cmd.size, &cmd.dma,
				    GFP_ATOMIC);
	if (!cmd.va)
		return -ENOMEM;

	req = cmd.va;
	be_wrb_cmd_hdr_prepare(&req->hdr, CMD_SUBSYSTEM_COMMON,
			       OPCODE_COMMON_SET_PROFILE_CONFIG, cmd.size,
			       &wrb, &cmd);
	req->hdr.version = version;
	req->hdr.domain = domain;
	req->desc_count = cpu_to_le32(count);
	memcpy(req->desc, desc, size);

	status = be_cmd_notify_wait(adapter, &wrb);

	if (cmd.va)
		dma_free_coherent(&adapter->pdev->dev, cmd.size, cmd.va,
				  cmd.dma);
	return status;
}