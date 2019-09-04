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
struct netxen_adapter {scalar_t__ is_up; int /*<<< orphan*/  state; struct net_device* netdev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ NETXEN_ADAPTER_UP_MAGIC ; 
 int /*<<< orphan*/  __NX_RESETTING ; 
 int /*<<< orphan*/  __netxen_nic_down (struct netxen_adapter*,struct net_device*) ; 
 int __netxen_nic_up (struct netxen_adapter*,struct net_device*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_device_attach (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_detach (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int netxen_nic_attach (struct netxen_adapter*) ; 
 int /*<<< orphan*/  netxen_nic_detach (struct netxen_adapter*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
netxen_nic_reset_context(struct netxen_adapter *adapter)
{
	int err = 0;
	struct net_device *netdev = adapter->netdev;

	if (test_and_set_bit(__NX_RESETTING, &adapter->state))
		return -EBUSY;

	if (adapter->is_up == NETXEN_ADAPTER_UP_MAGIC) {

		netif_device_detach(netdev);

		if (netif_running(netdev))
			__netxen_nic_down(adapter, netdev);

		netxen_nic_detach(adapter);

		if (netif_running(netdev)) {
			err = netxen_nic_attach(adapter);
			if (!err)
				err = __netxen_nic_up(adapter, netdev);

			if (err)
				goto done;
		}

		netif_device_attach(netdev);
	}

done:
	clear_bit(__NX_RESETTING, &adapter->state);
	return err;
}