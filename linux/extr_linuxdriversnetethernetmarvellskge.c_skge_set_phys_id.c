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
struct skge_port {int dummy; } ;
struct net_device {int dummy; } ;
typedef  enum ethtool_phys_id_state { ____Placeholder_ethtool_phys_id_state } ethtool_phys_id_state ;

/* Variables and functions */
#define  ETHTOOL_ID_ACTIVE 131 
#define  ETHTOOL_ID_INACTIVE 130 
#define  ETHTOOL_ID_OFF 129 
#define  ETHTOOL_ID_ON 128 
 int /*<<< orphan*/  LED_MODE_OFF ; 
 int /*<<< orphan*/  LED_MODE_ON ; 
 int /*<<< orphan*/  LED_MODE_TST ; 
 struct skge_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  skge_led (struct skge_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int skge_set_phys_id(struct net_device *dev,
			    enum ethtool_phys_id_state state)
{
	struct skge_port *skge = netdev_priv(dev);

	switch (state) {
	case ETHTOOL_ID_ACTIVE:
		return 2;	/* cycle on/off twice per second */

	case ETHTOOL_ID_ON:
		skge_led(skge, LED_MODE_TST);
		break;

	case ETHTOOL_ID_OFF:
		skge_led(skge, LED_MODE_OFF);
		break;

	case ETHTOOL_ID_INACTIVE:
		/* back to regular LED state */
		skge_led(skge, netif_running(dev) ? LED_MODE_ON : LED_MODE_OFF);
	}

	return 0;
}