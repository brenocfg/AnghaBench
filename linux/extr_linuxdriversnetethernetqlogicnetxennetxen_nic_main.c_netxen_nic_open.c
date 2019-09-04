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
struct netxen_adapter {scalar_t__ driver_mismatch; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int __netxen_nic_up (struct netxen_adapter*,struct net_device*) ; 
 struct netxen_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int netxen_nic_attach (struct netxen_adapter*) ; 
 int /*<<< orphan*/  netxen_nic_detach (struct netxen_adapter*) ; 

__attribute__((used)) static int netxen_nic_open(struct net_device *netdev)
{
	struct netxen_adapter *adapter = netdev_priv(netdev);
	int err = 0;

	if (adapter->driver_mismatch)
		return -EIO;

	err = netxen_nic_attach(adapter);
	if (err)
		return err;

	err = __netxen_nic_up(adapter, netdev);
	if (err)
		goto err_out;

	netif_start_queue(netdev);

	return 0;

err_out:
	netxen_nic_detach(adapter);
	return err;
}