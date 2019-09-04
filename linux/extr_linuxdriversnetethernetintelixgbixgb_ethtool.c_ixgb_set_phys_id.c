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
struct ixgb_adapter {int /*<<< orphan*/  hw; } ;
typedef  enum ethtool_phys_id_state { ____Placeholder_ethtool_phys_id_state } ethtool_phys_id_state ;

/* Variables and functions */
#define  ETHTOOL_ID_ACTIVE 131 
#define  ETHTOOL_ID_INACTIVE 130 
#define  ETHTOOL_ID_OFF 129 
#define  ETHTOOL_ID_ON 128 
 int /*<<< orphan*/  ixgb_led_off (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ixgb_led_on (int /*<<< orphan*/ *) ; 
 struct ixgb_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
ixgb_set_phys_id(struct net_device *netdev, enum ethtool_phys_id_state state)
{
	struct ixgb_adapter *adapter = netdev_priv(netdev);

	switch (state) {
	case ETHTOOL_ID_ACTIVE:
		return 2;

	case ETHTOOL_ID_ON:
		ixgb_led_on(&adapter->hw);
		break;

	case ETHTOOL_ID_OFF:
	case ETHTOOL_ID_INACTIVE:
		ixgb_led_off(&adapter->hw);
	}

	return 0;
}