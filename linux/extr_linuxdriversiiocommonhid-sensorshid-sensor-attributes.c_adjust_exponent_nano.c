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
 int abs (int) ; 
 int pow_10 (int) ; 

__attribute__((used)) static void adjust_exponent_nano(int *val0, int *val1, int scale0,
				  int scale1, int exp)
{
	int i;
	int x;
	int res;
	int rem;

	if (exp > 0) {
		*val0 = scale0 * pow_10(exp);
		res = 0;
		if (exp > 9) {
			*val1 = 0;
			return;
		}
		for (i = 0; i < exp; ++i) {
			x = scale1 / pow_10(8 - i);
			res += (pow_10(exp - 1 - i) * x);
			scale1 = scale1 % pow_10(8 - i);
		}
		*val0 += res;
			*val1 = scale1 * pow_10(exp);
	} else if (exp < 0) {
		exp = abs(exp);
		if (exp > 9) {
			*val0 = *val1 = 0;
			return;
		}
		*val0 = scale0 / pow_10(exp);
		rem = scale0 % pow_10(exp);
		res = 0;
		for (i = 0; i < (9 - exp); ++i) {
			x = scale1 / pow_10(8 - i);
			res += (pow_10(8 - exp - i) * x);
			scale1 = scale1 % pow_10(8 - i);
		}
		*val1 = rem * pow_10(9 - exp) + res;
	} else {
		*val0 = scale0;
		*val1 = scale1;
	}
}