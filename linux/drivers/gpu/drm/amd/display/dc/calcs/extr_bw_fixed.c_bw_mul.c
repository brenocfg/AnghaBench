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
typedef  int uint64_t ;
struct bw_fixed {scalar_t__ value; } ;
struct TYPE_2__ {scalar_t__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int BW_FIXED_BITS_PER_FRACTIONAL_PART ; 
 int BW_FIXED_GET_INTEGER_PART (int) ; 
 int BW_FIXED_MAX_I32 ; 
 int GET_FRACTIONAL_PART (int) ; 
 int MAX_I64 ; 
 int abs_i64 (scalar_t__) ; 
 TYPE_1__ bw_frc_to_fixed (int,int) ; 

struct bw_fixed bw_mul(const struct bw_fixed arg1, const struct bw_fixed arg2)
{
	struct bw_fixed res;

	bool arg1_negative = arg1.value < 0;
	bool arg2_negative = arg2.value < 0;

	uint64_t arg1_value = abs_i64(arg1.value);
	uint64_t arg2_value = abs_i64(arg2.value);

	uint64_t arg1_int = BW_FIXED_GET_INTEGER_PART(arg1_value);
	uint64_t arg2_int = BW_FIXED_GET_INTEGER_PART(arg2_value);

	uint64_t arg1_fra = GET_FRACTIONAL_PART(arg1_value);
	uint64_t arg2_fra = GET_FRACTIONAL_PART(arg2_value);

	uint64_t tmp;

	res.value = arg1_int * arg2_int;

	ASSERT(res.value <= BW_FIXED_MAX_I32);

	res.value <<= BW_FIXED_BITS_PER_FRACTIONAL_PART;

	tmp = arg1_int * arg2_fra;

	ASSERT(tmp <= (uint64_t)(MAX_I64 - res.value));

	res.value += tmp;

	tmp = arg2_int * arg1_fra;

	ASSERT(tmp <= (uint64_t)(MAX_I64 - res.value));

	res.value += tmp;

	tmp = arg1_fra * arg2_fra;

	tmp = (tmp >> BW_FIXED_BITS_PER_FRACTIONAL_PART) +
		(tmp >= (uint64_t)(bw_frc_to_fixed(1, 2).value));

	ASSERT(tmp <= (uint64_t)(MAX_I64 - res.value));

	res.value += tmp;

	if (arg1_negative ^ arg2_negative)
		res.value = -res.value;
	return res;
}