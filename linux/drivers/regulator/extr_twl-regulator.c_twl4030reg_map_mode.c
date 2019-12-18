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
 unsigned int REGULATOR_MODE_INVALID ; 
 unsigned int REGULATOR_MODE_NORMAL ; 
 unsigned int REGULATOR_MODE_STANDBY ; 
#define  RES_STATE_ACTIVE 129 
#define  RES_STATE_SLEEP 128 

__attribute__((used)) static inline unsigned int twl4030reg_map_mode(unsigned int mode)
{
	switch (mode) {
	case RES_STATE_ACTIVE:
		return REGULATOR_MODE_NORMAL;
	case RES_STATE_SLEEP:
		return REGULATOR_MODE_STANDBY;
	default:
		return REGULATOR_MODE_INVALID;
	}
}