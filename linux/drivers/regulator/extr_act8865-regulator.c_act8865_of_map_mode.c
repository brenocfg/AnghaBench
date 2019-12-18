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
#define  ACT8865_REGULATOR_MODE_FIXED 130 
#define  ACT8865_REGULATOR_MODE_LOWPOWER 129 
#define  ACT8865_REGULATOR_MODE_NORMAL 128 
 unsigned int REGULATOR_MODE_FAST ; 
 unsigned int REGULATOR_MODE_INVALID ; 
 unsigned int REGULATOR_MODE_NORMAL ; 
 unsigned int REGULATOR_MODE_STANDBY ; 

__attribute__((used)) static unsigned int act8865_of_map_mode(unsigned int mode)
{
	switch (mode) {
	case ACT8865_REGULATOR_MODE_FIXED:
		return REGULATOR_MODE_FAST;
	case ACT8865_REGULATOR_MODE_NORMAL:
		return REGULATOR_MODE_NORMAL;
	case ACT8865_REGULATOR_MODE_LOWPOWER:
		return REGULATOR_MODE_STANDBY;
	default:
		return REGULATOR_MODE_INVALID;
	}
}