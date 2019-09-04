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
struct hclge_mac_vlan_mask_entry_cmd {int /*<<< orphan*/  mac_mask; int /*<<< orphan*/  vlan_mask; } ;
struct hclge_dev {TYPE_1__* pdev; int /*<<< orphan*/  hw; } ;
struct hclge_desc {scalar_t__ data; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_OPC_MAC_VLAN_MASK_SET ; 
 int /*<<< orphan*/  HCLGE_VLAN_MASK_EN_B ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int hclge_cmd_send (int /*<<< orphan*/ *,struct hclge_desc*,int) ; 
 int /*<<< orphan*/  hclge_cmd_setup_basic_desc (struct hclge_desc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hnae3_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hclge_set_default_mac_vlan_mask(struct hclge_dev *hdev,
					   bool mask_vlan,
					   u8 *mac_mask)
{
	struct hclge_mac_vlan_mask_entry_cmd *req;
	struct hclge_desc desc;
	int status;

	req = (struct hclge_mac_vlan_mask_entry_cmd *)desc.data;
	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_MAC_VLAN_MASK_SET, false);

	hnae3_set_bit(req->vlan_mask, HCLGE_VLAN_MASK_EN_B,
		      mask_vlan ? 1 : 0);
	ether_addr_copy(req->mac_mask, mac_mask);

	status = hclge_cmd_send(&hdev->hw, &desc, 1);
	if (status)
		dev_err(&hdev->pdev->dev,
			"Config mac_vlan_mask failed for cmd_send, ret =%d\n",
			status);

	return status;
}