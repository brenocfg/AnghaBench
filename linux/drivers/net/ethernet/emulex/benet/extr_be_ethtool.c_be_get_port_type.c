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
struct TYPE_2__ {int interface_type; int cable_type; } ;
struct be_adapter {TYPE_1__ phy; } ;

/* Variables and functions */
#define  PHY_TYPE_BASET_10GB 135 
#define  PHY_TYPE_BASET_1GB 134 
#define  PHY_TYPE_BASEX_1GB 133 
#define  PHY_TYPE_QSFP 132 
#define  PHY_TYPE_SFP_1GB 131 
#define  PHY_TYPE_SFP_PLUS_10GB 130 
#define  PHY_TYPE_SGMII 129 
#define  PHY_TYPE_XFP_10GB 128 
 int /*<<< orphan*/  PORT_DA ; 
 int /*<<< orphan*/  PORT_FIBRE ; 
 int /*<<< orphan*/  PORT_OTHER ; 
 int /*<<< orphan*/  PORT_TP ; 
 int QSFP_PLUS_CR4_CABLE ; 
 int SFP_PLUS_COPPER_CABLE ; 

__attribute__((used)) static u32 be_get_port_type(struct be_adapter *adapter)
{
	u32 port;

	switch (adapter->phy.interface_type) {
	case PHY_TYPE_BASET_1GB:
	case PHY_TYPE_BASEX_1GB:
	case PHY_TYPE_SGMII:
		port = PORT_TP;
		break;
	case PHY_TYPE_SFP_PLUS_10GB:
		if (adapter->phy.cable_type & SFP_PLUS_COPPER_CABLE)
			port = PORT_DA;
		else
			port = PORT_FIBRE;
		break;
	case PHY_TYPE_QSFP:
		if (adapter->phy.cable_type & QSFP_PLUS_CR4_CABLE)
			port = PORT_DA;
		else
			port = PORT_FIBRE;
		break;
	case PHY_TYPE_XFP_10GB:
	case PHY_TYPE_SFP_1GB:
		port = PORT_FIBRE;
		break;
	case PHY_TYPE_BASET_10GB:
		port = PORT_TP;
		break;
	default:
		port = PORT_OTHER;
	}

	return port;
}