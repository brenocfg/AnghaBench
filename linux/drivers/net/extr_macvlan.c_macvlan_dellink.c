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
struct macvlan_dev {scalar_t__ mode; int /*<<< orphan*/  lowerdev; int /*<<< orphan*/  list; int /*<<< orphan*/  port; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 scalar_t__ MACVLAN_MODE_SOURCE ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  macvlan_flush_sources (int /*<<< orphan*/ ,struct macvlan_dev*) ; 
 struct macvlan_dev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_upper_dev_unlink (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  unregister_netdevice_queue (struct net_device*,struct list_head*) ; 

void macvlan_dellink(struct net_device *dev, struct list_head *head)
{
	struct macvlan_dev *vlan = netdev_priv(dev);

	if (vlan->mode == MACVLAN_MODE_SOURCE)
		macvlan_flush_sources(vlan->port, vlan);
	list_del_rcu(&vlan->list);
	unregister_netdevice_queue(dev, head);
	netdev_upper_dev_unlink(vlan->lowerdev, dev);
}