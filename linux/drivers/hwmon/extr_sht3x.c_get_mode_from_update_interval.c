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
typedef  size_t u8 ;
typedef  scalar_t__ u16 ;

/* Variables and functions */
 size_t ARRAY_SIZE (scalar_t__*) ; 
 scalar_t__* mode_to_update_interval ; 

__attribute__((used)) static u8 get_mode_from_update_interval(u16 value)
{
	size_t index;
	u8 number_of_modes = ARRAY_SIZE(mode_to_update_interval);

	if (value == 0)
		return 0;

	/* find next faster update interval */
	for (index = 1; index < number_of_modes; index++) {
		if (mode_to_update_interval[index] <= value)
			return index;
	}

	return number_of_modes - 1;
}