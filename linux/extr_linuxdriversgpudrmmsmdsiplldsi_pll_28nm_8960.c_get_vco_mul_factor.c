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

__attribute__((used)) static unsigned int get_vco_mul_factor(unsigned long byte_clk_rate)
{
	unsigned long bit_mhz;

	/* convert to bit clock in Mhz */
	bit_mhz = (byte_clk_rate * 8) / 1000000;

	if (bit_mhz < 125)
		return 64;
	else if (bit_mhz < 250)
		return 32;
	else if (bit_mhz < 600)
		return 16;
	else
		return 8;
}