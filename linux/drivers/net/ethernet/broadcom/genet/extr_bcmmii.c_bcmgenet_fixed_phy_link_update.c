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
typedef  int u32 ;
struct net_device {scalar_t__ phydev; } ;
struct fixed_phy_status {int link; } ;
struct bcmgenet_priv {int dummy; } ;

/* Variables and functions */
 int MODE_LINK_STATUS ; 
 int /*<<< orphan*/  UMAC_MODE ; 
 int bcmgenet_umac_readl (struct bcmgenet_priv*,int /*<<< orphan*/ ) ; 
 struct bcmgenet_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int bcmgenet_fixed_phy_link_update(struct net_device *dev,
					  struct fixed_phy_status *status)
{
	struct bcmgenet_priv *priv;
	u32 reg;

	if (dev && dev->phydev && status) {
		priv = netdev_priv(dev);
		reg = bcmgenet_umac_readl(priv, UMAC_MODE);
		status->link = !!(reg & MODE_LINK_STATUS);
	}

	return 0;
}