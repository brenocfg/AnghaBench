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
struct wilc_wfi_mon_priv {struct net_device* real_ndev; } ;
struct wilc {struct net_device* monitor_dev; } ;
struct net_device {int needs_free_netdev; int /*<<< orphan*/ * netdev_ops; scalar_t__* name; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_IEEE80211_RADIOTAP ; 
 int IFNAMSIZ ; 
 struct net_device* alloc_etherdev (int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct wilc_wfi_mon_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ register_netdevice (struct net_device*) ; 
 int /*<<< orphan*/  strncpy (scalar_t__*,char const*,int) ; 
 int /*<<< orphan*/  wilc_wfi_netdev_ops ; 

struct net_device *wilc_wfi_init_mon_interface(struct wilc *wl,
					       const char *name,
					       struct net_device *real_dev)
{
	struct wilc_wfi_mon_priv *priv;

	/*If monitor interface is already initialized, return it*/
	if (wl->monitor_dev)
		return wl->monitor_dev;

	wl->monitor_dev = alloc_etherdev(sizeof(struct wilc_wfi_mon_priv));
	if (!wl->monitor_dev)
		return NULL;

	wl->monitor_dev->type = ARPHRD_IEEE80211_RADIOTAP;
	strncpy(wl->monitor_dev->name, name, IFNAMSIZ);
	wl->monitor_dev->name[IFNAMSIZ - 1] = 0;
	wl->monitor_dev->netdev_ops = &wilc_wfi_netdev_ops;
	wl->monitor_dev->needs_free_netdev = true;

	if (register_netdevice(wl->monitor_dev)) {
		netdev_err(real_dev, "register_netdevice failed\n");
		return NULL;
	}
	priv = netdev_priv(wl->monitor_dev);
	if (!priv)
		return NULL;

	priv->real_ndev = real_dev;

	return wl->monitor_dev;
}