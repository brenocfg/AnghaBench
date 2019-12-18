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
struct can_priv {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ CAN_STATE_ERROR_PASSIVE ; 
 struct can_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 

__attribute__((used)) static inline int canif_is_active(struct net_device *netdev)
{
	struct can_priv *can = netdev_priv(netdev);

	if (!netif_running(netdev))
		return 0;
	return (can->state <= CAN_STATE_ERROR_PASSIVE);
}