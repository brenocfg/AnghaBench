#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct niu_link_config {int /*<<< orphan*/  autoneg; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  advertising; } ;
struct niu {struct niu_link_config link_config; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  autoneg; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; } ;
struct TYPE_4__ {int /*<<< orphan*/  advertising; } ;
struct ethtool_link_ksettings {TYPE_1__ base; TYPE_2__ link_modes; } ;

/* Variables and functions */
 int /*<<< orphan*/  ethtool_convert_link_mode_to_legacy_u32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct niu* netdev_priv (struct net_device*) ; 
 int niu_init_link (struct niu*) ; 

__attribute__((used)) static int niu_set_link_ksettings(struct net_device *dev,
				  const struct ethtool_link_ksettings *cmd)
{
	struct niu *np = netdev_priv(dev);
	struct niu_link_config *lp = &np->link_config;

	ethtool_convert_link_mode_to_legacy_u32(&lp->advertising,
						cmd->link_modes.advertising);
	lp->speed = cmd->base.speed;
	lp->duplex = cmd->base.duplex;
	lp->autoneg = cmd->base.autoneg;
	return niu_init_link(np);
}