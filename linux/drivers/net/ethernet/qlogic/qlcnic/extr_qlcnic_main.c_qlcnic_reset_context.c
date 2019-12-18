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
struct qlcnic_adapter {scalar_t__ is_up; int /*<<< orphan*/  state; struct net_device* netdev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  NETDEV_UP ; 
 scalar_t__ QLCNIC_ADAPTER_UP_MAGIC ; 
 int /*<<< orphan*/  __QLCNIC_RESETTING ; 
 int /*<<< orphan*/  __qlcnic_down (struct qlcnic_adapter*,struct net_device*) ; 
 int /*<<< orphan*/  __qlcnic_up (struct qlcnic_adapter*,struct net_device*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_device_attach (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_detach (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int qlcnic_attach (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_detach (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_restore_indev_addr (struct net_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
qlcnic_reset_context(struct qlcnic_adapter *adapter)
{
	int err = 0;
	struct net_device *netdev = adapter->netdev;

	if (test_and_set_bit(__QLCNIC_RESETTING, &adapter->state))
		return -EBUSY;

	if (adapter->is_up == QLCNIC_ADAPTER_UP_MAGIC) {

		netif_device_detach(netdev);

		if (netif_running(netdev))
			__qlcnic_down(adapter, netdev);

		qlcnic_detach(adapter);

		if (netif_running(netdev)) {
			err = qlcnic_attach(adapter);
			if (!err) {
				__qlcnic_up(adapter, netdev);
				qlcnic_restore_indev_addr(netdev, NETDEV_UP);
			}
		}

		netif_device_attach(netdev);
	}

	clear_bit(__QLCNIC_RESETTING, &adapter->state);
	return err;
}