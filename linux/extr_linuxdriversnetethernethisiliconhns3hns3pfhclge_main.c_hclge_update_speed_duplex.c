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
typedef  scalar_t__ u8 ;
struct hclge_mac {int speed; scalar_t__ duplex; int /*<<< orphan*/  autoneg; scalar_t__ phydev; } ;
struct TYPE_4__ {struct hclge_mac mac; } ;
struct hclge_dev {TYPE_1__* pdev; TYPE_2__ hw; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hclge_cfg_mac_speed_dup (struct hclge_dev*,int,scalar_t__) ; 
 int hclge_query_mac_an_speed_dup (struct hclge_dev*,int*,scalar_t__*) ; 

__attribute__((used)) static int hclge_update_speed_duplex(struct hclge_dev *hdev)
{
	struct hclge_mac mac = hdev->hw.mac;
	u8 duplex;
	int speed;
	int ret;

	/* get the speed and duplex as autoneg'result from mac cmd when phy
	 * doesn't exit.
	 */
	if (mac.phydev || !mac.autoneg)
		return 0;

	ret = hclge_query_mac_an_speed_dup(hdev, &speed, &duplex);
	if (ret) {
		dev_err(&hdev->pdev->dev,
			"mac autoneg/speed/duplex query failed %d\n", ret);
		return ret;
	}

	if ((mac.speed != speed) || (mac.duplex != duplex)) {
		ret = hclge_cfg_mac_speed_dup(hdev, speed, duplex);
		if (ret) {
			dev_err(&hdev->pdev->dev,
				"mac speed/duplex config failed %d\n", ret);
			return ret;
		}
	}

	return 0;
}