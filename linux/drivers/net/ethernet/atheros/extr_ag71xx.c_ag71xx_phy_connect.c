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
struct net_device {int dummy; } ;
struct device_node {int dummy; } ;
struct ag71xx {int /*<<< orphan*/  phy_if_mode; struct net_device* ndev; TYPE_2__* pdev; } ;
struct TYPE_3__ {struct device_node* of_node; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  ag71xx_phy_link_adjust ; 
 int /*<<< orphan*/  netif_err (struct ag71xx*,int /*<<< orphan*/ ,struct net_device*,char*,...) ; 
 struct device_node* of_node_get (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 struct phy_device* of_phy_connect (struct net_device*,struct device_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ of_phy_is_fixed_link (struct device_node*) ; 
 int of_phy_register_fixed_link (struct device_node*) ; 
 int /*<<< orphan*/  phy_attached_info (struct phy_device*) ; 
 int /*<<< orphan*/  probe ; 

__attribute__((used)) static int ag71xx_phy_connect(struct ag71xx *ag)
{
	struct device_node *np = ag->pdev->dev.of_node;
	struct net_device *ndev = ag->ndev;
	struct device_node *phy_node;
	struct phy_device *phydev;
	int ret;

	if (of_phy_is_fixed_link(np)) {
		ret = of_phy_register_fixed_link(np);
		if (ret < 0) {
			netif_err(ag, probe, ndev, "Failed to register fixed PHY link: %d\n",
				  ret);
			return ret;
		}

		phy_node = of_node_get(np);
	} else {
		phy_node = of_parse_phandle(np, "phy-handle", 0);
	}

	if (!phy_node) {
		netif_err(ag, probe, ndev, "Could not find valid phy node\n");
		return -ENODEV;
	}

	phydev = of_phy_connect(ag->ndev, phy_node, ag71xx_phy_link_adjust,
				0, ag->phy_if_mode);

	of_node_put(phy_node);

	if (!phydev) {
		netif_err(ag, probe, ndev, "Could not connect to PHY device\n");
		return -ENODEV;
	}

	phy_attached_info(phydev);

	return 0;
}