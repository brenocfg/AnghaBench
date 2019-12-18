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
struct hclge_dev {int /*<<< orphan*/  hw; } ;
struct hclge_desc {scalar_t__ data; } ;
struct hclge_config_max_frm_size_cmd {int /*<<< orphan*/  min_frm_size; int /*<<< orphan*/  max_frm_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_MAC_MIN_FRAME ; 
 int /*<<< orphan*/  HCLGE_OPC_CONFIG_MAX_FRM_SIZE ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int hclge_cmd_send (int /*<<< orphan*/ *,struct hclge_desc*,int) ; 
 int /*<<< orphan*/  hclge_cmd_setup_basic_desc (struct hclge_desc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hclge_set_mac_mtu(struct hclge_dev *hdev, int new_mps)
{
	struct hclge_config_max_frm_size_cmd *req;
	struct hclge_desc desc;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_CONFIG_MAX_FRM_SIZE, false);

	req = (struct hclge_config_max_frm_size_cmd *)desc.data;
	req->max_frm_size = cpu_to_le16(new_mps);
	req->min_frm_size = HCLGE_MAC_MIN_FRAME;

	return hclge_cmd_send(&hdev->hw, &desc, 1);
}