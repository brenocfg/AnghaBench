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
struct TYPE_2__ {int /*<<< orphan*/  supported; } ;
struct ethtool_link_ksettings {TYPE_1__ link_modes; } ;

/* Variables and functions */
 int /*<<< orphan*/  Asym_Pause ; 
 int /*<<< orphan*/  Autoneg ; 
 int /*<<< orphan*/  Pause ; 
 int /*<<< orphan*/  ethtool_link_ksettings_add_link_mode (struct ethtool_link_ksettings*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_from_ptys_link (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_from_ptys_supported_port (int /*<<< orphan*/ ,struct ethtool_link_ksettings*) ; 
 int /*<<< orphan*/  supported ; 

__attribute__((used)) static void mlxsw_sp_port_get_link_supported(u32 eth_proto_cap,
					     struct ethtool_link_ksettings *cmd)
{
	ethtool_link_ksettings_add_link_mode(cmd, supported, Asym_Pause);
	ethtool_link_ksettings_add_link_mode(cmd, supported, Autoneg);
	ethtool_link_ksettings_add_link_mode(cmd, supported, Pause);

	mlxsw_sp_from_ptys_supported_port(eth_proto_cap, cmd);
	mlxsw_sp_from_ptys_link(eth_proto_cap, cmd->link_modes.supported);
}