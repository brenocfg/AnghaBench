#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct mlxsw_sp {int dummy; } ;
struct ethtool_link_ksettings {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  Backplane ; 
 int /*<<< orphan*/  FIBRE ; 
 int MLXSW_REG_PTYS_ETH_SPEED_1000BASE_KX ; 
 int MLXSW_REG_PTYS_ETH_SPEED_100GBASE_KR4 ; 
 int MLXSW_REG_PTYS_ETH_SPEED_100GBASE_SR4 ; 
 int MLXSW_REG_PTYS_ETH_SPEED_10GBASE_CR ; 
 int MLXSW_REG_PTYS_ETH_SPEED_10GBASE_KR ; 
 int MLXSW_REG_PTYS_ETH_SPEED_10GBASE_KX4 ; 
 int MLXSW_REG_PTYS_ETH_SPEED_10GBASE_SR ; 
 int MLXSW_REG_PTYS_ETH_SPEED_40GBASE_CR4 ; 
 int MLXSW_REG_PTYS_ETH_SPEED_40GBASE_KR4 ; 
 int MLXSW_REG_PTYS_ETH_SPEED_40GBASE_SR4 ; 
 int MLXSW_REG_PTYS_ETH_SPEED_SGMII ; 
 int /*<<< orphan*/  ethtool_link_ksettings_add_link_mode (struct ethtool_link_ksettings*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  supported ; 

__attribute__((used)) static void
mlxsw_sp1_from_ptys_supported_port(struct mlxsw_sp *mlxsw_sp,
				   u32 ptys_eth_proto,
				   struct ethtool_link_ksettings *cmd)
{
	if (ptys_eth_proto & (MLXSW_REG_PTYS_ETH_SPEED_10GBASE_CR |
			      MLXSW_REG_PTYS_ETH_SPEED_10GBASE_SR |
			      MLXSW_REG_PTYS_ETH_SPEED_40GBASE_CR4 |
			      MLXSW_REG_PTYS_ETH_SPEED_40GBASE_SR4 |
			      MLXSW_REG_PTYS_ETH_SPEED_100GBASE_SR4 |
			      MLXSW_REG_PTYS_ETH_SPEED_SGMII))
		ethtool_link_ksettings_add_link_mode(cmd, supported, FIBRE);

	if (ptys_eth_proto & (MLXSW_REG_PTYS_ETH_SPEED_10GBASE_KR |
			      MLXSW_REG_PTYS_ETH_SPEED_10GBASE_KX4 |
			      MLXSW_REG_PTYS_ETH_SPEED_40GBASE_KR4 |
			      MLXSW_REG_PTYS_ETH_SPEED_100GBASE_KR4 |
			      MLXSW_REG_PTYS_ETH_SPEED_1000BASE_KX))
		ethtool_link_ksettings_add_link_mode(cmd, supported, Backplane);
}