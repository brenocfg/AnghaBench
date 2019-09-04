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
struct phy_device {scalar_t__ speed; scalar_t__ duplex; scalar_t__ link; } ;
struct net_device {struct phy_device* phydev; } ;
struct bgmac {scalar_t__ mac_speed; scalar_t__ mac_duplex; } ;

/* Variables and functions */
 int /*<<< orphan*/  bgmac_mac_speed (struct bgmac*) ; 
 struct bgmac* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  phy_print_status (struct phy_device*) ; 

void bgmac_adjust_link(struct net_device *net_dev)
{
	struct bgmac *bgmac = netdev_priv(net_dev);
	struct phy_device *phy_dev = net_dev->phydev;
	bool update = false;

	if (phy_dev->link) {
		if (phy_dev->speed != bgmac->mac_speed) {
			bgmac->mac_speed = phy_dev->speed;
			update = true;
		}

		if (phy_dev->duplex != bgmac->mac_duplex) {
			bgmac->mac_duplex = phy_dev->duplex;
			update = true;
		}
	}

	if (update) {
		bgmac_mac_speed(bgmac);
		phy_print_status(phy_dev);
	}
}