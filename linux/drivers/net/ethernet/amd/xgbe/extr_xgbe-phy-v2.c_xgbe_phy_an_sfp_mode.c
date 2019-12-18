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
struct xgbe_phy_data {int sfp_base; } ;
typedef  enum xgbe_an_mode { ____Placeholder_xgbe_an_mode } xgbe_an_mode ;

/* Variables and functions */
 int XGBE_AN_MODE_CL37 ; 
 int XGBE_AN_MODE_CL37_SGMII ; 
 int XGBE_AN_MODE_NONE ; 
#define  XGBE_SFP_BASE_1000_CX 131 
#define  XGBE_SFP_BASE_1000_LX 130 
#define  XGBE_SFP_BASE_1000_SX 129 
#define  XGBE_SFP_BASE_1000_T 128 

__attribute__((used)) static enum xgbe_an_mode xgbe_phy_an_sfp_mode(struct xgbe_phy_data *phy_data)
{
	switch (phy_data->sfp_base) {
	case XGBE_SFP_BASE_1000_T:
		return XGBE_AN_MODE_CL37_SGMII;
	case XGBE_SFP_BASE_1000_SX:
	case XGBE_SFP_BASE_1000_LX:
	case XGBE_SFP_BASE_1000_CX:
		return XGBE_AN_MODE_CL37;
	default:
		return XGBE_AN_MODE_NONE;
	}
}