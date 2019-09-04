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
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static uint32_t convert_and_clamp(
	uint32_t wm_ns,
	uint32_t refclk_mhz,
	uint32_t clamp_value)
{
	uint32_t ret_val = 0;
	ret_val = wm_ns * refclk_mhz;
	ret_val /= 1000;

	if (ret_val > clamp_value)
		ret_val = clamp_value;

	return ret_val;
}