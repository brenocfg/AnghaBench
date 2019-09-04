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
struct net_device {int dummy; } ;
struct TYPE_2__ {int status; } ;
struct e1000_hw {TYPE_1__ mng_cookie; } ;
struct e1000_adapter {int /*<<< orphan*/  mng_vlan_id; int /*<<< orphan*/ * active_vlans; int /*<<< orphan*/  flags; struct e1000_hw hw; } ;

/* Variables and functions */
 int E1000_CHECK_RESET_COUNT ; 
 int E1000_MNG_DHCP_COOKIE_STATUS_VLAN_SUPPORT ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int /*<<< orphan*/  WARN_ON (scalar_t__) ; 
 int /*<<< orphan*/  __E1000_RESETTING ; 
 int /*<<< orphan*/  e1000_down (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000_free_all_rx_resources (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000_free_all_tx_resources (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000_free_irq (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000_power_down_phy (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000_vlan_rx_kill_vid (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 struct e1000_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

int e1000_close(struct net_device *netdev)
{
	struct e1000_adapter *adapter = netdev_priv(netdev);
	struct e1000_hw *hw = &adapter->hw;
	int count = E1000_CHECK_RESET_COUNT;

	while (test_bit(__E1000_RESETTING, &adapter->flags) && count--)
		usleep_range(10000, 20000);

	WARN_ON(test_bit(__E1000_RESETTING, &adapter->flags));
	e1000_down(adapter);
	e1000_power_down_phy(adapter);
	e1000_free_irq(adapter);

	e1000_free_all_tx_resources(adapter);
	e1000_free_all_rx_resources(adapter);

	/* kill manageability vlan ID if supported, but not if a vlan with
	 * the same ID is registered on the host OS (let 8021q kill it)
	 */
	if ((hw->mng_cookie.status &
	     E1000_MNG_DHCP_COOKIE_STATUS_VLAN_SUPPORT) &&
	    !test_bit(adapter->mng_vlan_id, adapter->active_vlans)) {
		e1000_vlan_rx_kill_vid(netdev, htons(ETH_P_8021Q),
				       adapter->mng_vlan_id);
	}

	return 0;
}