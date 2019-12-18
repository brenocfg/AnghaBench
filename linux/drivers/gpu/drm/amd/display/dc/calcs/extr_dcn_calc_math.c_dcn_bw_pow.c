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

float dcn_bw_pow(float a, float exp)
{
	float temp;
	/*ASSERT(exp == (int)exp);*/
	if ((int)exp == 0)
		return 1;
	temp = dcn_bw_pow(a, (int)(exp / 2));
	if (((int)exp % 2) == 0) {
		return temp * temp;
	} else {
		if ((int)exp > 0)
			return a * temp * temp;
		else
			return (temp * temp) / a;
	}
}