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
struct phy_device {int /*<<< orphan*/  supported; int /*<<< orphan*/  advertising; } ;
struct net_device {int dummy; } ;
struct TYPE_7__ {struct phy_device* phydev; } ;
struct TYPE_8__ {TYPE_3__ mac; } ;
struct hclge_dev {TYPE_4__ hw; TYPE_2__* vport; } ;
struct TYPE_5__ {struct net_device* netdev; } ;
struct TYPE_6__ {TYPE_1__ nic; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_PHY_SUPPORTED_FEATURES ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_SGMII ; 
 int /*<<< orphan*/  SUPPORTED_FIBRE ; 
 int /*<<< orphan*/  hclge_mac_adjust_link ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 int phy_connect_direct (struct net_device*,struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int hclge_mac_connect_phy(struct hclge_dev *hdev)
{
	struct net_device *netdev = hdev->vport[0].nic.netdev;
	struct phy_device *phydev = hdev->hw.mac.phydev;
	int ret;

	if (!phydev)
		return 0;

	phydev->supported &= ~SUPPORTED_FIBRE;

	ret = phy_connect_direct(netdev, phydev,
				 hclge_mac_adjust_link,
				 PHY_INTERFACE_MODE_SGMII);
	if (ret) {
		netdev_err(netdev, "phy_connect_direct err.\n");
		return ret;
	}

	phydev->supported &= HCLGE_PHY_SUPPORTED_FEATURES;
	phydev->advertising = phydev->supported;

	return 0;
}