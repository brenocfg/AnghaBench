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
struct phy_device {TYPE_1__* drv; int /*<<< orphan*/  phy_id; } ;
struct mtk_mac {size_t id; } ;
struct mtk_eth {int /*<<< orphan*/  dev; int /*<<< orphan*/ * netdev; } ;
struct device_node {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_phy_link_adjust ; 
 int of_get_phy_mode (struct device_node*) ; 
 struct phy_device* of_phy_connect (int /*<<< orphan*/ ,struct device_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  phydev_name (struct phy_device*) ; 

__attribute__((used)) static int mtk_phy_connect_node(struct mtk_eth *eth, struct mtk_mac *mac,
				struct device_node *phy_node)
{
	struct phy_device *phydev;
	int phy_mode;

	phy_mode = of_get_phy_mode(phy_node);
	if (phy_mode < 0) {
		dev_err(eth->dev, "incorrect phy-mode %d\n", phy_mode);
		return -EINVAL;
	}

	phydev = of_phy_connect(eth->netdev[mac->id], phy_node,
				mtk_phy_link_adjust, 0, phy_mode);
	if (!phydev) {
		dev_err(eth->dev, "could not connect to PHY\n");
		return -ENODEV;
	}

	dev_info(eth->dev,
		 "connected mac %d to PHY at %s [uid=%08x, driver=%s]\n",
		 mac->id, phydev_name(phydev), phydev->phy_id,
		 phydev->drv->name);

	return 0;
}