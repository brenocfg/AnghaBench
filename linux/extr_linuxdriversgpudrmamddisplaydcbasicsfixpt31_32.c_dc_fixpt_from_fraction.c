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
struct fixed31_32 {long long value; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 unsigned int FIXED31_32_BITS_PER_FRACTIONAL_PART ; 
 unsigned long long LLONG_MAX ; 
 unsigned long long LONG_MAX ; 
 unsigned long long complete_integer_division_u64 (unsigned long long,unsigned long long,unsigned long long*) ; 

struct fixed31_32 dc_fixpt_from_fraction(long long numerator, long long denominator)
{
	struct fixed31_32 res;

	bool arg1_negative = numerator < 0;
	bool arg2_negative = denominator < 0;

	unsigned long long arg1_value = arg1_negative ? -numerator : numerator;
	unsigned long long arg2_value = arg2_negative ? -denominator : denominator;

	unsigned long long remainder;

	/* determine integer part */

	unsigned long long res_value = complete_integer_division_u64(
		arg1_value, arg2_value, &remainder);

	ASSERT(res_value <= LONG_MAX);

	/* determine fractional part */
	{
		unsigned int i = FIXED31_32_BITS_PER_FRACTIONAL_PART;

		do {
			remainder <<= 1;

			res_value <<= 1;

			if (remainder >= arg2_value) {
				res_value |= 1;
				remainder -= arg2_value;
			}
		} while (--i != 0);
	}

	/* round up LSB */
	{
		unsigned long long summand = (remainder << 1) >= arg2_value;

		ASSERT(res_value <= LLONG_MAX - summand);

		res_value += summand;
	}

	res.value = (long long)res_value;

	if (arg1_negative ^ arg2_negative)
		res.value = -res.value;

	return res;
}