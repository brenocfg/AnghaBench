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
struct TYPE_2__ {scalar_t__ autoneg; } ;
struct niu {TYPE_1__ link_config; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct niu* netdev_priv (struct net_device*) ; 
 int niu_init_link (struct niu*) ; 

__attribute__((used)) static int niu_nway_reset(struct net_device *dev)
{
	struct niu *np = netdev_priv(dev);

	if (np->link_config.autoneg)
		return niu_init_link(np);

	return 0;
}