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
struct typhoon {int /*<<< orphan*/  napi; } ;
struct net_device {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_D3hot ; 
 int /*<<< orphan*/  TYPHOON_STATUS_WAITING_FOR_HOST ; 
 int /*<<< orphan*/  WaitSleep ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct typhoon* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 scalar_t__ typhoon_boot_3XP (struct typhoon*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  typhoon_free_rx_rings (struct typhoon*) ; 
 int /*<<< orphan*/  typhoon_init_rings (struct typhoon*) ; 
 scalar_t__ typhoon_sleep (struct typhoon*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ typhoon_stop_runtime (struct typhoon*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
typhoon_close(struct net_device *dev)
{
	struct typhoon *tp = netdev_priv(dev);

	netif_stop_queue(dev);
	napi_disable(&tp->napi);

	if(typhoon_stop_runtime(tp, WaitSleep) < 0)
		netdev_err(dev, "unable to stop runtime\n");

	/* Make sure there is no irq handler running on a different CPU. */
	free_irq(dev->irq, dev);

	typhoon_free_rx_rings(tp);
	typhoon_init_rings(tp);

	if(typhoon_boot_3XP(tp, TYPHOON_STATUS_WAITING_FOR_HOST) < 0)
		netdev_err(dev, "unable to boot sleep image\n");

	if(typhoon_sleep(tp, PCI_D3hot, 0) < 0)
		netdev_err(dev, "unable to put card to sleep\n");

	return 0;
}