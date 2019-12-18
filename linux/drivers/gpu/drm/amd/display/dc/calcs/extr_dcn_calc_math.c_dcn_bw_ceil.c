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
 float dcn_bw_floor2 (float const,int) ; 

float dcn_bw_ceil(const float arg)
{
	float flr = dcn_bw_floor2(arg, 1);

	return flr + 0.00001 >= arg ? arg : flr + 1;
}