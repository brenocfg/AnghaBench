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
struct be_adapter {struct net_device* netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  be_clear (struct be_adapter*) ; 
 int /*<<< orphan*/  be_close (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_detach (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

__attribute__((used)) static void be_cleanup(struct be_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;

	rtnl_lock();
	netif_device_detach(netdev);
	if (netif_running(netdev))
		be_close(netdev);
	rtnl_unlock();

	be_clear(adapter);
}