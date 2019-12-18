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
struct e1000_hw {int dummy; } ;
struct e1000_adapter {struct e1000_hw hw; } ;
typedef  enum ethtool_phys_id_state { ____Placeholder_ethtool_phys_id_state } ethtool_phys_id_state ;

/* Variables and functions */
#define  ETHTOOL_ID_ACTIVE 131 
#define  ETHTOOL_ID_INACTIVE 130 
#define  ETHTOOL_ID_OFF 129 
#define  ETHTOOL_ID_ON 128 
 int /*<<< orphan*/  e1000_cleanup_led (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_led_off (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_led_on (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_setup_led (struct e1000_hw*) ; 
 struct e1000_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int e1000_set_phys_id(struct net_device *netdev,
			     enum ethtool_phys_id_state state)
{
	struct e1000_adapter *adapter = netdev_priv(netdev);
	struct e1000_hw *hw = &adapter->hw;

	switch (state) {
	case ETHTOOL_ID_ACTIVE:
		e1000_setup_led(hw);
		return 2;

	case ETHTOOL_ID_ON:
		e1000_led_on(hw);
		break;

	case ETHTOOL_ID_OFF:
		e1000_led_off(hw);
		break;

	case ETHTOOL_ID_INACTIVE:
		e1000_cleanup_led(hw);
	}

	return 0;
}