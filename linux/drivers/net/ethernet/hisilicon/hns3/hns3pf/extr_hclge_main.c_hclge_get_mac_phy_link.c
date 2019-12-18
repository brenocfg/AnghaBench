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
struct TYPE_5__ {TYPE_1__* phydev; } ;
struct TYPE_6__ {TYPE_2__ mac; } ;
struct hclge_dev {TYPE_3__ hw; int /*<<< orphan*/  state; } ;
struct TYPE_4__ {scalar_t__ state; unsigned int link; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_STATE_DOWN ; 
 scalar_t__ PHY_RUNNING ; 
 unsigned int hclge_get_mac_link_status (struct hclge_dev*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hclge_get_mac_phy_link(struct hclge_dev *hdev)
{
	unsigned int mac_state;
	int link_stat;

	if (test_bit(HCLGE_STATE_DOWN, &hdev->state))
		return 0;

	mac_state = hclge_get_mac_link_status(hdev);

	if (hdev->hw.mac.phydev) {
		if (hdev->hw.mac.phydev->state == PHY_RUNNING)
			link_stat = mac_state &
				hdev->hw.mac.phydev->link;
		else
			link_stat = 0;

	} else {
		link_stat = mac_state;
	}

	return !!link_stat;
}