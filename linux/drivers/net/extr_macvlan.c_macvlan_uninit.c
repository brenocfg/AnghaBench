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
struct macvlan_port {int /*<<< orphan*/  dev; scalar_t__ count; } ;
struct macvlan_dev {int /*<<< orphan*/  pcpu_stats; struct macvlan_port* port; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  macvlan_flush_sources (struct macvlan_port*,struct macvlan_dev*) ; 
 int /*<<< orphan*/  macvlan_port_destroy (int /*<<< orphan*/ ) ; 
 struct macvlan_dev* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void macvlan_uninit(struct net_device *dev)
{
	struct macvlan_dev *vlan = netdev_priv(dev);
	struct macvlan_port *port = vlan->port;

	free_percpu(vlan->pcpu_stats);

	macvlan_flush_sources(port, vlan);
	port->count -= 1;
	if (!port->count)
		macvlan_port_destroy(port->dev);
}