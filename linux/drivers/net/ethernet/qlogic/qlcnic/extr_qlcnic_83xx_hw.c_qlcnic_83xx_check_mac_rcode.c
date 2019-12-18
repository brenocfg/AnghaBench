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
typedef  scalar_t__ u32 ;
struct qlcnic_cmd_args {scalar_t__ cmd_op; int rsp_opcode; } ;
struct qlcnic_adapter {int /*<<< orphan*/  ahw; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ QLCNIC_CMD_CONFIG_MAC_VLAN ; 
 int /*<<< orphan*/  QLCNIC_MBX_FW (int /*<<< orphan*/ ,int) ; 
 int QLCNIC_RCODE_SUCCESS ; 
 scalar_t__ QLC_83XX_MAC_ABSENT ; 
 scalar_t__ QLC_83XX_MAC_PRESENT ; 
 scalar_t__ QLC_83XX_NO_NIC_RESOURCE ; 
 scalar_t__ readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qlcnic_83xx_check_mac_rcode(struct qlcnic_adapter *adapter,
				       struct qlcnic_cmd_args *cmd)
{
	u8 mac_cmd_rcode;
	u32 fw_data;

	if (cmd->cmd_op == QLCNIC_CMD_CONFIG_MAC_VLAN) {
		fw_data = readl(QLCNIC_MBX_FW(adapter->ahw, 2));
		mac_cmd_rcode = (u8)fw_data;
		if (mac_cmd_rcode == QLC_83XX_NO_NIC_RESOURCE ||
		    mac_cmd_rcode == QLC_83XX_MAC_PRESENT ||
		    mac_cmd_rcode == QLC_83XX_MAC_ABSENT) {
			cmd->rsp_opcode = QLCNIC_RCODE_SUCCESS;
			return QLCNIC_RCODE_SUCCESS;
		}
	}

	return -EINVAL;
}