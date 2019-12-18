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

__attribute__((used)) static inline int PWM_RR_EN_TO_REG(long val, int ix, int reg)
{
	int en = (ix == 1) ? 0x80 : 0x08;

	return val ? reg | en : reg & ~en;
}