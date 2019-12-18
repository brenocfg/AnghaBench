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
typedef  int /*<<< orphan*/  u16 ;
struct hinic_port_vlan_cmd {int /*<<< orphan*/  vlan_id; int /*<<< orphan*/  func_idx; } ;
struct hinic_hwdev {int /*<<< orphan*/  hwif; } ;
struct hinic_dev {struct hinic_hwdev* hwdev; } ;
typedef  int /*<<< orphan*/  port_vlan_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  HINIC_HWIF_FUNC_IDX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HINIC_PORT_CMD_DEL_VLAN ; 
 int hinic_port_msg_cmd (struct hinic_hwdev*,int /*<<< orphan*/ ,struct hinic_port_vlan_cmd*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int hinic_port_del_vlan(struct hinic_dev *nic_dev, u16 vlan_id)
{
	struct hinic_hwdev *hwdev = nic_dev->hwdev;
	struct hinic_port_vlan_cmd port_vlan_cmd;

	port_vlan_cmd.func_idx = HINIC_HWIF_FUNC_IDX(hwdev->hwif);
	port_vlan_cmd.vlan_id = vlan_id;

	return hinic_port_msg_cmd(hwdev, HINIC_PORT_CMD_DEL_VLAN,
				 &port_vlan_cmd, sizeof(port_vlan_cmd),
				 NULL, NULL);
}