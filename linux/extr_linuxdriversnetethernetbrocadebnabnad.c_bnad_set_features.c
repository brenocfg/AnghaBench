#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct net_device {int features; } ;
struct bnad {int /*<<< orphan*/  bna_lock; TYPE_1__* rx_info; } ;
typedef  int netdev_features_t ;
struct TYPE_2__ {int /*<<< orphan*/  rx; } ;

/* Variables and functions */
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int /*<<< orphan*/  bna_rx_vlan_strip_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bna_rx_vlan_strip_enable (int /*<<< orphan*/ ) ; 
 struct bnad* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int bnad_set_features(struct net_device *dev, netdev_features_t features)
{
	struct bnad *bnad = netdev_priv(dev);
	netdev_features_t changed = features ^ dev->features;

	if ((changed & NETIF_F_HW_VLAN_CTAG_RX) && netif_running(dev)) {
		unsigned long flags;

		spin_lock_irqsave(&bnad->bna_lock, flags);

		if (features & NETIF_F_HW_VLAN_CTAG_RX)
			bna_rx_vlan_strip_enable(bnad->rx_info[0].rx);
		else
			bna_rx_vlan_strip_disable(bnad->rx_info[0].rx);

		spin_unlock_irqrestore(&bnad->bna_lock, flags);
	}

	return 0;
}