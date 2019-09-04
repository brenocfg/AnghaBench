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

/* Variables and functions */
#define  SPEED_1000 129 
#define  SPEED_10000 128 

__attribute__((used)) static bool xgbe_phy_valid_speed_bp_mode(int speed)
{
	switch (speed) {
	case SPEED_1000:
	case SPEED_10000:
		return true;
	default:
		return false;
	}
}