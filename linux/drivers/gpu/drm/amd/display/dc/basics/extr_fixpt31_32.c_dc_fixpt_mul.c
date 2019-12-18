#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct fixed31_32 {unsigned long long value; } ;
struct TYPE_2__ {scalar_t__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 unsigned long long FIXED31_32_BITS_PER_FRACTIONAL_PART ; 
 unsigned long long GET_FRACTIONAL_PART (unsigned long long) ; 
 unsigned long long GET_INTEGER_PART (unsigned long long) ; 
 unsigned long long LLONG_MAX ; 
 unsigned long long LONG_MAX ; 
 TYPE_1__ dc_fixpt_half ; 

struct fixed31_32 dc_fixpt_mul(struct fixed31_32 arg1, struct fixed31_32 arg2)
{
	struct fixed31_32 res;

	bool arg1_negative = arg1.value < 0;
	bool arg2_negative = arg2.value < 0;

	unsigned long long arg1_value = arg1_negative ? -arg1.value : arg1.value;
	unsigned long long arg2_value = arg2_negative ? -arg2.value : arg2.value;

	unsigned long long arg1_int = GET_INTEGER_PART(arg1_value);
	unsigned long long arg2_int = GET_INTEGER_PART(arg2_value);

	unsigned long long arg1_fra = GET_FRACTIONAL_PART(arg1_value);
	unsigned long long arg2_fra = GET_FRACTIONAL_PART(arg2_value);

	unsigned long long tmp;

	res.value = arg1_int * arg2_int;

	ASSERT(res.value <= LONG_MAX);

	res.value <<= FIXED31_32_BITS_PER_FRACTIONAL_PART;

	tmp = arg1_int * arg2_fra;

	ASSERT(tmp <= (unsigned long long)(LLONG_MAX - res.value));

	res.value += tmp;

	tmp = arg2_int * arg1_fra;

	ASSERT(tmp <= (unsigned long long)(LLONG_MAX - res.value));

	res.value += tmp;

	tmp = arg1_fra * arg2_fra;

	tmp = (tmp >> FIXED31_32_BITS_PER_FRACTIONAL_PART) +
		(tmp >= (unsigned long long)dc_fixpt_half.value);

	ASSERT(tmp <= (unsigned long long)(LLONG_MAX - res.value));

	res.value += tmp;

	if (arg1_negative ^ arg2_negative)
		res.value = -res.value;

	return res;
}