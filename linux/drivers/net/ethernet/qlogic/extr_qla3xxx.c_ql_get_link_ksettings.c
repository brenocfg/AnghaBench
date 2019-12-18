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
typedef  int /*<<< orphan*/  u32 ;
struct ql3_adapter {int /*<<< orphan*/  PHYAddr; int /*<<< orphan*/  flags; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  advertising; int /*<<< orphan*/  supported; } ;
struct TYPE_3__ {int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  autoneg; int /*<<< orphan*/  phy_address; int /*<<< orphan*/  port; } ;
struct ethtool_link_ksettings {TYPE_2__ link_modes; TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  PORT_FIBRE ; 
 int /*<<< orphan*/  PORT_TP ; 
 int /*<<< orphan*/  QL_LINK_OPTICAL ; 
 int /*<<< orphan*/  ethtool_convert_legacy_u32_to_link_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ql3_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  ql_get_auto_cfg_status (struct ql3_adapter*) ; 
 int /*<<< orphan*/  ql_get_full_dup (struct ql3_adapter*) ; 
 int /*<<< orphan*/  ql_get_speed (struct ql3_adapter*) ; 
 int /*<<< orphan*/  ql_supported_modes (struct ql3_adapter*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ql_get_link_ksettings(struct net_device *ndev,
				 struct ethtool_link_ksettings *cmd)
{
	struct ql3_adapter *qdev = netdev_priv(ndev);
	u32 supported, advertising;

	supported = ql_supported_modes(qdev);

	if (test_bit(QL_LINK_OPTICAL, &qdev->flags)) {
		cmd->base.port = PORT_FIBRE;
	} else {
		cmd->base.port = PORT_TP;
		cmd->base.phy_address = qdev->PHYAddr;
	}
	advertising = ql_supported_modes(qdev);
	cmd->base.autoneg = ql_get_auto_cfg_status(qdev);
	cmd->base.speed = ql_get_speed(qdev);
	cmd->base.duplex = ql_get_full_dup(qdev);

	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						supported);
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.advertising,
						advertising);

	return 0;
}