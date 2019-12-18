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
typedef  int u8 ;
typedef  int u32 ;
struct ethtool_link_ksettings {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUI ; 
 int /*<<< orphan*/  BNC ; 
 int /*<<< orphan*/  Backplane ; 
 int /*<<< orphan*/  FIBRE ; 
 int /*<<< orphan*/  MII ; 
 int /*<<< orphan*/  MLX5E_1000BASE_CX_SGMII ; 
 int /*<<< orphan*/  MLX5E_1000BASE_KX ; 
 int /*<<< orphan*/  MLX5E_100GBASE_KR4 ; 
 int /*<<< orphan*/  MLX5E_100GBASE_SR4 ; 
 int /*<<< orphan*/  MLX5E_10GBASE_CR ; 
 int /*<<< orphan*/  MLX5E_10GBASE_KR ; 
 int /*<<< orphan*/  MLX5E_10GBASE_KX4 ; 
 int /*<<< orphan*/  MLX5E_10GBASE_SR ; 
 int /*<<< orphan*/  MLX5E_40GBASE_CR4 ; 
 int /*<<< orphan*/  MLX5E_40GBASE_KR4 ; 
 int /*<<< orphan*/  MLX5E_40GBASE_SR4 ; 
 int MLX5E_CONNECTOR_TYPE_NUMBER ; 
#define  MLX5E_PORT_AUI 135 
#define  MLX5E_PORT_BNC 134 
#define  MLX5E_PORT_DA 133 
#define  MLX5E_PORT_FIBRE 132 
#define  MLX5E_PORT_MII 131 
#define  MLX5E_PORT_NONE 130 
#define  MLX5E_PORT_OTHER 129 
#define  MLX5E_PORT_TP 128 
 int MLX5E_PROT_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TP ; 
 int /*<<< orphan*/  advertising ; 
 int /*<<< orphan*/  ethtool_link_ksettings_add_link_mode (struct ethtool_link_ksettings*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  supported ; 

__attribute__((used)) static void ptys2ethtool_supported_advertised_port(struct ethtool_link_ksettings *link_ksettings,
						   u32 eth_proto_cap,
						   u8 connector_type)
{
	if (!connector_type || connector_type >= MLX5E_CONNECTOR_TYPE_NUMBER) {
		if (eth_proto_cap & (MLX5E_PROT_MASK(MLX5E_10GBASE_CR)
				   | MLX5E_PROT_MASK(MLX5E_10GBASE_SR)
				   | MLX5E_PROT_MASK(MLX5E_40GBASE_CR4)
				   | MLX5E_PROT_MASK(MLX5E_40GBASE_SR4)
				   | MLX5E_PROT_MASK(MLX5E_100GBASE_SR4)
				   | MLX5E_PROT_MASK(MLX5E_1000BASE_CX_SGMII))) {
			ethtool_link_ksettings_add_link_mode(link_ksettings,
							     supported,
							     FIBRE);
			ethtool_link_ksettings_add_link_mode(link_ksettings,
							     advertising,
							     FIBRE);
		}

		if (eth_proto_cap & (MLX5E_PROT_MASK(MLX5E_100GBASE_KR4)
				   | MLX5E_PROT_MASK(MLX5E_40GBASE_KR4)
				   | MLX5E_PROT_MASK(MLX5E_10GBASE_KR)
				   | MLX5E_PROT_MASK(MLX5E_10GBASE_KX4)
				   | MLX5E_PROT_MASK(MLX5E_1000BASE_KX))) {
			ethtool_link_ksettings_add_link_mode(link_ksettings,
							     supported,
							     Backplane);
			ethtool_link_ksettings_add_link_mode(link_ksettings,
							     advertising,
							     Backplane);
		}
		return;
	}

	switch (connector_type) {
	case MLX5E_PORT_TP:
		ethtool_link_ksettings_add_link_mode(link_ksettings,
						     supported, TP);
		ethtool_link_ksettings_add_link_mode(link_ksettings,
						     advertising, TP);
		break;
	case MLX5E_PORT_AUI:
		ethtool_link_ksettings_add_link_mode(link_ksettings,
						     supported, AUI);
		ethtool_link_ksettings_add_link_mode(link_ksettings,
						     advertising, AUI);
		break;
	case MLX5E_PORT_BNC:
		ethtool_link_ksettings_add_link_mode(link_ksettings,
						     supported, BNC);
		ethtool_link_ksettings_add_link_mode(link_ksettings,
						     advertising, BNC);
		break;
	case MLX5E_PORT_MII:
		ethtool_link_ksettings_add_link_mode(link_ksettings,
						     supported, MII);
		ethtool_link_ksettings_add_link_mode(link_ksettings,
						     advertising, MII);
		break;
	case MLX5E_PORT_FIBRE:
		ethtool_link_ksettings_add_link_mode(link_ksettings,
						     supported, FIBRE);
		ethtool_link_ksettings_add_link_mode(link_ksettings,
						     advertising, FIBRE);
		break;
	case MLX5E_PORT_DA:
		ethtool_link_ksettings_add_link_mode(link_ksettings,
						     supported, Backplane);
		ethtool_link_ksettings_add_link_mode(link_ksettings,
						     advertising, Backplane);
		break;
	case MLX5E_PORT_NONE:
	case MLX5E_PORT_OTHER:
	default:
		break;
	}
}