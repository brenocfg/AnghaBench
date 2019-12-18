#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct phy_device {int link; } ;
struct TYPE_4__ {struct phy_device* phydev; } ;
struct TYPE_5__ {TYPE_1__ mac; } ;
struct hclge_dev {TYPE_3__* pdev; TYPE_2__ hw; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_LINK_STATUS_MS ; 
 int HCLGE_PHY_LINK_STATUS_NUM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int phy_read_status (struct phy_device*) ; 

__attribute__((used)) static void hclge_phy_link_status_wait(struct hclge_dev *hdev,
				       int link_ret)
{
#define HCLGE_PHY_LINK_STATUS_NUM  200

	struct phy_device *phydev = hdev->hw.mac.phydev;
	int i = 0;
	int ret;

	do {
		ret = phy_read_status(phydev);
		if (ret) {
			dev_err(&hdev->pdev->dev,
				"phy update link status fail, ret = %d\n", ret);
			return;
		}

		if (phydev->link == link_ret)
			break;

		msleep(HCLGE_LINK_STATUS_MS);
	} while (++i < HCLGE_PHY_LINK_STATUS_NUM);
}