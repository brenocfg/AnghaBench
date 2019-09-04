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
 int ARRAY_SIZE (int**) ; 
 int EINVAL ; 
 int** si1133_int_time_table ; 

__attribute__((used)) static int si1133_get_int_time_index(int milliseconds, int nanoseconds)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(si1133_int_time_table); i++) {
		if (milliseconds == si1133_int_time_table[i][0] &&
		    nanoseconds == si1133_int_time_table[i][1])
			return i;
	}
	return -EINVAL;
}