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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct hnae3_handle {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * mac_addr; } ;
struct TYPE_4__ {TYPE_1__ mac; } ;
struct hclgevf_dev {TYPE_2__ hw; } ;
typedef  int /*<<< orphan*/  msg_data ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  HCLGE_MBX_MAC_VLAN_UC_ADD ; 
 int /*<<< orphan*/  HCLGE_MBX_MAC_VLAN_UC_MODIFY ; 
 int /*<<< orphan*/  HCLGE_MBX_SET_UNICAST ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct hclgevf_dev* hclgevf_ae_get_hdev (struct hnae3_handle*) ; 
 int hclgevf_send_mbx_msg (struct hclgevf_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hclgevf_set_mac_addr(struct hnae3_handle *handle, void *p,
				bool is_first)
{
	struct hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);
	u8 *old_mac_addr = (u8 *)hdev->hw.mac.mac_addr;
	u8 *new_mac_addr = (u8 *)p;
	u8 msg_data[ETH_ALEN * 2];
	u16 subcode;
	int status;

	ether_addr_copy(msg_data, new_mac_addr);
	ether_addr_copy(&msg_data[ETH_ALEN], old_mac_addr);

	subcode = is_first ? HCLGE_MBX_MAC_VLAN_UC_ADD :
			HCLGE_MBX_MAC_VLAN_UC_MODIFY;

	status = hclgevf_send_mbx_msg(hdev, HCLGE_MBX_SET_UNICAST,
				      subcode, msg_data, sizeof(msg_data),
				      true, NULL, 0);
	if (!status)
		ether_addr_copy(hdev->hw.mac.mac_addr, new_mac_addr);

	return status;
}