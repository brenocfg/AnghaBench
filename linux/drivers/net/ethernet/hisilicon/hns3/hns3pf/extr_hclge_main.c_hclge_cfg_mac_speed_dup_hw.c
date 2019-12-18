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
typedef  scalar_t__ u8 ;
struct hclge_dev {TYPE_1__* pdev; int /*<<< orphan*/  hw; } ;
struct hclge_desc {scalar_t__ data; } ;
struct hclge_config_mac_speed_dup_cmd {int /*<<< orphan*/  mac_change_fec_en; int /*<<< orphan*/  speed_dup; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HCLGE_CFG_DUPLEX_B ; 
 int /*<<< orphan*/  HCLGE_CFG_MAC_SPEED_CHANGE_EN_B ; 
 int /*<<< orphan*/  HCLGE_CFG_SPEED_M ; 
 int /*<<< orphan*/  HCLGE_CFG_SPEED_S ; 
#define  HCLGE_MAC_SPEED_100G 135 
#define  HCLGE_MAC_SPEED_100M 134 
#define  HCLGE_MAC_SPEED_10G 133 
#define  HCLGE_MAC_SPEED_10M 132 
#define  HCLGE_MAC_SPEED_1G 131 
#define  HCLGE_MAC_SPEED_25G 130 
#define  HCLGE_MAC_SPEED_40G 129 
#define  HCLGE_MAC_SPEED_50G 128 
 int /*<<< orphan*/  HCLGE_OPC_CONFIG_SPEED_DUP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hclge_cmd_send (int /*<<< orphan*/ *,struct hclge_desc*,int) ; 
 int /*<<< orphan*/  hclge_cmd_setup_basic_desc (struct hclge_desc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hnae3_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hnae3_set_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hclge_cfg_mac_speed_dup_hw(struct hclge_dev *hdev, int speed,
				      u8 duplex)
{
	struct hclge_config_mac_speed_dup_cmd *req;
	struct hclge_desc desc;
	int ret;

	req = (struct hclge_config_mac_speed_dup_cmd *)desc.data;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_CONFIG_SPEED_DUP, false);

	if (duplex)
		hnae3_set_bit(req->speed_dup, HCLGE_CFG_DUPLEX_B, 1);

	switch (speed) {
	case HCLGE_MAC_SPEED_10M:
		hnae3_set_field(req->speed_dup, HCLGE_CFG_SPEED_M,
				HCLGE_CFG_SPEED_S, 6);
		break;
	case HCLGE_MAC_SPEED_100M:
		hnae3_set_field(req->speed_dup, HCLGE_CFG_SPEED_M,
				HCLGE_CFG_SPEED_S, 7);
		break;
	case HCLGE_MAC_SPEED_1G:
		hnae3_set_field(req->speed_dup, HCLGE_CFG_SPEED_M,
				HCLGE_CFG_SPEED_S, 0);
		break;
	case HCLGE_MAC_SPEED_10G:
		hnae3_set_field(req->speed_dup, HCLGE_CFG_SPEED_M,
				HCLGE_CFG_SPEED_S, 1);
		break;
	case HCLGE_MAC_SPEED_25G:
		hnae3_set_field(req->speed_dup, HCLGE_CFG_SPEED_M,
				HCLGE_CFG_SPEED_S, 2);
		break;
	case HCLGE_MAC_SPEED_40G:
		hnae3_set_field(req->speed_dup, HCLGE_CFG_SPEED_M,
				HCLGE_CFG_SPEED_S, 3);
		break;
	case HCLGE_MAC_SPEED_50G:
		hnae3_set_field(req->speed_dup, HCLGE_CFG_SPEED_M,
				HCLGE_CFG_SPEED_S, 4);
		break;
	case HCLGE_MAC_SPEED_100G:
		hnae3_set_field(req->speed_dup, HCLGE_CFG_SPEED_M,
				HCLGE_CFG_SPEED_S, 5);
		break;
	default:
		dev_err(&hdev->pdev->dev, "invalid speed (%d)\n", speed);
		return -EINVAL;
	}

	hnae3_set_bit(req->mac_change_fec_en, HCLGE_CFG_MAC_SPEED_CHANGE_EN_B,
		      1);

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	if (ret) {
		dev_err(&hdev->pdev->dev,
			"mac speed/duplex config cmd failed %d.\n", ret);
		return ret;
	}

	return 0;
}