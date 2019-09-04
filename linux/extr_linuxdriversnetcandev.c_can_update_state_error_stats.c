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
struct TYPE_2__ {int /*<<< orphan*/  bus_off; int /*<<< orphan*/  error_passive; int /*<<< orphan*/  error_warning; } ;
struct can_priv {int state; TYPE_1__ can_stats; } ;
typedef  enum can_state { ____Placeholder_can_state } can_state ;

/* Variables and functions */
#define  CAN_STATE_BUS_OFF 130 
#define  CAN_STATE_ERROR_PASSIVE 129 
#define  CAN_STATE_ERROR_WARNING 128 
 struct can_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void can_update_state_error_stats(struct net_device *dev,
					 enum can_state new_state)
{
	struct can_priv *priv = netdev_priv(dev);

	if (new_state <= priv->state)
		return;

	switch (new_state) {
	case CAN_STATE_ERROR_WARNING:
		priv->can_stats.error_warning++;
		break;
	case CAN_STATE_ERROR_PASSIVE:
		priv->can_stats.error_passive++;
		break;
	case CAN_STATE_BUS_OFF:
		priv->can_stats.bus_off++;
		break;
	default:
		break;
	}
}