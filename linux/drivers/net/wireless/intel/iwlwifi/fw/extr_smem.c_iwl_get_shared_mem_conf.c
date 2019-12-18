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
struct iwl_rx_packet {int dummy; } ;
struct iwl_host_cmd {struct iwl_rx_packet* resp_pkt; int /*<<< orphan*/  id; int /*<<< orphan*/  len; int /*<<< orphan*/  data; int /*<<< orphan*/  flags; } ;
struct iwl_fw_runtime {TYPE_3__* trans; TYPE_1__* fw; } ;
struct TYPE_6__ {TYPE_2__* trans_cfg; } ;
struct TYPE_5__ {scalar_t__ device_family; } ;
struct TYPE_4__ {int /*<<< orphan*/  ucode_capa; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_WANT_SKB ; 
 int ERFKILL ; 
 int /*<<< orphan*/  IWL_DEBUG_INFO (struct iwl_fw_runtime*,char*) ; 
 scalar_t__ IWL_DEVICE_FAMILY_22000 ; 
 int /*<<< orphan*/  IWL_UCODE_TLV_CAPA_EXTEND_SHARED_MEM_CFG ; 
 int /*<<< orphan*/  SHARED_MEM_CFG ; 
 int /*<<< orphan*/  SHARED_MEM_CFG_CMD ; 
 int /*<<< orphan*/  SYSTEM_GROUP ; 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 scalar_t__ fw_has_capa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_cmd_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_free_resp (struct iwl_host_cmd*) ; 
 int /*<<< orphan*/  iwl_parse_shared_mem (struct iwl_fw_runtime*,struct iwl_rx_packet*) ; 
 int /*<<< orphan*/  iwl_parse_shared_mem_22000 (struct iwl_fw_runtime*,struct iwl_rx_packet*) ; 
 int iwl_trans_send_cmd (TYPE_3__*,struct iwl_host_cmd*) ; 

void iwl_get_shared_mem_conf(struct iwl_fw_runtime *fwrt)
{
	struct iwl_host_cmd cmd = {
		.flags = CMD_WANT_SKB,
		.data = { NULL, },
		.len = { 0, },
	};
	struct iwl_rx_packet *pkt;
	int ret;

	if (fw_has_capa(&fwrt->fw->ucode_capa,
			IWL_UCODE_TLV_CAPA_EXTEND_SHARED_MEM_CFG))
		cmd.id = iwl_cmd_id(SHARED_MEM_CFG_CMD, SYSTEM_GROUP, 0);
	else
		cmd.id = SHARED_MEM_CFG;

	ret = iwl_trans_send_cmd(fwrt->trans, &cmd);

	if (ret) {
		WARN(ret != -ERFKILL,
		     "Could not send the SMEM command: %d\n", ret);
		return;
	}

	pkt = cmd.resp_pkt;
	if (fwrt->trans->trans_cfg->device_family >= IWL_DEVICE_FAMILY_22000)
		iwl_parse_shared_mem_22000(fwrt, pkt);
	else
		iwl_parse_shared_mem(fwrt, pkt);

	IWL_DEBUG_INFO(fwrt, "SHARED MEM CFG: got memory offsets/sizes\n");

	iwl_free_resp(&cmd);
}