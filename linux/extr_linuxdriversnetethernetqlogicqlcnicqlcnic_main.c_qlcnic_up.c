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
struct qlcnic_adapter {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int __qlcnic_up (struct qlcnic_adapter*,struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

int qlcnic_up(struct qlcnic_adapter *adapter, struct net_device *netdev)
{
	int err = 0;

	rtnl_lock();
	if (netif_running(netdev))
		err = __qlcnic_up(adapter, netdev);
	rtnl_unlock();

	return err;
}