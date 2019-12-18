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
struct gem {int /*<<< orphan*/  link_timer; int /*<<< orphan*/  dev; int /*<<< orphan*/  want_autoneg; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gem_begin_auto_negotiation (struct gem*,int /*<<< orphan*/ *) ; 
 struct gem* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_device_present (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gem_nway_reset(struct net_device *dev)
{
	struct gem *gp = netdev_priv(dev);

	if (!gp->want_autoneg)
		return -EINVAL;

	/* Restart link process  */
	if (netif_device_present(gp->dev)) {
		del_timer_sync(&gp->link_timer);
		gem_begin_auto_negotiation(gp, NULL);
	}

	return 0;
}