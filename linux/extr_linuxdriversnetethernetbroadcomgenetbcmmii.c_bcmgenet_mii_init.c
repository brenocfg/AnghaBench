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
struct bcmgenet_priv {int dummy; } ;

/* Variables and functions */
 int bcmgenet_mii_bus_init (struct bcmgenet_priv*) ; 
 int /*<<< orphan*/  bcmgenet_mii_exit (struct net_device*) ; 
 int bcmgenet_mii_register (struct bcmgenet_priv*) ; 
 struct bcmgenet_priv* netdev_priv (struct net_device*) ; 

int bcmgenet_mii_init(struct net_device *dev)
{
	struct bcmgenet_priv *priv = netdev_priv(dev);
	int ret;

	ret = bcmgenet_mii_register(priv);
	if (ret)
		return ret;

	ret = bcmgenet_mii_bus_init(priv);
	if (ret)
		goto out;

	return 0;

out:
	bcmgenet_mii_exit(dev);
	return ret;
}