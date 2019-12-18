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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct iwl_fw_runtime {int /*<<< orphan*/  trans; } ;
struct iwl_fw_error_dump_data {void* len; void* type; scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_INFO (struct iwl_fw_runtime*,char*) ; 
 int IWL_FW_ERROR_DUMP_RADIO_REG ; 
 int RADIO_REG_MAX_READ ; 
 int RADIO_RSP_ADDR_POS ; 
 int RADIO_RSP_RD_CMD ; 
 int /*<<< orphan*/  RSP_RADIO_CMD ; 
 int /*<<< orphan*/  RSP_RADIO_RDDAT ; 
 void* cpu_to_le32 (int) ; 
 struct iwl_fw_error_dump_data* iwl_fw_error_next_data (struct iwl_fw_error_dump_data*) ; 
 scalar_t__ iwl_read_prph_no_grab (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_trans_grab_nic_access (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  iwl_trans_release_nic_access (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  iwl_write_prph_no_grab (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void iwl_read_radio_regs(struct iwl_fw_runtime *fwrt,
				struct iwl_fw_error_dump_data **dump_data)
{
	u8 *pos = (void *)(*dump_data)->data;
	unsigned long flags;
	int i;

	IWL_DEBUG_INFO(fwrt, "WRT radio registers dump\n");

	if (!iwl_trans_grab_nic_access(fwrt->trans, &flags))
		return;

	(*dump_data)->type = cpu_to_le32(IWL_FW_ERROR_DUMP_RADIO_REG);
	(*dump_data)->len = cpu_to_le32(RADIO_REG_MAX_READ);

	for (i = 0; i < RADIO_REG_MAX_READ; i++) {
		u32 rd_cmd = RADIO_RSP_RD_CMD;

		rd_cmd |= i << RADIO_RSP_ADDR_POS;
		iwl_write_prph_no_grab(fwrt->trans, RSP_RADIO_CMD, rd_cmd);
		*pos = (u8)iwl_read_prph_no_grab(fwrt->trans, RSP_RADIO_RDDAT);

		pos++;
	}

	*dump_data = iwl_fw_error_next_data(*dump_data);

	iwl_trans_release_nic_access(fwrt->trans, &flags);
}