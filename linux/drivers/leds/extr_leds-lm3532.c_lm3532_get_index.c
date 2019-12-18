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

__attribute__((used)) static int lm3532_get_index(const int table[], int size, int value)
{
	int i;

	for (i = 1; i < size; i++) {
		if (value == table[i])
			return i;

		/* Find an approximate index by looking up the table */
		if (value > table[i - 1] &&
		    value < table[i]) {
			if (value - table[i - 1] < table[i] - value)
				return i - 1;
			else
				return i;
		}
	}

	return -EINVAL;
}