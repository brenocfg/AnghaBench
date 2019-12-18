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
struct sxgbe_priv_data {int rxcsum_insertion; int /*<<< orphan*/  ioaddr; TYPE_2__* hw; } ;
struct net_device {int features; } ;
typedef  int netdev_features_t ;
struct TYPE_4__ {TYPE_1__* mac; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* disable_rx_csum ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* enable_rx_csum ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int NETIF_F_RXCSUM ; 
 struct sxgbe_priv_data* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sxgbe_set_features(struct net_device *dev,
			      netdev_features_t features)
{
	struct sxgbe_priv_data *priv = netdev_priv(dev);
	netdev_features_t changed = dev->features ^ features;

	if (changed & NETIF_F_RXCSUM) {
		if (features & NETIF_F_RXCSUM) {
			priv->hw->mac->enable_rx_csum(priv->ioaddr);
			priv->rxcsum_insertion = true;
		} else {
			priv->hw->mac->disable_rx_csum(priv->ioaddr);
			priv->rxcsum_insertion = false;
		}
	}

	return 0;
}