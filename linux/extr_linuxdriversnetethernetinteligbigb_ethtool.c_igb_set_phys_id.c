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
struct igb_adapter {int /*<<< orphan*/  led_status; struct e1000_hw hw; } ;
typedef  enum ethtool_phys_id_state { ____Placeholder_ethtool_phys_id_state } ethtool_phys_id_state ;

/* Variables and functions */
#define  ETHTOOL_ID_ACTIVE 131 
#define  ETHTOOL_ID_INACTIVE 130 
#define  ETHTOOL_ID_OFF 129 
#define  ETHTOOL_ID_ON 128 
 int /*<<< orphan*/  IGB_LED_ON ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  igb_blink_led (struct e1000_hw*) ; 
 int /*<<< orphan*/  igb_cleanup_led (struct e1000_hw*) ; 
 int /*<<< orphan*/  igb_led_off (struct e1000_hw*) ; 
 struct igb_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int igb_set_phys_id(struct net_device *netdev,
			   enum ethtool_phys_id_state state)
{
	struct igb_adapter *adapter = netdev_priv(netdev);
	struct e1000_hw *hw = &adapter->hw;

	switch (state) {
	case ETHTOOL_ID_ACTIVE:
		igb_blink_led(hw);
		return 2;
	case ETHTOOL_ID_ON:
		igb_blink_led(hw);
		break;
	case ETHTOOL_ID_OFF:
		igb_led_off(hw);
		break;
	case ETHTOOL_ID_INACTIVE:
		igb_led_off(hw);
		clear_bit(IGB_LED_ON, &adapter->led_status);
		igb_cleanup_led(hw);
		break;
	}

	return 0;
}