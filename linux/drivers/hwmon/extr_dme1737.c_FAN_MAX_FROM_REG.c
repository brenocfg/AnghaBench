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
 int* FAN_MAX ; 

__attribute__((used)) static int FAN_MAX_FROM_REG(int reg)
{
	int i;

	for (i = 10; i > 0; i--) {
		if (reg == FAN_MAX[i])
			break;
	}

	return 1000 + i * 500;
}