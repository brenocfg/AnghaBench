#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct phy_device {int dummy; } ;
struct net_device {int dummy; } ;
struct emac_board_info {int duplex; scalar_t__ speed; scalar_t__ link; int /*<<< orphan*/  ndev; int /*<<< orphan*/  phy_interface; int /*<<< orphan*/  phy_node; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  SPEED_100 ; 
 int /*<<< orphan*/  emac_handle_link_change ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 struct emac_board_info* netdev_priv (struct net_device*) ; 
 struct phy_device* of_phy_connect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_set_max_speed (struct phy_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int emac_mdio_probe(struct net_device *dev)
{
	struct emac_board_info *db = netdev_priv(dev);
	struct phy_device *phydev;

	/* to-do: PHY interrupts are currently not supported */

	/* attach the mac to the phy */
	phydev = of_phy_connect(db->ndev, db->phy_node,
				&emac_handle_link_change, 0,
				db->phy_interface);
	if (!phydev) {
		netdev_err(db->ndev, "could not find the PHY\n");
		return -ENODEV;
	}

	/* mask with MAC supported features */
	phy_set_max_speed(phydev, SPEED_100);

	db->link = 0;
	db->speed = 0;
	db->duplex = -1;

	return 0;
}