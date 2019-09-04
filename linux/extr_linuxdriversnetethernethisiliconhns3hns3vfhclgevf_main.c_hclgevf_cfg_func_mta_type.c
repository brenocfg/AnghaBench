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
typedef  int u8 ;
struct hclgevf_dev {int mta_mac_sel_type; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int HCLGEVF_MTA_TYPE_SEL_MAX ; 
 int /*<<< orphan*/  HCLGE_MBX_MAC_VLAN_MTA_TYPE_READ ; 
 int /*<<< orphan*/  HCLGE_MBX_SET_MULTICAST ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hclgevf_send_mbx_msg (struct hclgevf_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int*,int) ; 

__attribute__((used)) static int hclgevf_cfg_func_mta_type(struct hclgevf_dev *hdev)
{
	u8 resp_msg = HCLGEVF_MTA_TYPE_SEL_MAX;
	int ret;

	ret = hclgevf_send_mbx_msg(hdev, HCLGE_MBX_SET_MULTICAST,
				   HCLGE_MBX_MAC_VLAN_MTA_TYPE_READ,
				   NULL, 0, true, &resp_msg, sizeof(u8));

	if (ret) {
		dev_err(&hdev->pdev->dev,
			"Read mta type fail, ret=%d.\n", ret);
		return ret;
	}

	if (resp_msg > HCLGEVF_MTA_TYPE_SEL_MAX) {
		dev_err(&hdev->pdev->dev,
			"Read mta type invalid, resp=%d.\n", resp_msg);
		return -EINVAL;
	}

	hdev->mta_mac_sel_type = resp_msg;

	return 0;
}