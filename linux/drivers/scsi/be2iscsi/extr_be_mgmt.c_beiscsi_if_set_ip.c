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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct beiscsi_hba {int /*<<< orphan*/  interface_handle; } ;
struct be_ip_addr_subnet_format {int dummy; } ;
struct be_dma_mem {struct be_cmd_set_ip_addr_req* va; } ;
struct TYPE_4__ {int size_of_structure; int /*<<< orphan*/  subnet_mask; int /*<<< orphan*/  addr; scalar_t__ ip_type; } ;
struct TYPE_5__ {scalar_t__ status; TYPE_1__ ip_addr; int /*<<< orphan*/  interface_hndl; int /*<<< orphan*/  action; } ;
struct TYPE_6__ {int record_entry_count; TYPE_2__ ip_record; } ;
struct be_cmd_set_ip_addr_req {TYPE_3__ ip_params; } ;

/* Variables and functions */
 scalar_t__ BEISCSI_IP_TYPE_V6 ; 
 int /*<<< orphan*/  CMD_SUBSYSTEM_ISCSI ; 
 int EINVAL ; 
 int /*<<< orphan*/  IP_ACTION_ADD ; 
 int /*<<< orphan*/  IP_V4_LEN ; 
 int /*<<< orphan*/  IP_V6_LEN ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  OPCODE_COMMON_ISCSI_NTWK_MODIFY_IP_ADDR ; 
 int /*<<< orphan*/  __beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,char*,int,scalar_t__) ; 
 int beiscsi_exec_nemb_cmd (struct beiscsi_hba*,struct be_dma_mem*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int beiscsi_prep_nemb_cmd (struct beiscsi_hba*,struct be_dma_mem*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
beiscsi_if_set_ip(struct beiscsi_hba *phba, u8 *ip,
		  u8 *subnet, u32 ip_type)
{
	struct be_cmd_set_ip_addr_req *req;
	struct be_dma_mem nonemb_cmd;
	uint32_t ip_len;
	int rc;

	rc = beiscsi_prep_nemb_cmd(phba, &nonemb_cmd, CMD_SUBSYSTEM_ISCSI,
			OPCODE_COMMON_ISCSI_NTWK_MODIFY_IP_ADDR,
			sizeof(*req));
	if (rc)
		return rc;

	req = nonemb_cmd.va;
	req->ip_params.record_entry_count = 1;
	req->ip_params.ip_record.action = IP_ACTION_ADD;
	req->ip_params.ip_record.interface_hndl =
		phba->interface_handle;
	req->ip_params.ip_record.ip_addr.size_of_structure =
		sizeof(struct be_ip_addr_subnet_format);
	req->ip_params.ip_record.ip_addr.ip_type = ip_type;
	ip_len = (ip_type < BEISCSI_IP_TYPE_V6) ? IP_V4_LEN : IP_V6_LEN;
	memcpy(req->ip_params.ip_record.ip_addr.addr, ip, ip_len);
	if (subnet)
		memcpy(req->ip_params.ip_record.ip_addr.subnet_mask,
		       subnet, ip_len);

	rc = beiscsi_exec_nemb_cmd(phba, &nonemb_cmd, NULL, NULL, 0);
	/**
	 * In some cases, host needs to look into individual record status
	 * even though FW reported success for that IOCTL.
	 */
	if (rc < 0 || req->ip_params.ip_record.status) {
		__beiscsi_log(phba, KERN_ERR,
			    "BG_%d : failed to set IP: rc %d status %d\n",
			    rc, req->ip_params.ip_record.status);
		if (req->ip_params.ip_record.status)
			rc = -EINVAL;
	}
	return rc;
}