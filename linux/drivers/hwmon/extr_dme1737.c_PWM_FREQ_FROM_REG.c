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

__attribute__((used)) static inline int PWM_FREQ_FROM_REG(int reg)
{
	return PWM_FREQ[reg & 0x0f];
}