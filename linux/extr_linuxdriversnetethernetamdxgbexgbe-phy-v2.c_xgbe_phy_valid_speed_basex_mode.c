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
#define  SPEED_1000 129 
#define  SPEED_10000 128 
 int /*<<< orphan*/  XGBE_PORT_MODE_1000BASE_X ; 
 int /*<<< orphan*/  XGBE_PORT_MODE_10GBASE_R ; 

__attribute__((used)) static bool xgbe_phy_valid_speed_basex_mode(struct xgbe_phy_data *phy_data,
					    int speed)
{
	switch (speed) {
	case SPEED_1000:
		return (phy_data->port_mode == XGBE_PORT_MODE_1000BASE_X);
	case SPEED_10000:
		return (phy_data->port_mode == XGBE_PORT_MODE_10GBASE_R);
	default:
		return false;
	}
}