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
 float dcn_bw_floor2 (float const,float const) ; 

float dcn_bw_ceil2(const float arg, const float significance)
{
	float flr = dcn_bw_floor2(arg, significance);
	if (significance == 0)
		return 0;
	return flr + 0.00001 >= arg ? arg : flr + significance;
}