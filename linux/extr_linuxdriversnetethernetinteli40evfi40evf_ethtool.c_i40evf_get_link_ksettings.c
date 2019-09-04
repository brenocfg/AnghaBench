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
struct net_device {int dummy; } ;
struct i40evf_adapter {int link_speed; } ;
struct TYPE_2__ {int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  port; int /*<<< orphan*/  autoneg; } ;
struct ethtool_link_ksettings {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int /*<<< orphan*/  DUPLEX_FULL ; 
#define  I40E_LINK_SPEED_100MB 133 
#define  I40E_LINK_SPEED_10GB 132 
#define  I40E_LINK_SPEED_1GB 131 
#define  I40E_LINK_SPEED_20GB 130 
#define  I40E_LINK_SPEED_25GB 129 
#define  I40E_LINK_SPEED_40GB 128 
 int /*<<< orphan*/  PORT_NONE ; 
 int /*<<< orphan*/  SPEED_100 ; 
 int /*<<< orphan*/  SPEED_1000 ; 
 int /*<<< orphan*/  SPEED_10000 ; 
 int /*<<< orphan*/  SPEED_20000 ; 
 int /*<<< orphan*/  SPEED_40000 ; 
 int /*<<< orphan*/  ethtool_link_ksettings_zero_link_mode (struct ethtool_link_ksettings*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*) ; 
 struct i40evf_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  supported ; 

__attribute__((used)) static int i40evf_get_link_ksettings(struct net_device *netdev,
				     struct ethtool_link_ksettings *cmd)
{
	struct i40evf_adapter *adapter = netdev_priv(netdev);

	ethtool_link_ksettings_zero_link_mode(cmd, supported);
	cmd->base.autoneg = AUTONEG_DISABLE;
	cmd->base.port = PORT_NONE;
	/* Set speed and duplex */
	switch (adapter->link_speed) {
	case I40E_LINK_SPEED_40GB:
		cmd->base.speed = SPEED_40000;
		break;
	case I40E_LINK_SPEED_25GB:
#ifdef SPEED_25000
		cmd->base.speed = SPEED_25000;
#else
		netdev_info(netdev,
			    "Speed is 25G, display not supported by this version of ethtool.\n");
#endif
		break;
	case I40E_LINK_SPEED_20GB:
		cmd->base.speed = SPEED_20000;
		break;
	case I40E_LINK_SPEED_10GB:
		cmd->base.speed = SPEED_10000;
		break;
	case I40E_LINK_SPEED_1GB:
		cmd->base.speed = SPEED_1000;
		break;
	case I40E_LINK_SPEED_100MB:
		cmd->base.speed = SPEED_100;
		break;
	default:
		break;
	}
	cmd->base.duplex = DUPLEX_FULL;

	return 0;
}