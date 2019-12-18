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
struct net_device {int dummy; } ;
struct altera_tse_private {TYPE_1__* mdio; } ;
struct TYPE_3__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  mdiobus_free (TYPE_1__*) ; 
 int /*<<< orphan*/  mdiobus_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int /*<<< orphan*/ ) ; 
 struct altera_tse_private* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_msg_drv (struct altera_tse_private*) ; 

__attribute__((used)) static void altera_tse_mdio_destroy(struct net_device *dev)
{
	struct altera_tse_private *priv = netdev_priv(dev);

	if (priv->mdio == NULL)
		return;

	if (netif_msg_drv(priv))
		netdev_info(dev, "MDIO bus %s: removed\n",
			    priv->mdio->id);

	mdiobus_unregister(priv->mdio);
	mdiobus_free(priv->mdio);
	priv->mdio = NULL;
}