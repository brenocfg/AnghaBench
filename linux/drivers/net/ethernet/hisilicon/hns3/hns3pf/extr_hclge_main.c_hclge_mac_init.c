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
struct hclge_mac {int user_fec_mode; scalar_t__ link; int /*<<< orphan*/  autoneg; scalar_t__ support_autoneg; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; } ;
struct TYPE_3__ {struct hclge_mac mac; } ;
struct hclge_dev {int support_sfp_query; TYPE_2__* pdev; int /*<<< orphan*/  mps; TYPE_1__ hw; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCLGE_MAC_FULL ; 
 int /*<<< orphan*/  HNAE3_FEC_USER_DEF ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hclge_buffer_alloc (struct hclge_dev*) ; 
 int hclge_cfg_mac_speed_dup_hw (struct hclge_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hclge_set_autoneg_en (struct hclge_dev*,int /*<<< orphan*/ ) ; 
 int hclge_set_default_loopback (struct hclge_dev*) ; 
 int hclge_set_fec_hw (struct hclge_dev*,int) ; 
 int hclge_set_mac_mtu (struct hclge_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hclge_mac_init(struct hclge_dev *hdev)
{
	struct hclge_mac *mac = &hdev->hw.mac;
	int ret;

	hdev->support_sfp_query = true;
	hdev->hw.mac.duplex = HCLGE_MAC_FULL;
	ret = hclge_cfg_mac_speed_dup_hw(hdev, hdev->hw.mac.speed,
					 hdev->hw.mac.duplex);
	if (ret) {
		dev_err(&hdev->pdev->dev,
			"Config mac speed dup fail ret=%d\n", ret);
		return ret;
	}

	if (hdev->hw.mac.support_autoneg) {
		ret = hclge_set_autoneg_en(hdev, hdev->hw.mac.autoneg);
		if (ret) {
			dev_err(&hdev->pdev->dev,
				"Config mac autoneg fail ret=%d\n", ret);
			return ret;
		}
	}

	mac->link = 0;

	if (mac->user_fec_mode & BIT(HNAE3_FEC_USER_DEF)) {
		ret = hclge_set_fec_hw(hdev, mac->user_fec_mode);
		if (ret) {
			dev_err(&hdev->pdev->dev,
				"Fec mode init fail, ret = %d\n", ret);
			return ret;
		}
	}

	ret = hclge_set_mac_mtu(hdev, hdev->mps);
	if (ret) {
		dev_err(&hdev->pdev->dev, "set mtu failed ret=%d\n", ret);
		return ret;
	}

	ret = hclge_set_default_loopback(hdev);
	if (ret)
		return ret;

	ret = hclge_buffer_alloc(hdev);
	if (ret)
		dev_err(&hdev->pdev->dev,
			"allocate buffer fail, ret=%d\n", ret);

	return ret;
}