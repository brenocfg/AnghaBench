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
struct net_device {int features; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/  dev_addr; } ;
struct ep93xx_priv {int dummy; } ;
struct ep93xx_eth_data {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int NETIF_F_HW_CSUM ; 
 int NETIF_F_SG ; 
 struct net_device* alloc_etherdev (int) ; 
 int /*<<< orphan*/  ep93xx_ethtool_ops ; 
 int /*<<< orphan*/  ep93xx_netdev_ops ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct net_device *ep93xx_dev_alloc(struct ep93xx_eth_data *data)
{
	struct net_device *dev;

	dev = alloc_etherdev(sizeof(struct ep93xx_priv));
	if (dev == NULL)
		return NULL;

	memcpy(dev->dev_addr, data->dev_addr, ETH_ALEN);

	dev->ethtool_ops = &ep93xx_ethtool_ops;
	dev->netdev_ops = &ep93xx_netdev_ops;

	dev->features |= NETIF_F_SG | NETIF_F_HW_CSUM;

	return dev;
}