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
struct xgbe_phy_data {int dummy; } ;
typedef  enum xgbe_mode { ____Placeholder_xgbe_mode } xgbe_mode ;

/* Variables and functions */
#define  SPEED_100 131 
#define  SPEED_1000 130 
#define  SPEED_10000 129 
#define  SPEED_2500 128 
 int XGBE_MODE_KR ; 
 int XGBE_MODE_KX_2500 ; 
 int XGBE_MODE_SGMII_100 ; 
 int XGBE_MODE_SGMII_1000 ; 
 int XGBE_MODE_UNKNOWN ; 

__attribute__((used)) static enum xgbe_mode xgbe_phy_get_baset_mode(struct xgbe_phy_data *phy_data,
					      int speed)
{
	switch (speed) {
	case SPEED_100:
		return XGBE_MODE_SGMII_100;
	case SPEED_1000:
		return XGBE_MODE_SGMII_1000;
	case SPEED_2500:
		return XGBE_MODE_KX_2500;
	case SPEED_10000:
		return XGBE_MODE_KR;
	default:
		return XGBE_MODE_UNKNOWN;
	}
}