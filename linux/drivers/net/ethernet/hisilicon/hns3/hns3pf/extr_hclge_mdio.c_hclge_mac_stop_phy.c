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
struct phy_device {int dummy; } ;
struct net_device {struct phy_device* phydev; } ;
struct hclge_dev {TYPE_2__* vport; } ;
struct TYPE_3__ {struct net_device* netdev; } ;
struct TYPE_4__ {TYPE_1__ nic; } ;

/* Variables and functions */
 int /*<<< orphan*/  phy_stop (struct phy_device*) ; 

void hclge_mac_stop_phy(struct hclge_dev *hdev)
{
	struct net_device *netdev = hdev->vport[0].nic.netdev;
	struct phy_device *phydev = netdev->phydev;

	if (!phydev)
		return;

	phy_stop(phydev);
}