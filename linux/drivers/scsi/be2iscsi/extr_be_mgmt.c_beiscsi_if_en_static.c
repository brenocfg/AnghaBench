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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct beiscsi_hba {int /*<<< orphan*/  interface_handle; } ;
struct be_dma_mem {struct be_cmd_rel_dhcp_req* va; } ;
struct be_cmd_rel_dhcp_req {int /*<<< orphan*/  ip_type; int /*<<< orphan*/  interface_hndl; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;
struct be_cmd_get_if_info_resp {TYPE_1__ ip_addr; scalar_t__ dhcp_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEISCSI_LOG_CONFIG ; 
 int /*<<< orphan*/  CMD_SUBSYSTEM_ISCSI ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  OPCODE_COMMON_ISCSI_NTWK_REL_STATELESS_IP_ADDR ; 
 int beiscsi_exec_nemb_cmd (struct beiscsi_hba*,struct be_dma_mem*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int beiscsi_if_clr_ip (struct beiscsi_hba*,struct be_cmd_get_if_info_resp*) ; 
 int beiscsi_if_get_info (struct beiscsi_hba*,int /*<<< orphan*/ ,struct be_cmd_get_if_info_resp**) ; 
 int beiscsi_if_set_ip (struct beiscsi_hba*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  beiscsi_if_zero_ip (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int beiscsi_prep_nemb_cmd (struct beiscsi_hba*,struct be_dma_mem*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (struct be_cmd_get_if_info_resp*) ; 

int beiscsi_if_en_static(struct beiscsi_hba *phba, u32 ip_type,
			 u8 *ip, u8 *subnet)
{
	struct be_cmd_get_if_info_resp *if_info;
	struct be_cmd_rel_dhcp_req *reldhcp;
	struct be_dma_mem nonemb_cmd;
	int rc;

	rc = beiscsi_if_get_info(phba, ip_type, &if_info);
	if (rc)
		return rc;

	if (if_info->dhcp_state) {
		rc = beiscsi_prep_nemb_cmd(phba, &nonemb_cmd,
				CMD_SUBSYSTEM_ISCSI,
				OPCODE_COMMON_ISCSI_NTWK_REL_STATELESS_IP_ADDR,
				sizeof(*reldhcp));
		if (rc)
			goto exit;

		reldhcp = nonemb_cmd.va;
		reldhcp->interface_hndl = phba->interface_handle;
		reldhcp->ip_type = ip_type;
		rc = beiscsi_exec_nemb_cmd(phba, &nonemb_cmd, NULL, NULL, 0);
		if (rc < 0) {
			beiscsi_log(phba, KERN_WARNING, BEISCSI_LOG_CONFIG,
				    "BG_%d : failed to release existing DHCP: %d\n",
				    rc);
			goto exit;
		}
	}

	/* first delete any IP set */
	if (!beiscsi_if_zero_ip(if_info->ip_addr.addr, ip_type)) {
		rc = beiscsi_if_clr_ip(phba, if_info);
		if (rc)
			goto exit;
	}

	/* if ip == NULL then this is called just to release DHCP IP */
	if (ip)
		rc = beiscsi_if_set_ip(phba, ip, subnet, ip_type);
exit:
	kfree(if_info);
	return rc;
}