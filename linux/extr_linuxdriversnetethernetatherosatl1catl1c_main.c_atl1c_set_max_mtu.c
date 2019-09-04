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
struct net_device {scalar_t__ max_mtu; } ;
struct atl1c_hw {int nic_type; } ;
struct atl1c_adapter {struct atl1c_hw hw; } ;

/* Variables and functions */
 scalar_t__ ETH_DATA_LEN ; 
 scalar_t__ ETH_FCS_LEN ; 
 scalar_t__ ETH_HLEN ; 
 scalar_t__ MAX_JUMBO_FRAME_SIZE ; 
 scalar_t__ VLAN_HLEN ; 
#define  athr_l1c 130 
#define  athr_l1d 129 
#define  athr_l1d_2 128 
 struct atl1c_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void atl1c_set_max_mtu(struct net_device *netdev)
{
	struct atl1c_adapter *adapter = netdev_priv(netdev);
	struct atl1c_hw *hw = &adapter->hw;

	switch (hw->nic_type) {
	/* These (GbE) devices support jumbo packets, max_mtu 6122 */
	case athr_l1c:
	case athr_l1d:
	case athr_l1d_2:
		netdev->max_mtu = MAX_JUMBO_FRAME_SIZE -
				  (ETH_HLEN + ETH_FCS_LEN + VLAN_HLEN);
		break;
	/* The 10/100 devices don't support jumbo packets, max_mtu 1500 */
	default:
		netdev->max_mtu = ETH_DATA_LEN;
		break;
	}
}