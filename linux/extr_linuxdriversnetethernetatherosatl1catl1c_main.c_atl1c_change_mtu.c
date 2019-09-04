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
struct net_device {int mtu; } ;
struct TYPE_2__ {int max_frame_size; } ;
struct atl1c_adapter {int /*<<< orphan*/  flags; TYPE_1__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  __AT_RESETTING ; 
 int /*<<< orphan*/  atl1c_down (struct atl1c_adapter*) ; 
 int /*<<< orphan*/  atl1c_set_rxbufsize (struct atl1c_adapter*,struct net_device*) ; 
 int /*<<< orphan*/  atl1c_up (struct atl1c_adapter*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct atl1c_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_update_features (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int atl1c_change_mtu(struct net_device *netdev, int new_mtu)
{
	struct atl1c_adapter *adapter = netdev_priv(netdev);

	/* set MTU */
	if (netif_running(netdev)) {
		while (test_and_set_bit(__AT_RESETTING, &adapter->flags))
			msleep(1);
		netdev->mtu = new_mtu;
		adapter->hw.max_frame_size = new_mtu;
		atl1c_set_rxbufsize(adapter, netdev);
		atl1c_down(adapter);
		netdev_update_features(netdev);
		atl1c_up(adapter);
		clear_bit(__AT_RESETTING, &adapter->flags);
	}
	return 0;
}