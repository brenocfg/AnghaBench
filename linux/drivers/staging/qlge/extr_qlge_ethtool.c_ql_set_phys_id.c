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
struct ql_adapter {int /*<<< orphan*/  led_config; } ;
struct net_device {int dummy; } ;
typedef  enum ethtool_phys_id_state { ____Placeholder_ethtool_phys_id_state } ethtool_phys_id_state ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
#define  ETHTOOL_ID_ACTIVE 129 
#define  ETHTOOL_ID_INACTIVE 128 
 int /*<<< orphan*/  QL_LED_BLINK ; 
 struct ql_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  ql_mb_get_led_cfg (struct ql_adapter*) ; 
 int /*<<< orphan*/  ql_mb_set_led_cfg (struct ql_adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ql_set_phys_id(struct net_device *ndev,
			  enum ethtool_phys_id_state state)

{
	struct ql_adapter *qdev = netdev_priv(ndev);

	switch (state) {
	case ETHTOOL_ID_ACTIVE:
		/* Save the current LED settings */
		if (ql_mb_get_led_cfg(qdev))
			return -EIO;

		/* Start blinking */
		ql_mb_set_led_cfg(qdev, QL_LED_BLINK);
		return 0;

	case ETHTOOL_ID_INACTIVE:
		/* Restore LED settings */
		if (ql_mb_set_led_cfg(qdev, qdev->led_config))
			return -EIO;
		return 0;

	default:
		return -EINVAL;
	}
}