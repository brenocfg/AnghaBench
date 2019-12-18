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
struct net_device {int dummy; } ;
struct bcm_enet_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcm_enetsw_phy_is_external (struct bcm_enet_priv*,int) ; 
 int bcmenet_sw_mdio_read (struct bcm_enet_priv*,int /*<<< orphan*/ ,int,int) ; 
 struct bcm_enet_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int bcm_enetsw_mii_mdio_read(struct net_device *dev, int phy_id,
				    int location)
{
	struct bcm_enet_priv *priv;

	priv = netdev_priv(dev);
	return bcmenet_sw_mdio_read(priv,
				    bcm_enetsw_phy_is_external(priv, phy_id),
				    phy_id, location);
}