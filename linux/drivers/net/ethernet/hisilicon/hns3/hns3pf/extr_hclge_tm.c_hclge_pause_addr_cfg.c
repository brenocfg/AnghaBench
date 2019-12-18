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
typedef  int /*<<< orphan*/  u16 ;
struct hclge_dev {int /*<<< orphan*/  hw; } ;
struct hclge_desc {scalar_t__ data; } ;
struct hclge_cfg_pause_param_cmd {int /*<<< orphan*/  pause_trans_time; int /*<<< orphan*/  pause_trans_gap; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_OPC_CFG_MAC_PARA ; 
 int hclge_cmd_send (int /*<<< orphan*/ *,struct hclge_desc*,int) ; 
 int /*<<< orphan*/  hclge_cmd_setup_basic_desc (struct hclge_desc*,int /*<<< orphan*/ ,int) ; 
 int hclge_pause_param_cfg (struct hclge_dev*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 

int hclge_pause_addr_cfg(struct hclge_dev *hdev, const u8 *mac_addr)
{
	struct hclge_cfg_pause_param_cmd *pause_param;
	struct hclge_desc desc;
	u16 trans_time;
	u8 trans_gap;
	int ret;

	pause_param = (struct hclge_cfg_pause_param_cmd *)desc.data;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_CFG_MAC_PARA, true);

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	if (ret)
		return ret;

	trans_gap = pause_param->pause_trans_gap;
	trans_time = le16_to_cpu(pause_param->pause_trans_time);

	return hclge_pause_param_cfg(hdev, mac_addr, trans_gap, trans_time);
}