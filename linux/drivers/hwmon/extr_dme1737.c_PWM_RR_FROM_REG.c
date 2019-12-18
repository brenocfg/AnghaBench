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

__attribute__((used)) static inline int PWM_RR_FROM_REG(int reg, int ix)
{
	int rr = (ix == 1) ? reg >> 4 : reg;

	return (rr & 0x08) ? PWM_RR[rr & 0x07] : 0;
}