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
 int* TEMP_RANGE ; 

__attribute__((used)) static int TEMP_RANGE_TO_REG(long val, int reg)
{
	int i;

	for (i = 15; i > 0; i--) {
		if (val > (TEMP_RANGE[i] + TEMP_RANGE[i - 1] + 1) / 2)
			break;
	}

	return (reg & 0x0f) | (i << 4);
}