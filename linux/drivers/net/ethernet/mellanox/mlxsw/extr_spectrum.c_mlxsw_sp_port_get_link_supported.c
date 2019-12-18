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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct mlxsw_sp_port_type_speed_ops {int /*<<< orphan*/  (* from_ptys_link ) (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* from_ptys_supported_port ) (struct mlxsw_sp*,int /*<<< orphan*/ ,struct ethtool_link_ksettings*) ;} ;
struct mlxsw_sp {struct mlxsw_sp_port_type_speed_ops* port_type_speed_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  supported; } ;
struct ethtool_link_ksettings {TYPE_1__ link_modes; } ;

/* Variables and functions */
 int /*<<< orphan*/  Asym_Pause ; 
 int /*<<< orphan*/  Autoneg ; 
 int /*<<< orphan*/  Pause ; 
 int /*<<< orphan*/  ethtool_link_ksettings_add_link_mode (struct ethtool_link_ksettings*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct mlxsw_sp*,int /*<<< orphan*/ ,struct ethtool_link_ksettings*) ; 
 int /*<<< orphan*/  stub2 (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  supported ; 

__attribute__((used)) static void
mlxsw_sp_port_get_link_supported(struct mlxsw_sp *mlxsw_sp, u32 eth_proto_cap,
				 u8 width, struct ethtool_link_ksettings *cmd)
{
	const struct mlxsw_sp_port_type_speed_ops *ops;

	ops = mlxsw_sp->port_type_speed_ops;

	ethtool_link_ksettings_add_link_mode(cmd, supported, Asym_Pause);
	ethtool_link_ksettings_add_link_mode(cmd, supported, Autoneg);
	ethtool_link_ksettings_add_link_mode(cmd, supported, Pause);

	ops->from_ptys_supported_port(mlxsw_sp, eth_proto_cap, cmd);
	ops->from_ptys_link(mlxsw_sp, eth_proto_cap, width,
			    cmd->link_modes.supported);
}