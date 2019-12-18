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
struct qlcnic_adapter {struct net_device* netdev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETDEV_UP ; 
 int /*<<< orphan*/  netif_device_attach (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  qlcnic_restore_indev_addr (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_up (struct qlcnic_adapter*,struct net_device*) ; 

__attribute__((used)) static void qlcnic_sriov_vf_attach(struct qlcnic_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;

	if (netif_running(netdev)) {
		if (!qlcnic_up(adapter, netdev))
			qlcnic_restore_indev_addr(netdev, NETDEV_UP);
	}

	netif_device_attach(netdev);
}