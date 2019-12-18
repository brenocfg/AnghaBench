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
struct can_priv {scalar_t__ restart_ms; int /*<<< orphan*/  restart_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  msecs_to_jiffies (scalar_t__) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*) ; 
 struct can_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void can_bus_off(struct net_device *dev)
{
	struct can_priv *priv = netdev_priv(dev);

	netdev_info(dev, "bus-off\n");

	netif_carrier_off(dev);

	if (priv->restart_ms)
		schedule_delayed_work(&priv->restart_work,
				      msecs_to_jiffies(priv->restart_ms));
}