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

float dcn_bw_log(float a, float b)
{
	int * const exp_ptr = (int *)(&a);
	int x = *exp_ptr;
	const int log_2 = ((x >> 23) & 255) - 128;
	x &= ~(255 << 23);
	x += 127 << 23;
	*exp_ptr = x;

	a = ((-1.0f / 3) * a + 2) * a - 2.0f / 3;

	if (b > 2.00001 || b < 1.99999)
		return (a + log_2) / dcn_bw_log(b, 2);
	else
		return (a + log_2);
}