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
struct board_info {scalar_t__ in_suspend; int /*<<< orphan*/  wake_state; } ;

/* Variables and functions */
 struct net_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dm9000_init_dm9000 (struct net_device*) ; 
 int /*<<< orphan*/  dm9000_unmask_interrupts (struct board_info*) ; 
 struct board_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_attach (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 

__attribute__((used)) static int
dm9000_drv_resume(struct device *dev)
{
	struct net_device *ndev = dev_get_drvdata(dev);
	struct board_info *db = netdev_priv(ndev);

	if (ndev) {
		if (netif_running(ndev)) {
			/* reset if we were not in wake mode to ensure if
			 * the device was powered off it is in a known state */
			if (!db->wake_state) {
				dm9000_init_dm9000(ndev);
				dm9000_unmask_interrupts(db);
			}

			netif_device_attach(ndev);
		}

		db->in_suspend = 0;
	}
	return 0;
}