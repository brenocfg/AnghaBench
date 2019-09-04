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
struct TYPE_2__ {int max_frame_size; int rx_jumbo_th; } ;
struct atl1e_adapter {int /*<<< orphan*/  flags; TYPE_1__ hw; } ;

/* Variables and functions */
 int ETH_FCS_LEN ; 
 int ETH_HLEN ; 
 int VLAN_HLEN ; 
 int /*<<< orphan*/  __AT_RESETTING ; 
 int /*<<< orphan*/  atl1e_down (struct atl1e_adapter*) ; 
 int /*<<< orphan*/  atl1e_up (struct atl1e_adapter*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct atl1e_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int atl1e_change_mtu(struct net_device *netdev, int new_mtu)
{
	struct atl1e_adapter *adapter = netdev_priv(netdev);
	int max_frame = new_mtu + ETH_HLEN + ETH_FCS_LEN + VLAN_HLEN;

	/* set MTU */
	if (netif_running(netdev)) {
		while (test_and_set_bit(__AT_RESETTING, &adapter->flags))
			msleep(1);
		netdev->mtu = new_mtu;
		adapter->hw.max_frame_size = new_mtu;
		adapter->hw.rx_jumbo_th = (max_frame + 7) >> 3;
		atl1e_down(adapter);
		atl1e_up(adapter);
		clear_bit(__AT_RESETTING, &adapter->flags);
	}
	return 0;
}