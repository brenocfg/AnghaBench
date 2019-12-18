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
struct ef4_nic {TYPE_1__* type; } ;
typedef  enum ethtool_phys_id_state { ____Placeholder_ethtool_phys_id_state } ethtool_phys_id_state ;
typedef  enum ef4_led_mode { ____Placeholder_ef4_led_mode } ef4_led_mode ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_id_led ) (struct ef4_nic*,int) ;} ;

/* Variables and functions */
 int EF4_LED_DEFAULT ; 
 int EF4_LED_OFF ; 
 int EF4_LED_ON ; 
#define  ETHTOOL_ID_ACTIVE 131 
#define  ETHTOOL_ID_INACTIVE 130 
#define  ETHTOOL_ID_OFF 129 
#define  ETHTOOL_ID_ON 128 
 struct ef4_nic* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct ef4_nic*,int) ; 

__attribute__((used)) static int ef4_ethtool_phys_id(struct net_device *net_dev,
			       enum ethtool_phys_id_state state)
{
	struct ef4_nic *efx = netdev_priv(net_dev);
	enum ef4_led_mode mode = EF4_LED_DEFAULT;

	switch (state) {
	case ETHTOOL_ID_ON:
		mode = EF4_LED_ON;
		break;
	case ETHTOOL_ID_OFF:
		mode = EF4_LED_OFF;
		break;
	case ETHTOOL_ID_INACTIVE:
		mode = EF4_LED_DEFAULT;
		break;
	case ETHTOOL_ID_ACTIVE:
		return 1;	/* cycle on/off once per second */
	}

	efx->type->set_id_led(efx, mode);
	return 0;
}