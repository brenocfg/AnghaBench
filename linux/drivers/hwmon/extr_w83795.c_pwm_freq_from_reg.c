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
typedef  int u16 ;

/* Variables and functions */
 unsigned int* pwm_freq_cksel0 ; 

__attribute__((used)) static unsigned int pwm_freq_from_reg(u8 reg, u16 clkin)
{
	unsigned long base_clock;

	if (reg & 0x80) {
		base_clock = clkin * 1000 / ((clkin == 48000) ? 384 : 256);
		return base_clock / ((reg & 0x7f) + 1);
	} else
		return pwm_freq_cksel0[reg & 0x0f];
}