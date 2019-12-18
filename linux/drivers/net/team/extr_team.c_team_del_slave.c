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
struct team {int /*<<< orphan*/  team_lock_key; int /*<<< orphan*/  lock; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lockdep_register_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_set_class (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_unregister_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_change_features (struct net_device*) ; 
 struct team* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_is_team_master (struct net_device*) ; 
 int team_port_del (struct team*,struct net_device*) ; 

__attribute__((used)) static int team_del_slave(struct net_device *dev, struct net_device *port_dev)
{
	struct team *team = netdev_priv(dev);
	int err;

	mutex_lock(&team->lock);
	err = team_port_del(team, port_dev);
	mutex_unlock(&team->lock);

	if (err)
		return err;

	if (netif_is_team_master(port_dev)) {
		lockdep_unregister_key(&team->team_lock_key);
		lockdep_register_key(&team->team_lock_key);
		lockdep_set_class(&team->lock, &team->team_lock_key);
	}
	netdev_change_features(dev);

	return err;
}