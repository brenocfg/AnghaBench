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
 int* PWM_RR ; 

__attribute__((used)) static int PWM_RR_TO_REG(long val, int ix, int reg)
{
	int i;

	for (i = 0; i < 7; i++) {
		if (val > (PWM_RR[i] + PWM_RR[i + 1] + 1) / 2)
			break;
	}

	return (ix == 1) ? (reg & 0x8f) | (i << 4) : (reg & 0xf8) | i;
}