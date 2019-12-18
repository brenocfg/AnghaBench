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
struct niu {int /*<<< orphan*/  orig_led_state; } ;
struct net_device {int dummy; } ;
typedef  enum ethtool_phys_id_state { ____Placeholder_ethtool_phys_id_state } ethtool_phys_id_state ;

/* Variables and functions */
 int EAGAIN ; 
#define  ETHTOOL_ID_ACTIVE 131 
#define  ETHTOOL_ID_INACTIVE 130 
#define  ETHTOOL_ID_OFF 129 
#define  ETHTOOL_ID_ON 128 
 struct niu* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  niu_force_led (struct niu*,int) ; 
 int /*<<< orphan*/  niu_led_state_restore (struct niu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  niu_led_state_save (struct niu*) ; 

__attribute__((used)) static int niu_set_phys_id(struct net_device *dev,
			   enum ethtool_phys_id_state state)

{
	struct niu *np = netdev_priv(dev);

	if (!netif_running(dev))
		return -EAGAIN;

	switch (state) {
	case ETHTOOL_ID_ACTIVE:
		np->orig_led_state = niu_led_state_save(np);
		return 1;	/* cycle on/off once per second */

	case ETHTOOL_ID_ON:
		niu_force_led(np, 1);
		break;

	case ETHTOOL_ID_OFF:
		niu_force_led(np, 0);
		break;

	case ETHTOOL_ID_INACTIVE:
		niu_led_state_restore(np, np->orig_led_state);
	}

	return 0;
}