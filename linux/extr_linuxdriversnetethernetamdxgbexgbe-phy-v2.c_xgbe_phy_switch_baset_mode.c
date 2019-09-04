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
struct xgbe_phy_data {scalar_t__ port_mode; } ;
typedef  enum xgbe_mode { ____Placeholder_xgbe_mode } xgbe_mode ;

/* Variables and functions */
#define  XGBE_MODE_KR 130 
#define  XGBE_MODE_SGMII_100 129 
#define  XGBE_MODE_SGMII_1000 128 
 scalar_t__ XGBE_PORT_MODE_10GBASE_T ; 
 int xgbe_phy_cur_mode (struct xgbe_prv_data*) ; 

__attribute__((used)) static enum xgbe_mode xgbe_phy_switch_baset_mode(struct xgbe_prv_data *pdata)
{
	struct xgbe_phy_data *phy_data = pdata->phy_data;

	/* No switching if not 10GBase-T */
	if (phy_data->port_mode != XGBE_PORT_MODE_10GBASE_T)
		return xgbe_phy_cur_mode(pdata);

	switch (xgbe_phy_cur_mode(pdata)) {
	case XGBE_MODE_SGMII_100:
	case XGBE_MODE_SGMII_1000:
		return XGBE_MODE_KR;
	case XGBE_MODE_KR:
	default:
		return XGBE_MODE_SGMII_1000;
	}
}