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
typedef  int /*<<< orphan*/  u16 ;
struct hnae3_handle {int dummy; } ;
struct hclgevf_dev {int /*<<< orphan*/  vlan_del_fail_bmap; int /*<<< orphan*/  state; } ;
typedef  int /*<<< orphan*/  proto ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int EPROTONOSUPPORT ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int /*<<< orphan*/  HCLGEVF_MAX_VLAN_ID ; 
 int /*<<< orphan*/  HCLGEVF_STATE_RST_HANDLING ; 
 int HCLGEVF_VLAN_MBX_MSG_LEN ; 
 int /*<<< orphan*/  HCLGE_MBX_SET_VLAN ; 
 int /*<<< orphan*/  HCLGE_MBX_VLAN_FILTER ; 
 struct hclgevf_dev* hclgevf_ae_get_hdev (struct hnae3_handle*) ; 
 int hclgevf_send_mbx_msg (struct hclgevf_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hclgevf_set_vlan_filter(struct hnae3_handle *handle,
				   __be16 proto, u16 vlan_id,
				   bool is_kill)
{
#define HCLGEVF_VLAN_MBX_MSG_LEN 5
	struct hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);
	u8 msg_data[HCLGEVF_VLAN_MBX_MSG_LEN];
	int ret;

	if (vlan_id > HCLGEVF_MAX_VLAN_ID)
		return -EINVAL;

	if (proto != htons(ETH_P_8021Q))
		return -EPROTONOSUPPORT;

	/* When device is resetting, firmware is unable to handle
	 * mailbox. Just record the vlan id, and remove it after
	 * reset finished.
	 */
	if (test_bit(HCLGEVF_STATE_RST_HANDLING, &hdev->state) && is_kill) {
		set_bit(vlan_id, hdev->vlan_del_fail_bmap);
		return -EBUSY;
	}

	msg_data[0] = is_kill;
	memcpy(&msg_data[1], &vlan_id, sizeof(vlan_id));
	memcpy(&msg_data[3], &proto, sizeof(proto));
	ret = hclgevf_send_mbx_msg(hdev, HCLGE_MBX_SET_VLAN,
				   HCLGE_MBX_VLAN_FILTER, msg_data,
				   HCLGEVF_VLAN_MBX_MSG_LEN, false, NULL, 0);

	/* when remove hw vlan filter failed, record the vlan id,
	 * and try to remove it from hw later, to be consistence
	 * with stack.
	 */
	if (is_kill && ret)
		set_bit(vlan_id, hdev->vlan_del_fail_bmap);

	return ret;
}