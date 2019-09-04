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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct TYPE_3__ {int speed; int /*<<< orphan*/  duplex; } ;
struct ethtool_link_ksettings {TYPE_1__ base; } ;
struct TYPE_4__ {int mask; int speed; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  DUPLEX_UNKNOWN ; 
 int MLXSW_SX_PORT_LINK_MODE_LEN ; 
 int SPEED_UNKNOWN ; 
 TYPE_2__* mlxsw_sx_port_link_mode ; 

__attribute__((used)) static void mlxsw_sx_from_ptys_speed_duplex(bool carrier_ok, u32 ptys_eth_proto,
					    struct ethtool_link_ksettings *cmd)
{
	u32 speed = SPEED_UNKNOWN;
	u8 duplex = DUPLEX_UNKNOWN;
	int i;

	if (!carrier_ok)
		goto out;

	for (i = 0; i < MLXSW_SX_PORT_LINK_MODE_LEN; i++) {
		if (ptys_eth_proto & mlxsw_sx_port_link_mode[i].mask) {
			speed = mlxsw_sx_port_link_mode[i].speed;
			duplex = DUPLEX_FULL;
			break;
		}
	}
out:
	cmd->base.speed = speed;
	cmd->base.duplex = duplex;
}