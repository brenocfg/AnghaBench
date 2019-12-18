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
typedef  int u8 ;

/* Variables and functions */

__attribute__((used)) static inline u8 pwm_freq_to_reg(unsigned long val)
{
	if (val >= 187500)	/* The highest we can do */
		return 0x80;
	if (val >= 1475)	/* Use 48 MHz clock */
		return 0x80 | (48000000UL / (val << 8));
	if (val < 31)		/* The lowest we can do */
		return 0x7f;
	else			/* Use 1 MHz clock */
		return 1000000UL / (val << 8);
}