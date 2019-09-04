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
struct dcn_bw_internal_vars {float* max_dppclk; } ;

/* Variables and functions */

__attribute__((used)) static void hack_force_pipe_split(struct dcn_bw_internal_vars *v,
		unsigned int pixel_rate_khz)
{
	float pixel_rate_mhz = pixel_rate_khz / 1000;

	/*
	 * force enabling pipe split by lower dpp clock for DPM0 to just
	 * below the specify pixel_rate, so bw calc would split pipe.
	 */
	if (pixel_rate_mhz < v->max_dppclk[0])
		v->max_dppclk[0] = pixel_rate_mhz;
}