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
struct xgbe_prv_data {int an_mode; } ;
typedef  enum xgbe_mode { ____Placeholder_xgbe_mode } xgbe_mode ;

/* Variables and functions */
#define  XGBE_AN_MODE_CL37 131 
#define  XGBE_AN_MODE_CL37_SGMII 130 
#define  XGBE_AN_MODE_CL73 129 
#define  XGBE_AN_MODE_CL73_REDRV 128 
 int XGBE_MODE_UNKNOWN ; 
 int xgbe_phy_an37_outcome (struct xgbe_prv_data*) ; 
 int xgbe_phy_an37_sgmii_outcome (struct xgbe_prv_data*) ; 
 int xgbe_phy_an73_outcome (struct xgbe_prv_data*) ; 
 int xgbe_phy_an73_redrv_outcome (struct xgbe_prv_data*) ; 

__attribute__((used)) static enum xgbe_mode xgbe_phy_an_outcome(struct xgbe_prv_data *pdata)
{
	switch (pdata->an_mode) {
	case XGBE_AN_MODE_CL73:
		return xgbe_phy_an73_outcome(pdata);
	case XGBE_AN_MODE_CL73_REDRV:
		return xgbe_phy_an73_redrv_outcome(pdata);
	case XGBE_AN_MODE_CL37:
		return xgbe_phy_an37_outcome(pdata);
	case XGBE_AN_MODE_CL37_SGMII:
		return xgbe_phy_an37_sgmii_outcome(pdata);
	default:
		return XGBE_MODE_UNKNOWN;
	}
}