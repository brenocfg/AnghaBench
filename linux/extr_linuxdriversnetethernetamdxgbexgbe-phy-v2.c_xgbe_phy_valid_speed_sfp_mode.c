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
struct xgbe_phy_data {int /*<<< orphan*/  sfp_speed; } ;

/* Variables and functions */
#define  SPEED_100 130 
#define  SPEED_1000 129 
#define  SPEED_10000 128 
 int /*<<< orphan*/  XGBE_SFP_SPEED_1000 ; 
 int /*<<< orphan*/  XGBE_SFP_SPEED_10000 ; 
 int /*<<< orphan*/  XGBE_SFP_SPEED_100_1000 ; 

__attribute__((used)) static bool xgbe_phy_valid_speed_sfp_mode(struct xgbe_phy_data *phy_data,
					  int speed)
{
	switch (speed) {
	case SPEED_100:
		return (phy_data->sfp_speed == XGBE_SFP_SPEED_100_1000);
	case SPEED_1000:
		return ((phy_data->sfp_speed == XGBE_SFP_SPEED_100_1000) ||
			(phy_data->sfp_speed == XGBE_SFP_SPEED_1000));
	case SPEED_10000:
		return (phy_data->sfp_speed == XGBE_SFP_SPEED_10000);
	default:
		return false;
	}
}