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
struct typhoon {int /*<<< orphan*/  ioaddr; TYPE_1__* indexes; int /*<<< orphan*/  txLoRing; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  txLoCleared; } ;

/* Variables and functions */
 int /*<<< orphan*/  NoWait ; 
 int /*<<< orphan*/  WaitNoSleep ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct typhoon* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  typhoon_clean_tx (struct typhoon*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  typhoon_free_rx_rings (struct typhoon*) ; 
 scalar_t__ typhoon_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ typhoon_start_runtime (struct typhoon*) ; 

__attribute__((used)) static void
typhoon_tx_timeout(struct net_device *dev)
{
	struct typhoon *tp = netdev_priv(dev);

	if(typhoon_reset(tp->ioaddr, WaitNoSleep) < 0) {
		netdev_warn(dev, "could not reset in tx timeout\n");
		goto truly_dead;
	}

	/* If we ever start using the Hi ring, it will need cleaning too */
	typhoon_clean_tx(tp, &tp->txLoRing, &tp->indexes->txLoCleared);
	typhoon_free_rx_rings(tp);

	if(typhoon_start_runtime(tp) < 0) {
		netdev_err(dev, "could not start runtime in tx timeout\n");
		goto truly_dead;
        }

	netif_wake_queue(dev);
	return;

truly_dead:
	/* Reset the hardware, and turn off carrier to avoid more timeouts */
	typhoon_reset(tp->ioaddr, NoWait);
	netif_carrier_off(dev);
}