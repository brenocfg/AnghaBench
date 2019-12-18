#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* ops; } ;
struct TYPE_4__ {scalar_t__ autoneg; } ;
struct port_info {TYPE_3__ phy; TYPE_1__ link_config; } ;
struct net_device {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* autoneg_restart ) (TYPE_3__*) ;} ;

/* Variables and functions */
 scalar_t__ AUTONEG_ENABLE ; 
 int EAGAIN ; 
 int EINVAL ; 
 struct port_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

__attribute__((used)) static int restart_autoneg(struct net_device *dev)
{
	struct port_info *p = netdev_priv(dev);

	if (!netif_running(dev))
		return -EAGAIN;
	if (p->link_config.autoneg != AUTONEG_ENABLE)
		return -EINVAL;
	p->phy.ops->autoneg_restart(&p->phy);
	return 0;
}