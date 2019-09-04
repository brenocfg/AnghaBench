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
struct mvpp2_port {int phy_interface; int /*<<< orphan*/  comphy; } ;
typedef  enum phy_mode { ____Placeholder_phy_mode } phy_mode ;

/* Variables and functions */
 int EINVAL ; 
#define  PHY_INTERFACE_MODE_1000BASEX 131 
#define  PHY_INTERFACE_MODE_10GKR 130 
#define  PHY_INTERFACE_MODE_2500BASEX 129 
#define  PHY_INTERFACE_MODE_SGMII 128 
 int PHY_MODE_10GKR ; 
 int PHY_MODE_2500SGMII ; 
 int PHY_MODE_SGMII ; 
 int phy_power_on (int /*<<< orphan*/ ) ; 
 int phy_set_mode (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mvpp22_comphy_init(struct mvpp2_port *port)
{
	enum phy_mode mode;
	int ret;

	if (!port->comphy)
		return 0;

	switch (port->phy_interface) {
	case PHY_INTERFACE_MODE_SGMII:
	case PHY_INTERFACE_MODE_1000BASEX:
		mode = PHY_MODE_SGMII;
		break;
	case PHY_INTERFACE_MODE_2500BASEX:
		mode = PHY_MODE_2500SGMII;
		break;
	case PHY_INTERFACE_MODE_10GKR:
		mode = PHY_MODE_10GKR;
		break;
	default:
		return -EINVAL;
	}

	ret = phy_set_mode(port->comphy, mode);
	if (ret)
		return ret;

	return phy_power_on(port->comphy);
}