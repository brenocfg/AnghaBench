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
typedef  long long u32 ;

/* Variables and functions */
 long long abs (int) ; 
 int hid_sensor_convert_exponent (int) ; 
 long long pow_10 (int) ; 

__attribute__((used)) static u32 convert_to_vtf_format(int size, int exp, int val1, int val2)
{
	u32 value;
	int sign = 1;

	if (val1 < 0 || val2 < 0)
		sign = -1;
	exp = hid_sensor_convert_exponent(exp);
	if (exp < 0) {
		value = abs(val1) * pow_10(-exp);
		value += abs(val2) / pow_10(6+exp);
	} else
		value = abs(val1) / pow_10(exp);
	if (sign < 0)
		value =  ((1LL << (size * 8)) - value);

	return value;
}