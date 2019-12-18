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
 int* PWM_FREQ ; 

__attribute__((used)) static int PWM_FREQ_TO_REG(long val, int reg)
{
	int i;

	/* the first two cases are special - stupid chip design! */
	if (val > 27500) {
		i = 10;
	} else if (val > 22500) {
		i = 11;
	} else {
		for (i = 9; i > 0; i--) {
			if (val > (PWM_FREQ[i] + PWM_FREQ[i - 1] + 1) / 2)
				break;
		}
	}

	return (reg & 0xf0) | i;
}