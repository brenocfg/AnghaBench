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
struct fm10k_intfc {struct net_device* netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  drv ; 
 scalar_t__ netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int /*<<< orphan*/  netif_info (struct fm10k_intfc*,int /*<<< orphan*/ ,struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_tx_wake_all_queues (struct net_device*) ; 

__attribute__((used)) static void fm10k_watchdog_host_is_ready(struct fm10k_intfc *interface)
{
	struct net_device *netdev = interface->netdev;

	/* only continue if link state is currently down */
	if (netif_carrier_ok(netdev))
		return;

	netif_info(interface, drv, netdev, "NIC Link is up\n");

	netif_carrier_on(netdev);
	netif_tx_wake_all_queues(netdev);
}