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
struct xgbe_phy_data {int /*<<< orphan*/  port_mode; } ;

/* Variables and functions */
#define  SPEED_100 131 
#define  SPEED_1000 130 
#define  SPEED_10000 129 
#define  SPEED_2500 128 
 int /*<<< orphan*/  XGBE_PORT_MODE_10GBASE_T ; 
 int /*<<< orphan*/  XGBE_PORT_MODE_NBASE_T ; 

__attribute__((used)) static bool xgbe_phy_valid_speed_baset_mode(struct xgbe_phy_data *phy_data,
					    int speed)
{
	switch (speed) {
	case SPEED_100:
	case SPEED_1000:
		return true;
	case SPEED_2500:
		return (phy_data->port_mode == XGBE_PORT_MODE_NBASE_T);
	case SPEED_10000:
		return (phy_data->port_mode == XGBE_PORT_MODE_10GBASE_T);
	default:
		return false;
	}
}