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
struct nic {int /*<<< orphan*/  netdev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int e100_up (struct nic*) ; 
 int /*<<< orphan*/  ifup ; 
 struct nic* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_err (struct nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int e100_open(struct net_device *netdev)
{
	struct nic *nic = netdev_priv(netdev);
	int err = 0;

	netif_carrier_off(netdev);
	if ((err = e100_up(nic)))
		netif_err(nic, ifup, nic->netdev, "Cannot open interface, aborting\n");
	return err;
}