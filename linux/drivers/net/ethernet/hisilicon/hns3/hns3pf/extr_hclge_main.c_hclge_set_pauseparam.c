#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct phy_device {int dummy; } ;
struct hnae3_handle {int dummy; } ;
struct hclge_vport {struct hclge_dev* back; } ;
struct TYPE_6__ {scalar_t__ fc_mode; } ;
struct TYPE_8__ {struct phy_device* phydev; } ;
struct TYPE_5__ {TYPE_4__ mac; } ;
struct hclge_dev {TYPE_3__* pdev; TYPE_2__ tm_info; TYPE_1__ hw; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ HCLGE_FC_PFC ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int hclge_cfg_pauseparam (struct hclge_dev*,scalar_t__,scalar_t__) ; 
 scalar_t__ hclge_get_autoneg (struct hnae3_handle*) ; 
 struct hclge_vport* hclge_get_vport (struct hnae3_handle*) ; 
 int /*<<< orphan*/  hclge_record_user_pauseparam (struct hclge_dev*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  hclge_set_flowctrl_adv (struct hclge_dev*,scalar_t__,scalar_t__) ; 
 int phy_start_aneg (struct phy_device*) ; 

__attribute__((used)) static int hclge_set_pauseparam(struct hnae3_handle *handle, u32 auto_neg,
				u32 rx_en, u32 tx_en)
{
	struct hclge_vport *vport = hclge_get_vport(handle);
	struct hclge_dev *hdev = vport->back;
	struct phy_device *phydev = hdev->hw.mac.phydev;
	u32 fc_autoneg;

	if (phydev) {
		fc_autoneg = hclge_get_autoneg(handle);
		if (auto_neg != fc_autoneg) {
			dev_info(&hdev->pdev->dev,
				 "To change autoneg please use: ethtool -s <dev> autoneg <on|off>\n");
			return -EOPNOTSUPP;
		}
	}

	if (hdev->tm_info.fc_mode == HCLGE_FC_PFC) {
		dev_info(&hdev->pdev->dev,
			 "Priority flow control enabled. Cannot set link flow control.\n");
		return -EOPNOTSUPP;
	}

	hclge_set_flowctrl_adv(hdev, rx_en, tx_en);

	hclge_record_user_pauseparam(hdev, rx_en, tx_en);

	if (!auto_neg)
		return hclge_cfg_pauseparam(hdev, rx_en, tx_en);

	if (phydev)
		return phy_start_aneg(phydev);

	return -EOPNOTSUPP;
}