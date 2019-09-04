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
struct hclge_dev {int mps; TYPE_1__* pdev; int /*<<< orphan*/  hw; } ;
struct hclge_desc {scalar_t__ data; } ;
struct hclge_config_max_frm_size_cmd {int min_frm_size; int /*<<< orphan*/  max_frm_size; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETH_FCS_LEN ; 
 int ETH_HLEN ; 
 int /*<<< orphan*/  HCLGE_MAC_DEFAULT_FRAME ; 
 int HCLGE_MAC_MAX_FRAME ; 
 int HCLGE_MAC_MIN_FRAME ; 
 int /*<<< orphan*/  HCLGE_OPC_CONFIG_MAX_FRM_SIZE ; 
 int VLAN_HLEN ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hclge_cmd_send (int /*<<< orphan*/ *,struct hclge_desc*,int) ; 
 int /*<<< orphan*/  hclge_cmd_setup_basic_desc (struct hclge_desc*,int /*<<< orphan*/ ,int) ; 
 int max (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hclge_set_mac_mtu(struct hclge_dev *hdev, int new_mtu)
{
	struct hclge_config_max_frm_size_cmd *req;
	struct hclge_desc desc;
	int max_frm_size;
	int ret;

	max_frm_size = new_mtu + ETH_HLEN + ETH_FCS_LEN + VLAN_HLEN;

	if (max_frm_size < HCLGE_MAC_MIN_FRAME ||
	    max_frm_size > HCLGE_MAC_MAX_FRAME)
		return -EINVAL;

	max_frm_size = max(max_frm_size, HCLGE_MAC_DEFAULT_FRAME);

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_CONFIG_MAX_FRM_SIZE, false);

	req = (struct hclge_config_max_frm_size_cmd *)desc.data;
	req->max_frm_size = cpu_to_le16(max_frm_size);
	req->min_frm_size = HCLGE_MAC_MIN_FRAME;

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	if (ret)
		dev_err(&hdev->pdev->dev, "set mtu fail, ret =%d.\n", ret);
	else
		hdev->mps = max_frm_size;

	return ret;
}