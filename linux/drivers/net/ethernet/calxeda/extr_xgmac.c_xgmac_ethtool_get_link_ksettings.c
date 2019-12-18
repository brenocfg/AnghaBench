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
struct net_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  advertising; int /*<<< orphan*/  supported; } ;
struct TYPE_3__ {int speed; int /*<<< orphan*/  duplex; scalar_t__ autoneg; } ;
struct ethtool_link_ksettings {TYPE_2__ link_modes; TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  ethtool_convert_legacy_u32_to_link_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xgmac_ethtool_get_link_ksettings(struct net_device *dev,
					    struct ethtool_link_ksettings *cmd)
{
	cmd->base.autoneg = 0;
	cmd->base.duplex = DUPLEX_FULL;
	cmd->base.speed = 10000;
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported, 0);
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.advertising, 0);
	return 0;
}