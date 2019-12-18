#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct stmmac_priv {TYPE_1__* mii; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  mdiobus_free (TYPE_1__*) ; 
 int /*<<< orphan*/  mdiobus_unregister (TYPE_1__*) ; 
 struct stmmac_priv* netdev_priv (struct net_device*) ; 

int stmmac_mdio_unregister(struct net_device *ndev)
{
	struct stmmac_priv *priv = netdev_priv(ndev);

	if (!priv->mii)
		return 0;

	mdiobus_unregister(priv->mii);
	priv->mii->priv = NULL;
	mdiobus_free(priv->mii);
	priv->mii = NULL;

	return 0;
}