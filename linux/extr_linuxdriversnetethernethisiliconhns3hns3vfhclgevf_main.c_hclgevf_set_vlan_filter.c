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
typedef  int /*<<< orphan*/  vlan_id ;
typedef  int u8 ;
typedef  int u16 ;
struct hnae3_handle {int dummy; } ;
struct hclgevf_dev {int dummy; } ;
typedef  int /*<<< orphan*/  proto ;
typedef  int __be16 ;

/* Variables and functions */
 int EINVAL ; 
 int EPROTONOSUPPORT ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int /*<<< orphan*/  HCLGE_MBX_SET_VLAN ; 
 int /*<<< orphan*/  HCLGE_MBX_VLAN_FILTER ; 
 struct hclgevf_dev* hclgevf_ae_get_hdev (struct hnae3_handle*) ; 
 int hclgevf_send_mbx_msg (struct hclgevf_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 

__attribute__((used)) static int hclgevf_set_vlan_filter(struct hnae3_handle *handle,
				   __be16 proto, u16 vlan_id,
				   bool is_kill)
{
#define HCLGEVF_VLAN_MBX_MSG_LEN 5
	struct hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);
	u8 msg_data[HCLGEVF_VLAN_MBX_MSG_LEN];

	if (vlan_id > 4095)
		return -EINVAL;

	if (proto != htons(ETH_P_8021Q))
		return -EPROTONOSUPPORT;

	msg_data[0] = is_kill;
	memcpy(&msg_data[1], &vlan_id, sizeof(vlan_id));
	memcpy(&msg_data[3], &proto, sizeof(proto));
	return hclgevf_send_mbx_msg(hdev, HCLGE_MBX_SET_VLAN,
				    HCLGE_MBX_VLAN_FILTER, msg_data,
				    HCLGEVF_VLAN_MBX_MSG_LEN, false, NULL, 0);
}