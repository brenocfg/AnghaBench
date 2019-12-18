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
typedef  int /*<<< orphan*/  u32 ;
struct mlxsw_sp {int dummy; } ;
struct TYPE_2__ {scalar_t__ speed; int /*<<< orphan*/  duplex; } ;
struct ethtool_link_ksettings {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  DUPLEX_UNKNOWN ; 
 scalar_t__ SPEED_UNKNOWN ; 
 scalar_t__ mlxsw_sp1_from_ptys_speed (struct mlxsw_sp*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mlxsw_sp1_from_ptys_speed_duplex(struct mlxsw_sp *mlxsw_sp, bool carrier_ok,
				 u32 ptys_eth_proto,
				 struct ethtool_link_ksettings *cmd)
{
	cmd->base.speed = SPEED_UNKNOWN;
	cmd->base.duplex = DUPLEX_UNKNOWN;

	if (!carrier_ok)
		return;

	cmd->base.speed = mlxsw_sp1_from_ptys_speed(mlxsw_sp, ptys_eth_proto);
	if (cmd->base.speed != SPEED_UNKNOWN)
		cmd->base.duplex = DUPLEX_FULL;
}