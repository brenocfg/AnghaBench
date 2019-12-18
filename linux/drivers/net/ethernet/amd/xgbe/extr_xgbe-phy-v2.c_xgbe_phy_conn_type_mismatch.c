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
struct xgbe_phy_data {int port_mode; int /*<<< orphan*/  conn_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  XGBE_CONN_TYPE_BACKPLANE ; 
 int /*<<< orphan*/  XGBE_CONN_TYPE_MDIO ; 
 int /*<<< orphan*/  XGBE_CONN_TYPE_SFP ; 
#define  XGBE_PORT_MODE_1000BASE_T 135 
#define  XGBE_PORT_MODE_1000BASE_X 134 
#define  XGBE_PORT_MODE_10GBASE_R 133 
#define  XGBE_PORT_MODE_10GBASE_T 132 
#define  XGBE_PORT_MODE_BACKPLANE 131 
#define  XGBE_PORT_MODE_BACKPLANE_2500 130 
#define  XGBE_PORT_MODE_NBASE_T 129 
#define  XGBE_PORT_MODE_SFP 128 

__attribute__((used)) static bool xgbe_phy_conn_type_mismatch(struct xgbe_prv_data *pdata)
{
	struct xgbe_phy_data *phy_data = pdata->phy_data;

	switch (phy_data->port_mode) {
	case XGBE_PORT_MODE_BACKPLANE:
	case XGBE_PORT_MODE_BACKPLANE_2500:
		if (phy_data->conn_type == XGBE_CONN_TYPE_BACKPLANE)
			return false;
		break;
	case XGBE_PORT_MODE_1000BASE_T:
	case XGBE_PORT_MODE_1000BASE_X:
	case XGBE_PORT_MODE_NBASE_T:
	case XGBE_PORT_MODE_10GBASE_T:
	case XGBE_PORT_MODE_10GBASE_R:
		if (phy_data->conn_type == XGBE_CONN_TYPE_MDIO)
			return false;
		break;
	case XGBE_PORT_MODE_SFP:
		if (phy_data->conn_type == XGBE_CONN_TYPE_SFP)
			return false;
		break;
	default:
		break;
	}

	return true;
}