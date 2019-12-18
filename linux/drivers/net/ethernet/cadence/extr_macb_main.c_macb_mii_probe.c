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
struct macb {int caps; int duplex; scalar_t__ speed; scalar_t__ link; int /*<<< orphan*/  phy_interface; int /*<<< orphan*/  mii_bus; scalar_t__ phy_node; TYPE_2__* pdev; } ;
struct device_node {int dummy; } ;
struct TYPE_3__ {struct device_node* of_node; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENXIO ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_1000baseT_Half_BIT ; 
 scalar_t__ IS_ERR (struct phy_device*) ; 
 int MACB_CAPS_GIGABIT_MODE_AVAILABLE ; 
 int MACB_CAPS_NO_GIGABIT_HALF ; 
 int PHY_MAX_ADDR ; 
 int PTR_ERR (struct phy_device*) ; 
 int /*<<< orphan*/  SPEED_100 ; 
 int /*<<< orphan*/  SPEED_1000 ; 
 int /*<<< orphan*/  macb_handle_link_change ; 
 scalar_t__ macb_is_gem (struct macb*) ; 
 struct phy_device* mdiobus_scan (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct macb* netdev_priv (struct net_device*) ; 
 scalar_t__ of_node_get (struct device_node*) ; 
 scalar_t__ of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 struct phy_device* of_phy_connect (struct net_device*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ of_phy_is_fixed_link (struct device_node*) ; 
 int phy_connect_direct (struct net_device*,struct phy_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct phy_device* phy_find_first (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_remove_link_mode (struct phy_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_set_max_speed (struct phy_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int macb_mii_probe(struct net_device *dev)
{
	struct macb *bp = netdev_priv(dev);
	struct phy_device *phydev;
	struct device_node *np;
	int ret, i;

	np = bp->pdev->dev.of_node;
	ret = 0;

	if (np) {
		if (of_phy_is_fixed_link(np)) {
			bp->phy_node = of_node_get(np);
		} else {
			bp->phy_node = of_parse_phandle(np, "phy-handle", 0);
			/* fallback to standard phy registration if no
			 * phy-handle was found nor any phy found during
			 * dt phy registration
			 */
			if (!bp->phy_node && !phy_find_first(bp->mii_bus)) {
				for (i = 0; i < PHY_MAX_ADDR; i++) {
					phydev = mdiobus_scan(bp->mii_bus, i);
					if (IS_ERR(phydev) &&
					    PTR_ERR(phydev) != -ENODEV) {
						ret = PTR_ERR(phydev);
						break;
					}
				}

				if (ret)
					return -ENODEV;
			}
		}
	}

	if (bp->phy_node) {
		phydev = of_phy_connect(dev, bp->phy_node,
					&macb_handle_link_change, 0,
					bp->phy_interface);
		if (!phydev)
			return -ENODEV;
	} else {
		phydev = phy_find_first(bp->mii_bus);
		if (!phydev) {
			netdev_err(dev, "no PHY found\n");
			return -ENXIO;
		}

		/* attach the mac to the phy */
		ret = phy_connect_direct(dev, phydev, &macb_handle_link_change,
					 bp->phy_interface);
		if (ret) {
			netdev_err(dev, "Could not attach to PHY\n");
			return ret;
		}
	}

	/* mask with MAC supported features */
	if (macb_is_gem(bp) && bp->caps & MACB_CAPS_GIGABIT_MODE_AVAILABLE)
		phy_set_max_speed(phydev, SPEED_1000);
	else
		phy_set_max_speed(phydev, SPEED_100);

	if (bp->caps & MACB_CAPS_NO_GIGABIT_HALF)
		phy_remove_link_mode(phydev,
				     ETHTOOL_LINK_MODE_1000baseT_Half_BIT);

	bp->link = 0;
	bp->speed = 0;
	bp->duplex = -1;

	return 0;
}