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
 int EINVAL ; 

__attribute__((used)) static int mma8452_get_int_plus_micros_index(const int (*vals)[2], int n,
					     int val, int val2)
{
	while (n-- > 0)
		if (val == vals[n][0] && val2 == vals[n][1])
			return n;

	return -EINVAL;
}