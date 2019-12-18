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
struct hnae3_handle {int /*<<< orphan*/  port_base_vlan_state; } ;
struct hclgevf_dev {TYPE_1__* pdev; struct hnae3_handle nic; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_MBX_GET_PORT_BASE_VLAN_STATE ; 
 int /*<<< orphan*/  HCLGE_MBX_SET_VLAN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hclgevf_send_mbx_msg (struct hclgevf_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int hclgevf_get_port_base_vlan_filter_state(struct hclgevf_dev *hdev)
{
	struct hnae3_handle *nic = &hdev->nic;
	u8 resp_msg;
	int ret;

	ret = hclgevf_send_mbx_msg(hdev, HCLGE_MBX_SET_VLAN,
				   HCLGE_MBX_GET_PORT_BASE_VLAN_STATE,
				   NULL, 0, true, &resp_msg, sizeof(u8));
	if (ret) {
		dev_err(&hdev->pdev->dev,
			"VF request to get port based vlan state failed %d",
			ret);
		return ret;
	}

	nic->port_base_vlan_state = resp_msg;

	return 0;
}