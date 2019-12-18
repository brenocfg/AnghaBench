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

/* Variables and functions */
#define  SPEED_1000 130 
#define  SPEED_10000 129 
#define  SPEED_2500 128 
 int /*<<< orphan*/  XGBE_SPEEDSET_1000_10000 ; 
 int /*<<< orphan*/  XGBE_SPEEDSET_2500_10000 ; 

__attribute__((used)) static bool xgbe_phy_valid_speed(struct xgbe_prv_data *pdata, int speed)
{
	struct xgbe_phy_data *phy_data = pdata->phy_data;

	switch (speed) {
	case SPEED_1000:
		if (phy_data->speed_set != XGBE_SPEEDSET_1000_10000)
			return false;
		return true;
	case SPEED_2500:
		if (phy_data->speed_set != XGBE_SPEEDSET_2500_10000)
			return false;
		return true;
	case SPEED_10000:
		return true;
	default:
		return false;
	}
}