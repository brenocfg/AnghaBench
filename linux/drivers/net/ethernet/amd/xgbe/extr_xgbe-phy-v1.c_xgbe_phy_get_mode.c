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
struct xgbe_phy_data {int /*<<< orphan*/  speed_set; } ;
typedef  enum xgbe_mode { ____Placeholder_xgbe_mode } xgbe_mode ;

/* Variables and functions */
#define  SPEED_1000 130 
#define  SPEED_10000 129 
#define  SPEED_2500 128 
 int XGBE_MODE_KR ; 
 int XGBE_MODE_KX_1000 ; 
 int XGBE_MODE_KX_2500 ; 
 int XGBE_MODE_UNKNOWN ; 
 int /*<<< orphan*/  XGBE_SPEEDSET_1000_10000 ; 
 int /*<<< orphan*/  XGBE_SPEEDSET_2500_10000 ; 

__attribute__((used)) static enum xgbe_mode xgbe_phy_get_mode(struct xgbe_prv_data *pdata,
					int speed)
{
	struct xgbe_phy_data *phy_data = pdata->phy_data;

	switch (speed) {
	case SPEED_1000:
		return (phy_data->speed_set == XGBE_SPEEDSET_1000_10000)
			? XGBE_MODE_KX_1000 : XGBE_MODE_UNKNOWN;
	case SPEED_2500:
		return (phy_data->speed_set == XGBE_SPEEDSET_2500_10000)
			? XGBE_MODE_KX_2500 : XGBE_MODE_UNKNOWN;
	case SPEED_10000:
		return XGBE_MODE_KR;
	default:
		return XGBE_MODE_UNKNOWN;
	}
}