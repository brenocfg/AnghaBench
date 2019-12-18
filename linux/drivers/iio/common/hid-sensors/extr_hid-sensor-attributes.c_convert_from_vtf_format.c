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
typedef  int u32 ;

/* Variables and functions */
 int BIT (int) ; 
 int hid_sensor_convert_exponent (int) ; 
 int int_pow (int,int) ; 
 int /*<<< orphan*/  split_micro_fraction (int,int,int*,int*) ; 

__attribute__((used)) static void convert_from_vtf_format(u32 value, int size, int exp,
					int *val1, int *val2)
{
	int sign = 1;

	if (value & BIT(size*8 - 1)) {
		value =  ((1LL << (size * 8)) - value);
		sign = -1;
	}
	exp = hid_sensor_convert_exponent(exp);
	if (exp >= 0) {
		*val1 = sign * value * int_pow(10, exp);
		*val2 = 0;
	} else {
		split_micro_fraction(value, -exp, val1, val2);
		if (*val1)
			*val1 = sign * (*val1);
		else
			*val2 = sign * (*val2);
	}
}