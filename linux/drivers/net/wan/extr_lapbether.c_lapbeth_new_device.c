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
struct lapbethdev {int /*<<< orphan*/  node; struct net_device* ethdev; struct net_device* axdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  NET_NAME_UNKNOWN ; 
 struct net_device* alloc_netdev (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  lapbeth_devices ; 
 int /*<<< orphan*/  lapbeth_setup ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct lapbethdev* netdev_priv (struct net_device*) ; 
 scalar_t__ register_netdevice (struct net_device*) ; 

__attribute__((used)) static int lapbeth_new_device(struct net_device *dev)
{
	struct net_device *ndev;
	struct lapbethdev *lapbeth;
	int rc = -ENOMEM;

	ASSERT_RTNL();

	ndev = alloc_netdev(sizeof(*lapbeth), "lapb%d", NET_NAME_UNKNOWN,
			    lapbeth_setup);
	if (!ndev)
		goto out;

	lapbeth = netdev_priv(ndev);
	lapbeth->axdev = ndev;

	dev_hold(dev);
	lapbeth->ethdev = dev;

	rc = -EIO;
	if (register_netdevice(ndev))
		goto fail;

	list_add_rcu(&lapbeth->node, &lapbeth_devices);
	rc = 0;
out:
	return rc;
fail:
	dev_put(dev);
	free_netdev(ndev);
	goto out;
}