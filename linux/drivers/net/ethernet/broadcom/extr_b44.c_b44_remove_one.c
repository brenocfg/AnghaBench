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
struct ssb_device {int /*<<< orphan*/  bus; } ;
struct net_device {int dummy; } ;
struct b44 {int flags; int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int B44_FLAG_EXTERNAL_PHY ; 
 int /*<<< orphan*/  PCI_D3hot ; 
 int /*<<< orphan*/  b44_unregister_phy_one (struct b44*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 struct b44* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssb_bus_may_powerdown (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssb_device_disable (struct ssb_device*,int /*<<< orphan*/ ) ; 
 struct net_device* ssb_get_drvdata (struct ssb_device*) ; 
 int /*<<< orphan*/  ssb_pcihost_set_power_state (struct ssb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssb_set_drvdata (struct ssb_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static void b44_remove_one(struct ssb_device *sdev)
{
	struct net_device *dev = ssb_get_drvdata(sdev);
	struct b44 *bp = netdev_priv(dev);

	unregister_netdev(dev);
	if (bp->flags & B44_FLAG_EXTERNAL_PHY)
		b44_unregister_phy_one(bp);
	ssb_device_disable(sdev, 0);
	ssb_bus_may_powerdown(sdev->bus);
	netif_napi_del(&bp->napi);
	free_netdev(dev);
	ssb_pcihost_set_power_state(sdev, PCI_D3hot);
	ssb_set_drvdata(sdev, NULL);
}