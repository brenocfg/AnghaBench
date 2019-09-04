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
struct xgbe_phy_data {int port_mode; } ;
typedef  enum xgbe_mode { ____Placeholder_xgbe_mode } xgbe_mode ;

/* Variables and functions */
 int XGBE_MODE_UNKNOWN ; 
#define  XGBE_PORT_MODE_1000BASE_T 135 
#define  XGBE_PORT_MODE_1000BASE_X 134 
#define  XGBE_PORT_MODE_10GBASE_R 133 
#define  XGBE_PORT_MODE_10GBASE_T 132 
#define  XGBE_PORT_MODE_BACKPLANE 131 
#define  XGBE_PORT_MODE_BACKPLANE_2500 130 
#define  XGBE_PORT_MODE_NBASE_T 129 
#define  XGBE_PORT_MODE_SFP 128 
 int xgbe_phy_cur_mode (struct xgbe_prv_data*) ; 
 int xgbe_phy_switch_baset_mode (struct xgbe_prv_data*) ; 
 int xgbe_phy_switch_bp_2500_mode (struct xgbe_prv_data*) ; 
 int xgbe_phy_switch_bp_mode (struct xgbe_prv_data*) ; 

__attribute__((used)) static enum xgbe_mode xgbe_phy_switch_mode(struct xgbe_prv_data *pdata)
{
	struct xgbe_phy_data *phy_data = pdata->phy_data;

	switch (phy_data->port_mode) {
	case XGBE_PORT_MODE_BACKPLANE:
		return xgbe_phy_switch_bp_mode(pdata);
	case XGBE_PORT_MODE_BACKPLANE_2500:
		return xgbe_phy_switch_bp_2500_mode(pdata);
	case XGBE_PORT_MODE_1000BASE_T:
	case XGBE_PORT_MODE_NBASE_T:
	case XGBE_PORT_MODE_10GBASE_T:
		return xgbe_phy_switch_baset_mode(pdata);
	case XGBE_PORT_MODE_1000BASE_X:
	case XGBE_PORT_MODE_10GBASE_R:
	case XGBE_PORT_MODE_SFP:
		/* No switching, so just return current mode */
		return xgbe_phy_cur_mode(pdata);
	default:
		return XGBE_MODE_UNKNOWN;
	}
}