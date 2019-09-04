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
struct tg3 {int mac_mode; int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;
typedef  int netdev_features_t ;

/* Variables and functions */
 int MAC_MODE_PORT_INT_LPBACK ; 
 int NETIF_F_LOOPBACK ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*) ; 
 struct tg3* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tg3_mac_loopback (struct tg3*,int) ; 
 int /*<<< orphan*/  tg3_setup_phy (struct tg3*,int) ; 

__attribute__((used)) static void tg3_set_loopback(struct net_device *dev, netdev_features_t features)
{
	struct tg3 *tp = netdev_priv(dev);

	if (features & NETIF_F_LOOPBACK) {
		if (tp->mac_mode & MAC_MODE_PORT_INT_LPBACK)
			return;

		spin_lock_bh(&tp->lock);
		tg3_mac_loopback(tp, true);
		netif_carrier_on(tp->dev);
		spin_unlock_bh(&tp->lock);
		netdev_info(dev, "Internal MAC loopback mode enabled.\n");
	} else {
		if (!(tp->mac_mode & MAC_MODE_PORT_INT_LPBACK))
			return;

		spin_lock_bh(&tp->lock);
		tg3_mac_loopback(tp, false);
		/* Force link status check */
		tg3_setup_phy(tp, true);
		spin_unlock_bh(&tp->lock);
		netdev_info(dev, "Internal MAC loopback mode disabled.\n");
	}
}