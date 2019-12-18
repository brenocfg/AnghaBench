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
typedef  enum xgbe_mode { ____Placeholder_xgbe_mode } xgbe_mode ;

/* Variables and functions */
#define  SPEED_2500 128 
 int XGBE_MODE_KX_2500 ; 
 int XGBE_MODE_UNKNOWN ; 

__attribute__((used)) static enum xgbe_mode xgbe_phy_get_bp_2500_mode(int speed)
{
	switch (speed) {
	case SPEED_2500:
		return XGBE_MODE_KX_2500;
	default:
		return XGBE_MODE_UNKNOWN;
	}
}