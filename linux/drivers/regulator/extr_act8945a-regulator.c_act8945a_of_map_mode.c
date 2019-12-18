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
#define  ACT8945A_REGULATOR_MODE_FIXED 130 
#define  ACT8945A_REGULATOR_MODE_LOWPOWER 129 
#define  ACT8945A_REGULATOR_MODE_NORMAL 128 
 unsigned int REGULATOR_MODE_INVALID ; 
 unsigned int REGULATOR_MODE_NORMAL ; 
 unsigned int REGULATOR_MODE_STANDBY ; 

__attribute__((used)) static unsigned int act8945a_of_map_mode(unsigned int mode)
{
	switch (mode) {
	case ACT8945A_REGULATOR_MODE_FIXED:
	case ACT8945A_REGULATOR_MODE_NORMAL:
		return REGULATOR_MODE_NORMAL;
	case ACT8945A_REGULATOR_MODE_LOWPOWER:
		return REGULATOR_MODE_STANDBY;
	default:
		return REGULATOR_MODE_INVALID;
	}
}