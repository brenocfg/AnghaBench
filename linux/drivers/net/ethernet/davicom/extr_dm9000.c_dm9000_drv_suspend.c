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
struct device {int dummy; } ;
struct board_info {int in_suspend; int /*<<< orphan*/  wake_state; } ;

/* Variables and functions */
 struct net_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dm9000_shutdown (struct net_device*) ; 
 struct board_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_detach (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 

__attribute__((used)) static int
dm9000_drv_suspend(struct device *dev)
{
	struct net_device *ndev = dev_get_drvdata(dev);
	struct board_info *db;

	if (ndev) {
		db = netdev_priv(ndev);
		db->in_suspend = 1;

		if (!netif_running(ndev))
			return 0;

		netif_device_detach(ndev);

		/* only shutdown if not using WoL */
		if (!db->wake_state)
			dm9000_shutdown(ndev);
	}
	return 0;
}