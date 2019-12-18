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

__attribute__((used)) static const char *regulator_opmode_to_str(int mode)
{
	switch (mode) {
	case REGULATOR_MODE_FAST:
		return "fast";
	case REGULATOR_MODE_NORMAL:
		return "normal";
	case REGULATOR_MODE_IDLE:
		return "idle";
	case REGULATOR_MODE_STANDBY:
		return "standby";
	}
	return "unknown";
}