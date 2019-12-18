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
 unsigned int REGULATOR_MODE_FAST ; 
 unsigned int REGULATOR_MODE_IDLE ; 
 unsigned int REGULATOR_MODE_NORMAL ; 

__attribute__((used)) static unsigned int spmi_regulator_of_map_mode(unsigned int mode)
{
	if (mode == 1)
		return REGULATOR_MODE_NORMAL;
	if (mode == 2)
		return REGULATOR_MODE_FAST;

	return REGULATOR_MODE_IDLE;
}