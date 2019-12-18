#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct beiscsi_hba {int /*<<< orphan*/  interface_handle; } ;
struct be_ip_addr_subnet_format {int dummy; } ;
struct be_dma_mem {struct be_cmd_set_ip_addr_req* va; } ;
struct TYPE_5__ {int size_of_structure; int /*<<< orphan*/  subnet_mask; int /*<<< orphan*/  addr; int /*<<< orphan*/  ip_type; } ;
struct TYPE_7__ {scalar_t__ status; TYPE_1__ ip_addr; int /*<<< orphan*/  interface_hndl; int /*<<< orphan*/  action; } ;
struct TYPE_8__ {int record_entry_count; TYPE_3__ ip_record; } ;
struct be_cmd_set_ip_addr_req {TYPE_4__ ip_params; } ;
struct TYPE_6__ {int /*<<< orphan*/  subnet_mask; int /*<<< orphan*/  addr; int /*<<< orphan*/  ip_type; } ;
struct be_cmd_get_if_info_resp {TYPE_2__ ip_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEISCSI_LOG_CONFIG ; 
 int /*<<< orphan*/  CMD_SUBSYSTEM_ISCSI ; 
 int /*<<< orphan*/  IP_ACTION_DEL ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  OPCODE_COMMON_ISCSI_NTWK_MODIFY_IP_ADDR ; 
 int beiscsi_exec_nemb_cmd (struct beiscsi_hba*,struct be_dma_mem*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,scalar_t__) ; 
 int beiscsi_prep_nemb_cmd (struct beiscsi_hba*,struct be_dma_mem*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
beiscsi_if_clr_ip(struct beiscsi_hba *phba,
		  struct be_cmd_get_if_info_resp *if_info)
{
	struct be_cmd_set_ip_addr_req *req;
	struct be_dma_mem nonemb_cmd;
	int rc;

	rc = beiscsi_prep_nemb_cmd(phba, &nonemb_cmd, CMD_SUBSYSTEM_ISCSI,
			OPCODE_COMMON_ISCSI_NTWK_MODIFY_IP_ADDR,
			sizeof(*req));
	if (rc)
		return rc;

	req = nonemb_cmd.va;
	req->ip_params.record_entry_count = 1;
	req->ip_params.ip_record.action = IP_ACTION_DEL;
	req->ip_params.ip_record.interface_hndl =
		phba->interface_handle;
	req->ip_params.ip_record.ip_addr.size_of_structure =
		sizeof(struct be_ip_addr_subnet_format);
	req->ip_params.ip_record.ip_addr.ip_type = if_info->ip_addr.ip_type;
	memcpy(req->ip_params.ip_record.ip_addr.addr,
	       if_info->ip_addr.addr,
	       sizeof(if_info->ip_addr.addr));
	memcpy(req->ip_params.ip_record.ip_addr.subnet_mask,
	       if_info->ip_addr.subnet_mask,
	       sizeof(if_info->ip_addr.subnet_mask));
	rc = beiscsi_exec_nemb_cmd(phba, &nonemb_cmd, NULL, NULL, 0);
	if (rc < 0 || req->ip_params.ip_record.status) {
		beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_CONFIG,
			    "BG_%d : failed to clear IP: rc %d status %d\n",
			    rc, req->ip_params.ip_record.status);
	}
	return rc;
}