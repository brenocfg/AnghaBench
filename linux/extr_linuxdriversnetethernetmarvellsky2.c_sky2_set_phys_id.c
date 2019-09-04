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
struct sky2_port {int dummy; } ;
struct net_device {int dummy; } ;
typedef  enum ethtool_phys_id_state { ____Placeholder_ethtool_phys_id_state } ethtool_phys_id_state ;

/* Variables and functions */
#define  ETHTOOL_ID_ACTIVE 131 
#define  ETHTOOL_ID_INACTIVE 130 
#define  ETHTOOL_ID_OFF 129 
#define  ETHTOOL_ID_ON 128 
 int /*<<< orphan*/  MO_LED_NORM ; 
 int /*<<< orphan*/  MO_LED_OFF ; 
 int /*<<< orphan*/  MO_LED_ON ; 
 struct sky2_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  sky2_led (struct sky2_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sky2_set_phys_id(struct net_device *dev,
			    enum ethtool_phys_id_state state)
{
	struct sky2_port *sky2 = netdev_priv(dev);

	switch (state) {
	case ETHTOOL_ID_ACTIVE:
		return 1;	/* cycle on/off once per second */
	case ETHTOOL_ID_INACTIVE:
		sky2_led(sky2, MO_LED_NORM);
		break;
	case ETHTOOL_ID_ON:
		sky2_led(sky2, MO_LED_ON);
		break;
	case ETHTOOL_ID_OFF:
		sky2_led(sky2, MO_LED_OFF);
		break;
	}

	return 0;
}