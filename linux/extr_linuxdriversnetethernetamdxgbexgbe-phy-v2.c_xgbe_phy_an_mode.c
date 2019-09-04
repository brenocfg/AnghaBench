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
struct xgbe_phy_data {int port_mode; scalar_t__ redrv; } ;
typedef  enum xgbe_an_mode { ____Placeholder_xgbe_an_mode } xgbe_an_mode ;

/* Variables and functions */
 int XGBE_AN_MODE_CL37 ; 
 int XGBE_AN_MODE_CL37_SGMII ; 
 int XGBE_AN_MODE_CL73 ; 
 int XGBE_AN_MODE_CL73_REDRV ; 
 int XGBE_AN_MODE_NONE ; 
#define  XGBE_PORT_MODE_1000BASE_T 135 
#define  XGBE_PORT_MODE_1000BASE_X 134 
#define  XGBE_PORT_MODE_10GBASE_R 133 
#define  XGBE_PORT_MODE_10GBASE_T 132 
#define  XGBE_PORT_MODE_BACKPLANE 131 
#define  XGBE_PORT_MODE_BACKPLANE_2500 130 
#define  XGBE_PORT_MODE_NBASE_T 129 
#define  XGBE_PORT_MODE_SFP 128 
 int xgbe_phy_an_sfp_mode (struct xgbe_phy_data*) ; 

__attribute__((used)) static enum xgbe_an_mode xgbe_phy_an_mode(struct xgbe_prv_data *pdata)
{
	struct xgbe_phy_data *phy_data = pdata->phy_data;

	/* A KR re-driver will always require CL73 AN */
	if (phy_data->redrv)
		return XGBE_AN_MODE_CL73_REDRV;

	switch (phy_data->port_mode) {
	case XGBE_PORT_MODE_BACKPLANE:
		return XGBE_AN_MODE_CL73;
	case XGBE_PORT_MODE_BACKPLANE_2500:
		return XGBE_AN_MODE_NONE;
	case XGBE_PORT_MODE_1000BASE_T:
		return XGBE_AN_MODE_CL37_SGMII;
	case XGBE_PORT_MODE_1000BASE_X:
		return XGBE_AN_MODE_CL37;
	case XGBE_PORT_MODE_NBASE_T:
		return XGBE_AN_MODE_CL37_SGMII;
	case XGBE_PORT_MODE_10GBASE_T:
		return XGBE_AN_MODE_CL73;
	case XGBE_PORT_MODE_10GBASE_R:
		return XGBE_AN_MODE_NONE;
	case XGBE_PORT_MODE_SFP:
		return xgbe_phy_an_sfp_mode(phy_data);
	default:
		return XGBE_AN_MODE_NONE;
	}
}