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
struct xgbe_prv_data {struct xgbe_phy_data* phy_data; } ;
struct xgbe_phy_data {int port_mode; int port_speeds; } ;

/* Variables and functions */
 int XGBE_PHY_PORT_SPEED_100 ; 
 int XGBE_PHY_PORT_SPEED_1000 ; 
 int XGBE_PHY_PORT_SPEED_10000 ; 
 int XGBE_PHY_PORT_SPEED_2500 ; 
#define  XGBE_PORT_MODE_1000BASE_T 135 
#define  XGBE_PORT_MODE_1000BASE_X 134 
#define  XGBE_PORT_MODE_10GBASE_R 133 
#define  XGBE_PORT_MODE_10GBASE_T 132 
#define  XGBE_PORT_MODE_BACKPLANE 131 
#define  XGBE_PORT_MODE_BACKPLANE_2500 130 
#define  XGBE_PORT_MODE_NBASE_T 129 
#define  XGBE_PORT_MODE_SFP 128 

__attribute__((used)) static bool xgbe_phy_port_mode_mismatch(struct xgbe_prv_data *pdata)
{
	struct xgbe_phy_data *phy_data = pdata->phy_data;

	switch (phy_data->port_mode) {
	case XGBE_PORT_MODE_BACKPLANE:
		if ((phy_data->port_speeds & XGBE_PHY_PORT_SPEED_1000) ||
		    (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_10000))
			return false;
		break;
	case XGBE_PORT_MODE_BACKPLANE_2500:
		if (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_2500)
			return false;
		break;
	case XGBE_PORT_MODE_1000BASE_T:
		if ((phy_data->port_speeds & XGBE_PHY_PORT_SPEED_100) ||
		    (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_1000))
			return false;
		break;
	case XGBE_PORT_MODE_1000BASE_X:
		if (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_1000)
			return false;
		break;
	case XGBE_PORT_MODE_NBASE_T:
		if ((phy_data->port_speeds & XGBE_PHY_PORT_SPEED_100) ||
		    (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_1000) ||
		    (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_2500))
			return false;
		break;
	case XGBE_PORT_MODE_10GBASE_T:
		if ((phy_data->port_speeds & XGBE_PHY_PORT_SPEED_100) ||
		    (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_1000) ||
		    (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_10000))
			return false;
		break;
	case XGBE_PORT_MODE_10GBASE_R:
		if (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_10000)
			return false;
		break;
	case XGBE_PORT_MODE_SFP:
		if ((phy_data->port_speeds & XGBE_PHY_PORT_SPEED_100) ||
		    (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_1000) ||
		    (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_10000))
			return false;
		break;
	default:
		break;
	}

	return true;
}