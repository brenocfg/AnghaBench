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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct hnae3_handle {scalar_t__ port_base_vlan_state; } ;
struct hclgevf_dev {struct hnae3_handle nic; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_MBX_PORT_BASE_VLAN_CFG ; 
 int /*<<< orphan*/  HCLGE_MBX_SET_VLAN ; 
 int /*<<< orphan*/  HNAE3_DOWN_CLIENT ; 
 scalar_t__ HNAE3_PORT_BASE_VLAN_DISABLE ; 
 scalar_t__ HNAE3_PORT_BASE_VLAN_ENABLE ; 
 int /*<<< orphan*/  HNAE3_UP_CLIENT ; 
 int /*<<< orphan*/  hclgevf_notify_client (struct hclgevf_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hclgevf_send_mbx_msg (struct hclgevf_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

void hclgevf_update_port_base_vlan_info(struct hclgevf_dev *hdev, u16 state,
					u8 *port_base_vlan_info, u8 data_size)
{
	struct hnae3_handle *nic = &hdev->nic;

	rtnl_lock();
	hclgevf_notify_client(hdev, HNAE3_DOWN_CLIENT);
	rtnl_unlock();

	/* send msg to PF and wait update port based vlan info */
	hclgevf_send_mbx_msg(hdev, HCLGE_MBX_SET_VLAN,
			     HCLGE_MBX_PORT_BASE_VLAN_CFG,
			     port_base_vlan_info, data_size,
			     false, NULL, 0);

	if (state == HNAE3_PORT_BASE_VLAN_DISABLE)
		nic->port_base_vlan_state = HNAE3_PORT_BASE_VLAN_DISABLE;
	else
		nic->port_base_vlan_state = HNAE3_PORT_BASE_VLAN_ENABLE;

	rtnl_lock();
	hclgevf_notify_client(hdev, HNAE3_UP_CLIENT);
	rtnl_unlock();
}