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
struct team {int /*<<< orphan*/  lock; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_change_features (struct net_device*) ; 
 struct team* netdev_priv (struct net_device*) ; 
 int team_port_add (struct team*,struct net_device*,struct netlink_ext_ack*) ; 

__attribute__((used)) static int team_add_slave(struct net_device *dev, struct net_device *port_dev,
			  struct netlink_ext_ack *extack)
{
	struct team *team = netdev_priv(dev);
	int err;

	mutex_lock(&team->lock);
	err = team_port_add(team, port_dev, extack);
	mutex_unlock(&team->lock);

	if (!err)
		netdev_change_features(dev);

	return err;
}