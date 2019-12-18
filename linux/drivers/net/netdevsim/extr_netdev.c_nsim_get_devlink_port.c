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
struct netdevsim {TYPE_1__* nsim_dev_port; } ;
struct net_device {int dummy; } ;
struct devlink_port {int dummy; } ;
struct TYPE_2__ {struct devlink_port devlink_port; } ;

/* Variables and functions */
 struct netdevsim* netdev_priv (struct net_device*) ; 

__attribute__((used)) static struct devlink_port *nsim_get_devlink_port(struct net_device *dev)
{
	struct netdevsim *ns = netdev_priv(dev);

	return &ns->nsim_dev_port->devlink_port;
}