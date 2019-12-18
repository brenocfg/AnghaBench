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
struct phy_device {scalar_t__ link; scalar_t__ speed; scalar_t__ duplex; } ;
struct nixge_priv {scalar_t__ link; scalar_t__ speed; scalar_t__ duplex; } ;
struct net_device {struct phy_device* phydev; } ;

/* Variables and functions */
 struct nixge_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  phy_print_status (struct phy_device*) ; 

__attribute__((used)) static void nixge_handle_link_change(struct net_device *ndev)
{
	struct nixge_priv *priv = netdev_priv(ndev);
	struct phy_device *phydev = ndev->phydev;

	if (phydev->link != priv->link || phydev->speed != priv->speed ||
	    phydev->duplex != priv->duplex) {
		priv->link = phydev->link;
		priv->speed = phydev->speed;
		priv->duplex = phydev->duplex;
		phy_print_status(phydev);
	}
}