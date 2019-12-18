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
#define  REGULATOR_MODE_FAST 131 
#define  REGULATOR_MODE_IDLE 130 
#define  REGULATOR_MODE_NORMAL 129 
#define  REGULATOR_MODE_STANDBY 128 
 int REGULATOR_STATUS_FAST ; 
 int REGULATOR_STATUS_IDLE ; 
 int REGULATOR_STATUS_NORMAL ; 
 int REGULATOR_STATUS_STANDBY ; 
 int REGULATOR_STATUS_UNDEFINED ; 

int regulator_mode_to_status(unsigned int mode)
{
	switch (mode) {
	case REGULATOR_MODE_FAST:
		return REGULATOR_STATUS_FAST;
	case REGULATOR_MODE_NORMAL:
		return REGULATOR_STATUS_NORMAL;
	case REGULATOR_MODE_IDLE:
		return REGULATOR_STATUS_IDLE;
	case REGULATOR_MODE_STANDBY:
		return REGULATOR_STATUS_STANDBY;
	default:
		return REGULATOR_STATUS_UNDEFINED;
	}
}