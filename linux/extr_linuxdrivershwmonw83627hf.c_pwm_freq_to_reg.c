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
	/* Minimum divider value is 0x01 and maximum is 0x7F */
	if (val >= 93750)	/* The highest we can do */
		return 0x01;
	if (val >= 720)	/* Use 24 MHz clock */
		return 24000000UL / (val << 8);
	if (val < 6)		/* The lowest we can do */
		return 0xFF;
	else			/* Use 180 kHz clock */
		return 0x80 | (180000UL / (val << 8));
}