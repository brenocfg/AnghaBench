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
struct ehea_port {int /*<<< orphan*/  stats_work; int /*<<< orphan*/  port_lock; } ;

/* Variables and functions */
 int ehea_up (struct net_device*) ; 
 int /*<<< orphan*/  ifup ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct ehea_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_info (struct ehea_port*,int /*<<< orphan*/ ,struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_tx_start_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  port_napi_enable (struct ehea_port*) ; 
 int /*<<< orphan*/  round_jiffies_relative (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ehea_open(struct net_device *dev)
{
	int ret;
	struct ehea_port *port = netdev_priv(dev);

	mutex_lock(&port->port_lock);

	netif_info(port, ifup, dev, "enabling port\n");

	netif_carrier_off(dev);

	ret = ehea_up(dev);
	if (!ret) {
		port_napi_enable(port);
		netif_tx_start_all_queues(dev);
	}

	mutex_unlock(&port->port_lock);
	schedule_delayed_work(&port->stats_work,
			      round_jiffies_relative(msecs_to_jiffies(1000)));

	return ret;
}