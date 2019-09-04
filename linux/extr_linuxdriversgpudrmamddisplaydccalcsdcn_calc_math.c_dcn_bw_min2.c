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
 scalar_t__ isNaN (float const) ; 

float dcn_bw_min2(const float arg1, const float arg2)
{
	if (isNaN(arg1))
		return arg2;
	if (isNaN(arg2))
		return arg1;
	return arg1 < arg2 ? arg1 : arg2;
}